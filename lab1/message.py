from datetime import datetime

class Message:
    def __init__(self, sender: str, text: str) -> None:
        self.sender = sender
        self.text = text
        self.timestamp = datetime.now()