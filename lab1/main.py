import sys
from datetime import datetime
from typing import List, Dict, Optional, Set


class SocialNetworkError(Exception):
    """Базовое исключение для всех ошибок системы."""
    pass


class UserNotFoundError(SocialNetworkError):
    """Вызывается, если пользователь не найден в базе."""
    pass


class ActionError(SocialNetworkError):
    """Вызывается при нарушении бизнес-логики."""
    pass


class Photo:
    """Сущность фотографии с описанием и временем публикации."""
    def __init__(self, owner_name: str, description: str) -> None:
        self.owner_name: str = owner_name
        self.description: str = description
        self.timestamp: datetime = datetime.now()

    def __repr__(self) -> str:
        time_str = self.timestamp.strftime("%H:%M:%S")
        return f"[{time_str}] {self.owner_name} опубликовал фото: {self.description}"


class Message:
    """Сущность личного сообщения."""
    def __init__(self, sender: str, text: str) -> None:
        self.sender: str = sender
        self.text: str = text
        self.timestamp: datetime = datetime.now()


class User:
    """Сущность пользователя, хранящая профиль, друзей и контент."""
    def __init__(self, username: str) -> None:
        self.username: str = username
        self.friends: Set[str] = set()
        self.messages: List[Message] = []
        self.photos: List[Photo] = []

    def add_friend(self, friend_name: str) -> None:
        if friend_name == self.username:
            raise ActionError("Нельзя добавить в друзья самого себя.")
        self.friends.add(friend_name)

    def receive_message(self, sender: str, text: str) -> None:
        self.messages.append(Message(sender, text))

    def post_photo(self, description: str) -> None:
        self.photos.append(Photo(self.username, description))


class SocialNetwork:
    """Управление пользователями и их взаимодействием."""
    def __init__(self) -> None:
        self.users: Dict[str, User] = {}

    def create_profile(self, username: str) -> None:
        if not username:
            raise ActionError("Имя пользователя не может быть пустым.")
        if username in self.users:
            raise ActionError(f"Пользователь '{username}' уже существует.")
        self.users[username] = User(username)

    def get_user(self, username: str) -> User:
        if username not in self.users:
            raise UserNotFoundError(f"Пользователь '{username}' не найден.")
        return self.users[username]

    def connect_friends(self, user1_name: str, user2_name: str) -> None:
        u1 = self.get_user(user1_name)
        u2 = self.get_user(user2_name)
        u1.add_friend(user2_name)
        u2.add_friend(user1_name)

    def send_private_message(self, from_user: str, to_user: str, text: str) -> None:
        sender = self.get_user(from_user)
        receiver = self.get_user(to_user)
        receiver.receive_message(sender.username, text)

    def get_news_feed(self, username: str) -> List[Photo]:
        """Глобальная лента новостей."""
        self.get_user(username) 
        all_photos: List[Photo] = []
        for user_obj in self.users.values():
            all_photos.extend(user_obj.photos)
        return sorted(all_photos, key=lambda x: x.timestamp, reverse=True)


class SocialCLI:
    def __init__(self) -> None:
        self.network = SocialNetwork()
        self.current_user: Optional[str] = None

    def _show_help(self) -> None:
        print("\nДоступные команды:")
        print("  reg [имя]      - Регистрация")
        print("  login [имя]    - Вход в аккаунт")
        print("  add [имя]      - Добавить друга")
        print("  msg [имя] [текст] - Написать сообщение")
        print("  post [текст]   - Опубликовать фото")
        print("  feed           - Лента новостей")
        print("  inbox          - Входящие сообщения")
        print("  logout         - Выйти из аккаунта")
        print("  exit           - Выход")

    def run(self) -> None:
        print("=== СИСТЕМА СОЦИАЛЬНАЯ СЕТЬ v1.0 ===")
        self._show_help()
        
        while True:
            prompt = f"\n({self.current_user or 'Гость'}) > "
            try:
                raw_input = input(prompt).strip().split(maxsplit=2)
                if not raw_input: continue
                
                cmd = raw_input[0].lower()
                args = raw_input[1:]

                if cmd == "exit":
                    print("До свидания!")
                    break
                
                elif cmd == "reg":
                    self.network.create_profile(args[0])
                    print(f"Пользователь {args[0]} зарегистрирован.")

                elif cmd == "login":
                    user = self.network.get_user(args[0])
                    self.current_user = user.username
                    print(f"Добро пожаловать, {self.current_user}!")

                elif cmd == "logout":
                    self.current_user = None
                    print("Вы вышли из системы.")

                elif cmd == "add":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    self.network.connect_friends(self.current_user, args[0])
                    print(f"Вы и {args[0]} теперь друзья.")

                elif cmd == "post":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    text = " ".join(args)
                    self.network.get_user(self.current_user).post_photo(text)
                    print("Фото опубликовано.")

                elif cmd == "feed":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    feed = self.network.get_news_feed(self.current_user)
                    if not feed: print("В ленте пока пусто.")
                    for photo in feed: print(photo)

                elif cmd == "msg":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    self.network.send_private_message(self.current_user, args[0], args[1])
                    print("Сообщение отправлено.")

                elif cmd == "inbox":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    messages = self.network.get_user(self.current_user).messages
                    for m in messages:
                        print(f"[{m.sender}]: {m.text}")

                else:
                    print("Неизвестная команда.")
                    self._show_help()

            except IndexError:
                print("Ошибка: Недостаточно аргументов для команды.")
            except SocialNetworkError as e:
                print(f"Ошибка системы: {e}", file=sys.stderr)
            except KeyboardInterrupt:
                print("\nПринудительный выход.")
                break


if __name__ == "__main__":
    SocialCLI().run()
