import pygame
import random
import json
import sys
import os

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
def get_path(filename):
    return os.path.join(BASE_DIR, filename)

try:
    with open(get_path('config.json'), 'r', encoding='utf-8') as f:
        CONFIG = json.load(f)
except FileNotFoundError:
    print("Критическая ошибка: config.json не найден!")
    sys.exit()

WIDTH, HEIGHT = CONFIG['screen']['width'], CONFIG['screen']['height']
FPS = CONFIG['screen']['fps']

class Particle:
    def __init__(self, x, y, image=None, color=(255,255,255), is_trail=False):
        self.x, self.y = x, y
        self.image = image
        self.color = color
        self.vx = random.uniform(-5, 5) if not is_trail else 0
        self.vy = random.uniform(-5, 5) if not is_trail else 0
        self.lifetime = 255
        self.fade_speed = 15 if is_trail else 8

    def update(self):
        self.x += self.vx; self.y += self.vy
        self.lifetime -= self.fade_speed

    def draw(self, surface):
        if self.lifetime <= 0: return
        if self.image:
            temp_img = self.image.copy()
            temp_img.set_alpha(self.lifetime)
            surface.blit(temp_img, (self.x, self.y))
        else:
            s = pygame.Surface((5, 5), pygame.SRCALPHA)
            pygame.draw.rect(s, (*self.color, self.lifetime), s.get_rect())
            surface.blit(s, (self.x, self.y))