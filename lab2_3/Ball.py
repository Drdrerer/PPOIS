import pygame
import random
import Particle

class Ball:
    def __init__(self, skin=None):
        self.radius = Particle.CONFIG['entities']['ball']['radius']
        self.rect = pygame.Rect(Particle.WIDTH//2, Particle.HEIGHT//2, self.radius*2, self.radius*2)
        self.speed_x, self.speed_y = Particle.CONFIG['entities']['ball']['speed_x'], Particle.CONFIG['entities']['ball']['speed_y']
        self.skin = skin
        self.angle = 0 

    def move(self, particles, b_skin):
        particles.append(Particle.Particle(self.rect.x, self.rect.y, b_skin, is_trail=True))
        self.rect.x += self.speed_x
        self.rect.y += self.speed_y
        self.angle += (abs(self.speed_x) + abs(self.speed_y)) 
        if self.rect.top <= 0 or self.rect.bottom >= Particle.HEIGHT: self.speed_y *= -1

    def reset(self, direction):
        self.rect.center = (Particle.WIDTH // 2, Particle.HEIGHT // 2)
        self.speed_x = Particle.CONFIG['entities']['ball']['speed_x'] * direction
        self.speed_y = Particle.CONFIG['entities']['ball']['speed_y'] * random.choice([-1, 1])
        self.angle = 0

    def draw(self, surface):
        if self.skin:
            rotated_skin = pygame.transform.rotate(self.skin, self.angle)
            new_rect = rotated_skin.get_rect(center=self.rect.center)
            surface.blit(rotated_skin, new_rect.topleft)
        else: pygame.draw.ellipse(surface, (240, 240, 240), self.rect)