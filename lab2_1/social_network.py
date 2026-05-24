import os
import pickle
from typing import Dict
from user import User
from exceptions import ActionError, UserNotFoundError

class SocialNetwork:
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
        u1.friends.add(user2_name)
        u2.friends.add(user1_name)

    def send_private_message(self, from_user: str, to_user: str, text: str) -> None:
        sender = self.get_user(from_user)
        receiver = self.get_user(to_user)
        receiver.receive_message(sender.username, text)

    def save_to_file(self, filename: str = "network_data.pkl") -> None:
        base_path = os.path.dirname(os.path.abspath(__file__))
        full_path = os.path.join(base_path, filename)
        with open(full_path, "wb") as f:
            pickle.dump(self, f)

    @staticmethod
    def load_from_file(filename: str = "network_data.pkl") -> 'SocialNetwork':
        base_path = os.path.dirname(os.path.abspath(__file__))
        full_path = os.path.join(base_path, filename)
        try:
            with open(full_path, "rb") as f:
                return pickle.load(f)
        except (FileNotFoundError, EOFError):
            return SocialNetwork()