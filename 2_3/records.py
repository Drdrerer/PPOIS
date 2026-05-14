# Чтение рекордов
with open('records.json', 'r') as f:
    records = json.load(f)

# Добавление и сортировка
records.append({"name": player_name, "score": self.player.score - self.bot.score})
records = sorted(records, key=lambda x: x['score'], reverse=True)[:5] # Топ-5

# Сохранение
with open('records.json', 'w') as f:
    json.dump(records, f)