class SocialNetworkError(Exception):
    """Базовое исключение."""
    pass

class UserNotFoundError(SocialNetworkError):
    """Пользователь не найден."""
    pass

class ActionError(SocialNetworkError):
    """Нарушение бизнес-логики."""
    pass