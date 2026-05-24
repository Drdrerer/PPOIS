import pygame
import json
import sys
import os
import Particle
from UDPNetwork import UDPNetwork
from Paddle import Paddle
from Ball import Ball

class PongGame:
    def __init__(self):
        pygame.init()
        pygame.mixer.init()
        self.screen = pygame.display.set_mode((Particle.WIDTH, Particle.HEIGHT))
        pygame.display.set_caption(Particle.CONFIG['screen']['title'])
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont("Verdana", 24)
        self.big_font = pygame.font.SysFont("Verdana", 50, bold=True)
        self.game_over_processed = False
        
        self.state = "MENU"
        self.game_mode = "BOT" 
        self.network = None
        
        self.player_name = ""
        self.input_ip = "127.0.0.1" 
        self.difficulty_label = "Средне"
        self.difficulty_mult = Particle.CONFIG['difficulty']['medium']
        self.start_time = 0
        self.final_time_str = ""
        self.particles = []
        
        self.load_assets()
        self.init_entities()

    def load_assets(self):
        self.sounds = {}
        sound_keys = ['hit_sound', 'boom_sound', 'win_sound', 'lose_sound', 'click_sound']
        for key in sound_keys:
            try: self.sounds[key] = pygame.mixer.Sound(Particle.get_path(Particle.CONFIG['paths'][key]))
            except: self.sounds[key] = None

        try:
            pygame.mixer.music.load(Particle.get_path(Particle.CONFIG['paths']['bg_music']))
            pygame.mixer.music.set_volume(0.3)
            pygame.mixer.music.play(-1)
        except: pass

        self.skins = {}
        skin_keys = ['skin_paddle', 'skin_ball', 'skin_bg', 'skin_p_trail', 'skin_b_trail', 'skin_boom']
        for key in skin_keys:
            try:
                img = pygame.image.load(Particle.get_path(Particle.CONFIG['paths'][key])).convert_alpha()
                if key == 'skin_paddle':
                    w, h = Particle.CONFIG['entities']['paddle']['width'], Particle.CONFIG['entities']['paddle']['height']
                    img = pygame.transform.scale(img, (w, h))
                    self.skins['skin_paddle_player'] = img
                    self.skins['skin_paddle_bot'] = pygame.transform.flip(img, True, False)
                elif key == 'skin_ball': 
                    self.skins[key] = pygame.transform.scale(img, (Particle.CONFIG['entities']['ball']['radius']*2, Particle.CONFIG['entities']['ball']['radius']*2))
                elif key == 'skin_bg': 
                    self.skins[key] = pygame.transform.scale(img, (Particle.WIDTH, Particle.HEIGHT))
                elif 'trail' in key or 'boom' in key: 
                    self.skins[key] = pygame.transform.scale(img, (15, 15))
                else: self.skins[key] = img
            except: self.skins[key] = None

    def init_entities(self):
        p_w, p_h = Particle.CONFIG['entities']['paddle']['width'], Particle.CONFIG['entities']['paddle']['height']
        self.player = Paddle(30, Particle.HEIGHT // 2 - p_h//2, self.skins.get('skin_paddle_player'))
        self.bot = Paddle(Particle.WIDTH - 30 - p_w, Particle.HEIGHT // 2 - p_h//2, self.skins.get('skin_paddle_bot'))
        self.ball = Ball(self.skins.get('skin_ball'))

    def format_time(self, ms):
        seconds = ms // 1000
        return f"{seconds // 60:02d}:{seconds % 60:02d}"

    def load_records(self):
        path = Particle.get_path(Particle.CONFIG['paths']['records'])
        if not os.path.exists(path): return []
        try:
            with open(path, 'r', encoding='utf-8') as f: return json.load(f)
        except: return []

    def save_record(self):
        if self.game_mode != "BOT": 
            self.state = "GAME_OVER"
            return

        recs = self.load_records()
        recs.append({"name": self.player_name.strip() or "Игрок", "score": self.player.score, "difficulty": self.difficulty_label, "time": self.final_time_str})
        weights = {"Сложно": 3, "Средне": 2, "Легко": 1}
        def sort_key(entry):
            try: m, s = map(int, entry['time'].split(':')); t = m * 60 + s
            except: t = 99999
            return (-weights.get(entry['difficulty'], 0), -entry['score'], t)
        
        recs = sorted(recs, key=sort_key)[:5]
        with open(Particle.get_path(Particle.CONFIG['paths']['records']), 'w', encoding='utf-8') as f:
            json.dump(recs, f, indent=4, ensure_ascii=False)
        self.state = "RECORDS"

    def create_explosion(self, pos):
        if self.sounds['boom_sound']: self.sounds['boom_sound'].play()
        for _ in range(20): self.particles.append(Particle.Particle(pos[0], pos[1], self.skins.get('skin_boom'), color=(255, 50, 50)))

    def start_game_session(self):
        """Инициализация новой игровой сессии против бота"""
        self.game_mode = "BOT"
        self.game_over_processed = False
        self.init_entities()
        self.player.score = 0
        self.bot.score = 0
        self.particles = []
        self.start_time = pygame.time.get_ticks()
        self.state = "PLAYING"
        print(f"Игра началась! Сложность: {self.difficulty_label}")

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                if self.network: self.network.close()
                pygame.quit(); sys.exit()

            if event.type == pygame.KEYDOWN:
                if self.state != "PLAYING" and self.sounds.get('click_sound'):
                    self.sounds['click_sound'].play()

                if self.state == "INPUT_NAME":
                    if event.key == pygame.K_RETURN:
                        if len(self.player_name.strip()) > 0: self.save_record()
                    elif event.key == pygame.K_BACKSPACE:
                        self.player_name = self.player_name[:-1]
                    elif len(self.player_name) < 12 and event.unicode.isprintable():
                        self.player_name += event.unicode
                    continue

                elif self.state == "INPUT_IP":
                    if event.key == pygame.K_RETURN:
                        self.network = UDPNetwork()
                        self.network.connect(self.input_ip)
                        self.game_mode = "ONLINE_CLIENT"
                        self.state = "WAITING"
                    elif event.key == pygame.K_BACKSPACE:
                        self.input_ip = self.input_ip[:-1]
                    elif event.key == pygame.K_ESCAPE:
                        self.state = "ONLINE_MENU" 
                    elif len(self.input_ip) < 15 and event.unicode.isprintable():
                        self.input_ip += event.unicode
                    continue

                if self.state == "MENU":
                    if event.key == pygame.K_1: self.state = "MODE_SELECT"
                    elif event.key == pygame.K_2: self.state = "RECORDS"
                    elif event.key == pygame.K_3: self.state = "HELP"
                    elif event.key == pygame.K_4: pygame.quit(); sys.exit()

                elif self.state == "MODE_SELECT":
                    if event.key == pygame.K_1: self.state = "DIFFICULTY"
                    elif event.key == pygame.K_2: self.state = "ONLINE_MENU"
                    elif event.key == pygame.K_ESCAPE: self.state = "MENU"

                elif self.state == "ONLINE_MENU":
                    if event.key == pygame.K_1:
                        self.network = UDPNetwork()
                        self.network.host()
                        self.game_mode = "ONLINE_HOST"
                        self.state = "WAITING"
                    elif event.key == pygame.K_2: self.state = "INPUT_IP"
                    elif event.key == pygame.K_ESCAPE: self.state = "MODE_SELECT"

                elif self.state == "DIFFICULTY":
                    if event.key == pygame.K_1: 
                        self.difficulty_mult = Particle.CONFIG['difficulty']['easy']
                        self.difficulty_label = "Легко"
                        self.start_game_session()
                    elif event.key == pygame.K_2: 
                        self.difficulty_mult = Particle.CONFIG['difficulty']['medium']
                        self.difficulty_label = "Средне"
                        self.start_game_session()
                    elif event.key == pygame.K_3: 
                        self.difficulty_mult = Particle.CONFIG['difficulty']['hard']
                        self.difficulty_label = "Сложно"
                        self.start_game_session()
                    elif event.key == pygame.K_ESCAPE: 
                        self.state = "MODE_SELECT"

                elif self.state in ["WAITING", "DIFFICULTY", "RECORDS", "HELP", "GAME_OVER"]:
                    if event.key == pygame.K_ESCAPE:
                        if self.network:
                            self.network.close()
                            self.network = None
                        
                        self.init_entities()
                        self.state = "MENU"

    def update(self):
        if self.state == "WAITING" and self.network:
            self.network.send_data({"status": "waiting_ack", "state": "WAITING"})
            
            data = self.network.receive_data()
            if self.network.connected:
                self.state = "PLAYING"
                self.start_time = pygame.time.get_ticks()
                self.player.score = 0
                self.bot.score = 0

        elif self.state == "PLAYING":
            keys = pygame.key.get_pressed()
            
            if self.game_mode == "BOT":
                self.player.move(keys[pygame.K_w] or keys[pygame.K_UP], keys[pygame.K_s] or keys[pygame.K_DOWN])
                bot_speed = self.player.speed * self.difficulty_mult
                if self.bot.rect.centery < self.ball.rect.centery: self.bot.rect.y += bot_speed
                else: self.bot.rect.y -= bot_speed
                self.ball.move(self.particles, self.skins.get('skin_b_trail'))

            elif self.game_mode == "ONLINE_HOST" and self.network:
                self.player.move(keys[pygame.K_w] or keys[pygame.K_UP], keys[pygame.K_s] or keys[pygame.K_DOWN])
                self.ball.move(self.particles, self.skins.get('skin_b_trail'))
                
                data = self.network.receive_data()
                if data and "p2" in data: 
                    self.bot.rect.y = data["p2"]

            elif self.game_mode == "ONLINE_CLIENT" and self.network:
                self.bot.move(keys[pygame.K_w] or keys[pygame.K_UP], keys[pygame.K_s] or keys[pygame.K_DOWN])
                self.network.send_data({"p2": self.bot.rect.y})
                
                data = self.network.receive_data()
                if data:
                    if data.get("state") == "GAME_OVER":
                        self.state = "GAME_OVER"
                    
                    if "b_x" in data:
                        self.ball.rect.x = data["b_x"]
                        self.ball.rect.y = data["b_y"]
                        self.ball.angle = data.get("a", 0)
                        self.particles.append(Particle.Particle(self.ball.rect.x, self.ball.rect.y, self.skins.get('skin_b_trail'), is_trail=True))
                    if "p1" in data: self.player.rect.y = data["p1"]
                    if "s1" in data: 
                        self.player.score = data["s1"]
                        self.bot.score = data["s2"]
                    if "t" in data: self.start_time = pygame.time.get_ticks() - data["t"]

            if self.game_mode != "ONLINE_CLIENT":
                if self.ball.rect.colliderect(self.player.rect) and self.ball.speed_x < 0:
                    self.ball.speed_x *= -1.05
                    self.ball.rect.left = self.player.rect.right 
                    if self.sounds['hit_sound']: self.sounds['hit_sound'].play()

                if self.ball.rect.colliderect(self.bot.rect) and self.ball.speed_x > 0:
                    self.ball.speed_x *= -1.05
                    self.ball.rect.right = self.bot.rect.left
                    if self.sounds['hit_sound']: self.sounds['hit_sound'].play()

                if self.ball.rect.left <= 0:
                    self.create_explosion(self.ball.rect.center); self.bot.score += 1; self.ball.reset(1)
                elif self.ball.rect.right >= Particle.WIDTH:
                    self.create_explosion(self.ball.rect.center); self.player.score += 1; self.ball.reset(-1)

            if (self.player.score >= 5 or self.bot.score >= 5) and not self.game_over_processed:
                self.game_over_processed = True
                self.final_time_str = self.format_time(pygame.time.get_ticks() - self.start_time)
                
                if (self.game_mode == "BOT" and self.player.score >= 5) or \
                   (self.game_mode == "ONLINE_HOST" and self.player.score >= 5) or \
                   (self.game_mode == "ONLINE_CLIENT" and self.bot.score >= 5):
                    if self.sounds.get('win_sound'): self.sounds['win_sound'].play()
                else:
                    if self.sounds.get('lose_sound'): self.sounds['lose_sound'].play()

                if self.game_mode == "BOT" and self.player.score >= 5: 
                    self.state = "INPUT_NAME"
                else: 
                    self.state = "GAME_OVER"

            if self.game_mode == "ONLINE_HOST" and self.network:
                self.network.send_data({
                    "b_x": self.ball.rect.x, "b_y": self.ball.rect.y, "a": self.ball.angle,
                    "p1": self.player.rect.y, "s1": self.player.score, "s2": self.bot.score,
                    "t": pygame.time.get_ticks() - self.start_time,
                    "state": self.state
                })

        for p in self.particles[:]:
            p.update()
            if p.lifetime <= 0: self.particles.remove(p)

    def draw_text(self, text, font, color, x, y, center=True):
        img = font.render(text, True, color)
        rect = img.get_rect(center=(x, y)) if center else img.get_rect(topleft=(x, y))
        self.screen.blit(img, rect)

    def render(self):
        if self.skins.get('skin_bg'): self.screen.blit(self.skins['skin_bg'], (0,0))
        else: self.screen.fill((15, 15, 25))
        
        if self.state == "MENU":
            self.draw_text("PONG ULTIMATE", self.big_font, (240,240,240), Particle.WIDTH//2, 150)
            self.draw_text("1. ИГРАТЬ", self.font, (240,240,240), Particle.WIDTH//2, 300)
            self.draw_text("2. РЕКОРДЫ", self.font, (240,240,240), Particle.WIDTH//2, 350)
            self.draw_text("3. СПРАВКА", self.font, (240,240,240), Particle.WIDTH//2, 400)
            self.draw_text("4. ВЫХОД", self.font, (255,80,80), Particle.WIDTH//2, 450)

        elif self.state == "MODE_SELECT":
            self.draw_text("ВЫБОР РЕЖИМА", self.big_font, (240,240,240), Particle.WIDTH//2, 150)
            self.draw_text("1. ИГРА С БОТОМ", self.font, (240,240,240), Particle.WIDTH//2, 300)
            self.draw_text("2. ОНЛАЙН", self.font, (60,180,255), Particle.WIDTH//2, 350)
            self.draw_text("ESC - НАЗАД", self.font, (255,80,80), Particle.WIDTH//2, 450)

        elif self.state == "ONLINE_MENU":
            self.draw_text("ОНЛАЙН ИГРА", self.big_font, (60,180,255), Particle.WIDTH//2, 150)
            self.draw_text("1. СОЗДАТЬ ИГРУ (ХОСТ)", self.font, (240,240,240), Particle.WIDTH//2, 300)
            self.draw_text("2. ПОДКЛЮЧИТЬСЯ", self.font, (240,240,240), Particle.WIDTH//2, 350)
            self.draw_text("ESC - НАЗАД", self.font, (255,80,80), Particle.WIDTH//2, 450)

        elif self.state == "WAITING":
            self.draw_text("ОЖИДАНИЕ ИГРОКА...", self.big_font, (60,180,255), Particle.WIDTH//2, 250)
            self.draw_text("ESC - ОТМЕНА", self.font, (255,80,80), Particle.WIDTH//2, 400)

        elif self.state == "INPUT_IP":
            self.draw_text("ПОДКЛЮЧЕНИЕ", self.big_font, (60,180,255), Particle.WIDTH//2, 150)
            self.draw_text("Введите IP Хоста:", self.font, (240,240,240), Particle.WIDTH//2, 250)
            self.draw_text(self.input_ip + "_", self.big_font, (255,255,100), Particle.WIDTH//2, 320)
            self.draw_text("ENTER - ПОДКЛЮЧИТЬСЯ", self.font, (100,255,100), Particle.WIDTH//2, 450)
            self.draw_text("ESC - НАЗАД", self.font, (255,80,80), Particle.WIDTH//2, 500)

        elif self.state == "DIFFICULTY":
            self.draw_text("СЛОЖНОСТЬ БОТА", self.big_font, (240,240,240), Particle.WIDTH//2, 150)
            self.draw_text("1. ЛЕГКО", self.font, (240,240,240), Particle.WIDTH//2, 300)
            self.draw_text("2. СРЕДНЕ", self.font, (240,240,240), Particle.WIDTH//2, 350)
            self.draw_text("3. СЛОЖНО", self.font, (240,240,240), Particle.WIDTH//2, 400)
            self.draw_text("ESC - НАЗАД", self.font, (255,80,80), Particle.WIDTH//2, 500)

        elif self.state == "PLAYING":
            pygame.draw.line(self.screen, (240,240,240), (Particle.WIDTH//2, 0), (Particle.WIDTH//2, Particle.HEIGHT), 1)
            self.draw_text(self.format_time(pygame.time.get_ticks() - self.start_time), self.font, (240,240,240), Particle.WIDTH//2, 30)
            self.draw_text(str(self.player.score), self.big_font, (240,240,240), Particle.WIDTH//4, 80)
            self.draw_text(str(self.bot.score), self.big_font, (240,240,240), Particle.WIDTH*3//4, 80)
            
            if self.game_mode == "ONLINE_CLIENT":
                self.draw_text("ВЫ", self.font, (100,255,100), Particle.WIDTH*3//4, 30)
                self.draw_text("ПРОТИВНИК", self.font, (255,80,80), Particle.WIDTH//4, 30)
            elif self.game_mode == "ONLINE_HOST":
                self.draw_text("ВЫ", self.font, (100,255,100), Particle.WIDTH//4, 30)
                self.draw_text("ПРОТИВНИК", self.font, (255,80,80), Particle.WIDTH*3//4, 30)

            self.player.draw(self.screen, self.particles, self.skins.get('skin_p_trail'))
            self.bot.draw(self.screen, self.particles, self.skins.get('skin_p_trail'))
            self.ball.draw(self.screen)

        elif self.state == "HELP":
            self.draw_text("Выбор - кнопками 1, 2, 3, 4", self.font, (240,240,240), Particle.WIDTH//2, 250)
            self.draw_text("Выход/Назад - esc", self.font, (240,240,240), Particle.WIDTH//2, 300)
            self.draw_text("Управление - W/S или стрелками", self.font, (240,240,240), Particle.WIDTH//2, 350)
            self.draw_text("ESC - НАЗАД", self.font, (255,80,80), Particle.WIDTH//2, 500)

        elif self.state == "INPUT_NAME":
            self.draw_text("НОВЫЙ РЕКОРД!", self.big_font, (255,80,80), Particle.WIDTH//2, 120)
            self.draw_text(f"ИМЯ: {self.player_name}_", self.font, (240,240,240), Particle.WIDTH//2, 340)

        elif self.state in ["RECORDS", "HELP", "GAME_OVER"]:
            if self.state == "GAME_OVER":
                msg = "КОНЕЦ ИГРЫ!"
                if self.game_mode == "BOT": msg = "ПОБЕДА!" if self.player.score > self.bot.score else "ПРОИГРЫШ..."
                elif self.game_mode == "ONLINE_HOST": msg = "ВЫ ПОБЕДИЛИ!" if self.player.score >= 5 else "ВЫ ПРОИГРАЛИ!"
                elif self.game_mode == "ONLINE_CLIENT": msg = "ВЫ ПОБЕДИЛИ!" if self.bot.score >= 5 else "ВЫ ПРОИГРАЛИ!"
                self.draw_text(msg, self.big_font, (255,80,80), Particle.WIDTH//2, 200)
            elif self.state == "RECORDS":
                self.draw_text("РЕКОРДЫ", self.big_font, (240,240,240), Particle.WIDTH//2, 80)
                for i, r in enumerate(self.load_records()):
                    self.draw_text(f"{i+1}. {r['name'][:10]} | {r['score']} | {r.get('difficulty')} | {r.get('time')}", self.font, (240,240,240), Particle.WIDTH//2, 200 + i*40)
            elif self.state == "HELP":
                 self.draw_text("СПРАВКА", self.big_font, (240,240,240), Particle.WIDTH//2, 100)
            
            self.draw_text("ESC - МЕНЮ", self.font, (255,80,80), Particle.WIDTH//2, Particle.HEIGHT - 50)

        for p in self.particles: p.draw(self.screen)
        pygame.display.flip()

    def run(self):
        while True:
            self.handle_events()
            self.update()
            self.render()
            self.clock.tick(Particle.FPS)