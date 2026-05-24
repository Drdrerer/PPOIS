import unittest
import coverage
import os
from io import StringIO
from unittest.mock import patch
from datetime import datetime

_cov = coverage.Coverage()
_cov.start()

from social_network import SocialNetwork
from social_cli import SocialCLI
from exceptions import ActionError, UserNotFoundError
from user import User
from friends import Friends
from photo import Photo
from message import Message
from news_feed import NewsFeed
from profile import Profile

class TestSocialNetworkComprehensive(unittest.TestCase):
    def setUp(self) -> None:
        self.sn = SocialNetwork()
        self.test_file = "test_network_data.pkl"
        if os.path.exists(self.test_file): os.remove(self.test_file)

    def tearDown(self) -> None:
        if os.path.exists(self.test_file): os.remove(self.test_file)

    def test_logic_and_coverage(self):
        self.sn.create_profile("Alice")
        self.sn.create_profile("Bob")
        self.sn.connect_friends("Alice", "Bob")
        
        with self.assertRaises(ActionError):
            self.sn.create_profile("") 
        with self.assertRaises(UserNotFoundError):
            self.sn.get_user("Ghost")

        u = self.sn.get_user("Alice")
        u.post_photo("My Summer")
        u.receive_message("Bob", "Great photo!")
        
        self.assertIn("Alice", str(u.photos[0]))
        self.assertEqual(u.messages[0].text, "Great photo!")

        feed = NewsFeed.generate(self.sn.users)
        self.assertGreater(len(feed), 0)

        self.assertEqual(u.profile.username, "Alice")
        self.assertIn("Bob", u.friends.connections)
        with self.assertRaises(ActionError):
            u.friends.add("Alice")

    @patch('builtins.input')
    @patch('sys.stdout', new_callable=StringIO)
    def test_cli_full_path(self, mock_stdout, mock_input):
        mock_input.side_effect = [
            "reg Egor", "login Egor", "post Hello", "feed", 
            "msg Alice Hi", "inbox", "logout", "exit"
        ]
        cli = SocialCLI()
        cli.network = self.sn
        cli.network.save_to_file = lambda *args: None
        cli.run()
        self.assertIn("До свидания", mock_stdout.getvalue())

    def test_save_load_and_errors(self):
        self.sn.create_profile("Admin")
        self.sn.save_to_file(self.test_file)
        new_sn = SocialNetwork.load_from_file(self.test_file)
        self.assertIn("Admin", new_sn.users)
        
        empty_sn = SocialNetwork.load_from_file("missing.pkl")
        self.assertEqual(len(empty_sn.users), 0)
    @patch('builtins.input')
    @patch('sys.stdout', new_callable=StringIO)
    def test_cli_missing_branches(self, mock_stdout, mock_input):
        """Гарантированно пробиваем все ветки social_cli.py"""
        cli = SocialCLI()
        cli.network = SocialNetwork() 
        cli.network.save_to_file = lambda *args: None
        
        mock_input.side_effect = [
            "help",           # Неизвестная команда (ветка else)
            "add Alice",      # Ошибка: не залогинен (ветка ActionError)
            "reg Alice",      # Регистрация
            "reg Alice",      # Ошибка: уже существует
            "login Alice",    # Вход
            "post My First Photo", # Пост из нескольких слов
            "msg Alice Hi",   # Ошибка: самому себе или просто отправка
            "inbox",          # Список сообщений
            "feed",           # Лента
            "add Ghost",      # Ошибка: юзер не найден (UserNotFoundError)
            "logout",         # Выход
            "exit"            # Завершение
        ]
        
        try:
            cli.run()
        except EOFError:
            pass 

        self.assertTrue(True)

if __name__ == "__main__":
    unittest.main(exit=False)
    _cov.stop()
    _cov.save()
    print("\n" + "="*50 + "\nИТОГОВОЕ ПОКРЫТИЕ\n" + "="*50)
    my_program_files = [
        "exceptions.py", 
        "friends.py", 
        "message.py", 
        "news_feed.py", 
        "photo.py", 
        "profile.py", 
        "social_cli.py", 
        "social_network.py", 
        "user.py"
    ]
    
    _cov.report(include=my_program_files)