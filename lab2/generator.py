import random
from datetime import datetime, timedelta
from model import ScheduleModel, TrainRecord

def generate_dummy_data():
    stations = ["Минск", "Брест", "Гомель", "Витебск", "Могилев", "Гродно", "Барановичи", "Орша"]
    model = ScheduleModel()
    
    base_time = datetime.now().replace(second=0, microsecond=0)
    
    for i in range(1, 61):
        train_num = f"{random.randint(100, 999)}{random.choice(['А', 'Б', 'В'])}"
        dep_station = random.choice(stations)
        arr_station = random.choice([s for s in stations if s != dep_station])
        
        dep_time = base_time + timedelta(days=random.randint(0, 30), hours=random.randint(0, 23), minutes=random.randint(0, 59))
        
        travel_hours = random.randint(2, 8)
        travel_minutes = random.choice([0, 15, 30, 45])
        arr_time = dep_time + timedelta(hours=travel_hours, minutes=travel_minutes)
        
        record = TrainRecord(
            train_num, 
            dep_station, 
            arr_station, 
            dep_time.strftime("%Y-%m-%d %H:%M"), 
            arr_time.strftime("%Y-%m-%d %H:%M")
        )
        model.add_record(record)
        
    model.save_to_xml("C:/Users/Egor/Desktop/work/aois/lab2/test_schedule.xml")
    print("test_schedule.xml успешно сгенерирован!")

if __name__ == "__main__":
    generate_dummy_data()