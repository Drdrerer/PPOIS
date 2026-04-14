import unittest
import os
import sys
from io import StringIO
from unittest.mock import patch
from qer import SocialNetwork, ActionError, UserNotFoundError, SocialCLI

class TestSocialNetworkComprehensive(unittest.TestCase):
    def setUp(self) -> None:
        self.sn = SocialNetwork()
        self.test_file = "test_network_data.pkl"
        if os.path.exists(self.test_file):
            os.remove(self.test_file)

    def tearDown(self) -> None:
        if os.path.exists(self.test_file):
            os.remove(self.test_file)

    def test_basic_logic(self):
        self.sn.create_profile("Alice")
        self.sn.create_profile("Bob")
        self.sn.connect_friends("Alice", "Bob")
        self.sn.send_private_message("Alice", "Bob", "Hi")
        self.sn.get_user("Alice").post_photo("Test")
        self.sn.save_to_file(self.test_file)
        
        new_sn = SocialNetwork.load_from_file(self.test_file)
        self.assertIn("Alice", new_sn.users)

    def test_errors(self):
        with self.assertRaises(ActionError):
            self.sn.create_profile("")
        with self.assertRaises(UserNotFoundError):
            self.sn.get_user("Ghost")

    @patch('builtins.input')
    @patch('sys.stdout', new_callable=StringIO)
    def test_cli_flow(self, mock_stdout, mock_input):
        mock_input.side_effect = [
            "reg Tester",
            "login Tester",
            "post MyPhoto",
            "feed",
            "inbox",
            "add Ghost",
            "logout",
            "exit"
        ]
        
        cli = SocialCLI()
        cli.network.save_to_file = lambda *args: None 
        
        cli.run()
        
        output = mock_stdout.getvalue()
        self.assertIn("Tester зарегистрирован", output)
        self.assertIn("Добро пожаловать, Tester", output)
        self.assertIn("MyPhoto", output)

    @patch('builtins.input')
    def test_cli_keyboard_interrupt(self, mock_input):
        mock_input.side_effect = KeyboardInterrupt
        cli = SocialCLI()
        cli.network.save_to_file = lambda *args: None
        cli.run()

    @patch('builtins.input')
    @patch('sys.stdout', new_callable=StringIO)
    def test_cli_missing_args(self, mock_stdout, mock_input):
        mock_input.side_effect = ["reg", "exit"]
        cli = SocialCLI()
        cli.network.save_to_file = lambda *args: None
        cli.run()
        self.assertIn("Недостаточно аргументов", mock_stdout.getvalue())

    def test_msg_repr_and_errors(self):
        self.sn.create_profile("A")
        self.sn.create_profile("B")
        cli = SocialCLI()
        cli.network = self.sn
        with patch('builtins.input', side_effect=["login A", "msg B Hello", "exit"]):
            cli.run()
        self.assertEqual(len(self.sn.get_user("B").messages), 1)

if __name__ == "__main__":
    unittest.main()
