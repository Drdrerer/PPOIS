from typing import List, Dict
from user import User
from photo import Photo

class NewsFeed:
    @staticmethod
    def generate(users_dict: Dict[str, User]) -> List[Photo]:
        all_photos: List[Photo] = []
        for user_obj in users_dict.values():
            all_photos.extend(user_obj.photos)
        return sorted(all_photos, key=lambda x: x.timestamp, reverse=True)