import pygame
import Particle

class Paddle:
    def __init__(self, x, y, skin=None):
        self.rect = pygame.Rect(x, y, Particle.CONFIG['entities']['paddle']['width'], Particle.CONFIG['entities']['paddle']['height'])
        self.speed = Particle.CONFIG['entities']['paddle']['speed']
        self.score = 0
        self.skin = skin
        self.trail_timer = 0

    def move(self, up, down):
        if up and self.rect.top > 0: self.rect.y -= self.speed
        if down and self.rect.bottom < Particle.HEIGHT: self.rect.y += self.speed

    def draw(self, surface, particles, p_skin):
        self.trail_timer += 1
        if self.trail_timer % 3 == 0:
            particles.append(Particle.Particle(self.rect.x, self.rect.y, p_skin, is_trail=True))
        if self.skin: surface.blit(self.skin, self.rect)
        else: pygame.draw.rect(surface, (240, 240, 240), self.rect, border_radius=3)