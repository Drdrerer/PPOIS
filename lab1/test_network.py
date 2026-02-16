import unittest
from main import SocialNetwork, ActionError, UserNotFoundError

class TestSocialNetwork(unittest.TestCase):
    def setUp(self) -> None:
        """Настройка окружения перед каждым тестом."""
        self.sn = SocialNetwork()
        self.sn.create_profile("Alice")
        self.sn.create_profile("Bob")
        self.sn.create_profile("Charlie")

    def test_create_profile_success(self) -> None:
        """Проверка успешного создания профиля."""
        self.assertIn("Alice", self.sn.users)

    def test_duplicate_profile_raises_error(self) -> None:
        """Проверка обработки исключения при дублировании имени."""
        with self.assertRaises(ActionError):
            self.sn.create_profile("Alice")

    def test_global_news_feed_visibility(self) -> None:
        """
        Ключевой тест: проверяем, что все видят публикации всех, 
        даже не будучи друзьями.
        """
        # Алиса публикует фото
        self.sn.get_user("Alice").post_photo("Завтрак Алисы")
        
        # Боб (не друг Алисы) смотрит ленту
        bob_feed = self.sn.get_news_feed("Bob")
        
        # Проверяем, что пост Алисы виден Бобу
        descriptions = [photo.description for photo in bob_feed]
        self.assertIn("Завтрак Алисы", descriptions, "Боб должен видеть пост Алисы в глобальной ленте")

    def test_own_posts_in_feed(self) -> None:
        """Проверка, что собственные посты пользователя есть в его ленте."""
        self.sn.get_user("Charlie").post_photo("Мое селфи")
        charlie_feed = self.sn.get_news_feed("Charlie")
        
        self.assertTrue(any(p.description == "Мое селфи" for p in charlie_feed))

    def test_add_friend_logic(self) -> None:
        """Проверка корректности работы механизма друзей."""
        self.sn.connect_friends("Alice", "Bob")
        alice = self.sn.get_user("Alice")
        bob = self.sn.get_user("Bob")
        
        self.assertIn("Bob", alice.friends)
        self.assertIn("Alice", bob.friends)

    def test_message_delivery(self) -> None:
        """Проверка отправки и получения сообщений."""
        self.sn.send_private_message("Alice", "Charlie", "Привет, Чарли!")
        charlie = self.sn.get_user("Charlie")
        
        self.assertEqual(len(charlie.messages), 1)
        self.assertEqual(charlie.messages[0].text, "Привет, Чарли!")
        self.assertEqual(charlie.messages[0].sender, "Alice")

    def test_invalid_user_access(self) -> None:
        """Проверка исключения при попытке получить доступ к несуществующему пользователю."""
        with self.assertRaises(UserNotFoundError):
            self.sn.get_user("UnknownUser")

if __name__ == "__main__":
    unittest.main()
