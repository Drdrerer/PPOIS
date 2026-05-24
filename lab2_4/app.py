import os
from flask import Flask, render_template, request, redirect, url_for, flash, session
from social_network import SocialNetwork
from news_feed import NewsFeed
from exceptions import SocialNetworkError

app = Flask(__name__)
# Ключ для работы сессий и flash-сообщений
app.secret_key = "super_secret_solid_web_key"

def get_network() -> SocialNetwork:
    """Инициализация или загрузка общей бизнес-логики."""
    return SocialNetwork.load_from_file()

@app.route("/")
def index():
    network = get_network()
    current_username = session.get("current_user")
    user_obj = None
    feed = []
    
    if current_username:
        try:
            user_obj = network.get_user(current_username)
            feed = NewsFeed.generate(network.users)
        except SocialNetworkError:
            # Если пользователя удалили или что-то пошло не так
            session.pop("current_user", None)
            current_username = None

    return render_template(
        "index.html", 
        network=network, 
        current_user=current_username, 
        user=user_obj, 
        feed=feed
    )

@app.route("/register", methods=["POST"])
def register():
    username = request.form.get("username", "").strip()
    network = get_network()
    try:
        network.create_profile(username)
        network.save_to_file()
        flash(f"Пользователь {username} успешно зарегистрирован!", "success")
    except SocialNetworkError as e:
        flash(f"Ошибка регистрации: {e}", "error")
    return redirect(url_for("index"))

@app.route("/login", methods=["POST"])
def login():
    username = request.form.get("username", "").strip()
    network = get_network()
    try:
        user = network.get_user(username)
        session["current_user"] = user.username
        flash(f"Добро пожаловать, {user.username}!", "success")
    except SocialNetworkError as e:
        flash(f"Ошибка входа: {e}", "error")
    return redirect(url_for("index"))

@app.route("/logout")
def logout():
    session.pop("current_user", None)
    flash("Вы вышли из системы.", "info")
    return redirect(url_for("index"))

@app.route("/add_friend", methods=["POST"])
def add_friend():
    current_username = session.get("current_user")
    if not current_username:
        flash("Необходима авторизация.", "error")
        return redirect(url_for("index"))
        
    friend_name = request.form.get("friend_name", "").strip()
    network = get_network()
    try:
        network.connect_friends(current_username, friend_name)
        network.save_to_file()
        flash(f"Вы и {friend_name} теперь друзья!", "success")
    except SocialNetworkError as e:
        flash(f"Ошибка: {e}", "error")
    return redirect(url_for("index"))

@app.route("/post", methods=["POST"])
def post_photo():
    current_username = session.get("current_user")
    if not current_username:
        flash("Необходима авторизация.", "error")
        return redirect(url_for("index"))
        
    description = request.form.get("description", "").strip()
    network = get_network()
    try:
        user = network.get_user(current_username)
        user.post_photo(description)
        network.save_to_file()
        flash("Фотография успешно опубликована!", "success")
    except SocialNetworkError as e:
        flash(f"Ошибка публикации: {e}", "error")
    return redirect(url_for("index"))

@app.route("/send_message", methods=["POST"])
def send_message():
    current_username = session.get("current_user")
    if not current_username:
        flash("Необходима авторизация.", "error")
        return redirect(url_for("index"))
        
    to_user = request.form.get("to_user", "").strip()
    text = request.form.get("text", "").strip()
    network = get_network()
    try:
        network.send_private_message(current_username, to_user, text)
        network.save_to_file()
        flash(f"Сообщение для {to_user} отправлено!", "success")
    except SocialNetworkError as e:
        flash(f"Ошибка отправки: {e}", "error")
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run(debug=True, port=5000)