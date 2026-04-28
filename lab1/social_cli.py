import sys
from typing import Optional
from social_network import SocialNetwork
from news_feed import NewsFeed
from exceptions import SocialNetworkError, ActionError

class SocialCLI:
    def __init__(self) -> None:
        self.network = SocialNetwork.load_from_file()
        self.current_user: Optional[str] = None

    def _save(self) -> None:
        self.network.save_to_file()

    def _show_help(self) -> None:
        print("\nДоступные команды:")
        print("  reg [имя]        - Регистрация")
        print("  login [имя]      - Вход в аккаунт")
        print("  add [имя]        - Добавить друга")
        print("  msg [имя] [текст] - Написать сообщение")
        print("  post [текст]     - Опубликовать фото")
        print("  feed             - Лента новостей")
        print("  inbox            - Входящие сообщения")
        print("  logout           - Выйти из аккаунта")
        print("  exit             - Выход")

    def run(self) -> None:
        print("=== СИСТЕМА СОЦИАЛЬНАЯ СЕТЬ (SOLID v3.0) ===")
        self._show_help()
        
        while True:
            prompt = f"\n({self.current_user or 'Гость'}) > "
            try:
                raw_input = input(prompt).strip().split(maxsplit=2)
                if not raw_input: continue
                
                cmd = raw_input[0].lower()
                args = raw_input[1:]

                if cmd == "exit":
                    self._save() 
                    print("Данные сохранены. До свидания!")
                    break
                
                elif cmd == "reg":
                    self.network.create_profile(args[0])
                    self._save()
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
                    self._save()
                    print(f"Вы и {args[0]} теперь друзья.")

                elif cmd == "post":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    text = " ".join(args)
                    self.network.get_user(self.current_user).post_photo(text)
                    self._save()
                    print("Фото опубликовано.")

                elif cmd == "feed":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    feed = NewsFeed.generate(self.network.users)
                    if not feed: print("В ленте пока пусто.")
                    for photo in feed: print(photo)

                elif cmd == "msg":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    self.network.send_private_message(self.current_user, args[0], args[1])
                    self._save()
                    print("Сообщение отправлено.")

                elif cmd == "inbox":
                    if not self.current_user: raise ActionError("Войдите в систему.")
                    messages = self.network.get_user(self.current_user).messages
                    for m in messages:
                        print(f"[{m.timestamp.strftime('%H:%M:%S')}] {m.sender}: {m.text}")

                else:
                    print("Неизвестная команда.")
                    self._show_help()

            except IndexError:
                print("Ошибка: Недостаточно аргументов для команды.")
            except SocialNetworkError as e:
                print(f"Ошибка системы: {e}", file=sys.stderr)
            except KeyboardInterrupt:
                self._save()
                print("\nСистема сохранена. Принудительный выход.")
                break
