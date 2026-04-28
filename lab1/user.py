from typing import List
from profile import Profile
from friends import Friends
from message import Message
from photo import Photo

class User:
    def __init__(self, username: str) -> None:
        self.profile = Profile(username)
        self.friends = Friends(username)
        self.messages: List[Message] = []
        self.photos: List[Photo] = []

    @property
    def username(self) -> str:
        return self.profile.username

    def receive_message(self, sender_name: str, text: str) -> None:
        new_msg = Message(sender_name, text)
        self.messages.append(new_msg)

    def post_photo(self, description: str) -> None:
        self.photos.append(Photo(self.username, description))
