from typing import Set
from exceptions import ActionError

class Friends:
    def __init__(self, owner_name: str) -> None:
        self.owner_name = owner_name
        self.connections: Set[str] = set()

    def add(self, friend_name: str) -> None:
        if friend_name == self.owner_name:
            raise ActionError("Нельзя добавить в друзья самого себя.")
        self.connections.add(friend_name)