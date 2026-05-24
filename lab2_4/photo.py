from datetime import datetime

class Photo:
    def __init__(self, owner_name: str, description: str) -> None:
        self.owner_name = owner_name
        self.description = description
        self.timestamp = datetime.now()

    def __repr__(self) -> str:
        time_str = self.timestamp.strftime("%H:%M:%S")
        return f"[{time_str}] {self.owner_name} опубликовал фото: {self.description}"