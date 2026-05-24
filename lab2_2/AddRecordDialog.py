import tkinter as tk
from tkinter import ttk, messagebox
from tkcalendar import DateEntry
from datetime import datetime

from model import TrainRecord

class AddRecordDialog(tk.Toplevel):
    def __init__(self, parent, controller):
        super().__init__(parent)
        self.title("Добавление записи")
        self.geometry("350x400")
        self.controller = controller
        
        # UI Elements
        ttk.Label(self, text="№ поезда:").pack(pady=(10, 0))
        self.entry_num = ttk.Entry(self)
        self.entry_num.pack()

        ttk.Label(self, text="Ст. отправления:").pack(pady=(5, 0))
        self.entry_dep_st = ttk.Entry(self)
        self.entry_dep_st.pack()

        ttk.Label(self, text="Ст. прибытия:").pack(pady=(5, 0))
        self.entry_arr_st = ttk.Entry(self)
        self.entry_arr_st.pack()

        ttk.Label(self, text="Дата отправления:").pack(pady=(5, 0))
        self.cal_dep = DateEntry(self, width=12, background='darkblue', foreground='white', borderwidth=2, date_pattern='yyyy-mm-dd')
        self.cal_dep.pack()
        
        ttk.Label(self, text="Время отправления (ЧЧ:ММ):").pack(pady=(5, 0))
        self.time_dep = ttk.Entry(self)
        self.time_dep.insert(0, "12:00")
        self.time_dep.pack()

        ttk.Label(self, text="Дата прибытия:").pack(pady=(5, 0))
        self.cal_arr = DateEntry(self, width=12, background='darkblue', foreground='white', borderwidth=2, date_pattern='yyyy-mm-dd')
        self.cal_arr.pack()

        ttk.Label(self, text="Время прибытия (ЧЧ:ММ):").pack(pady=(5, 0))
        self.time_arr = ttk.Entry(self)
        self.time_arr.insert(0, "15:00")
        self.time_arr.pack()

        ttk.Button(self, text="Сохранить", command=self.save_record).pack(pady=15)

    def save_record(self):
        try:
            dt_dep_str = f"{self.cal_dep.get()} {self.time_dep.get()}"
            dt_arr_str = f"{self.cal_arr.get()} {self.time_arr.get()}"
            
            datetime.strptime(dt_dep_str, "%Y-%m-%d %H:%M")
            datetime.strptime(dt_arr_str, "%Y-%m-%d %H:%M")

            new_record = TrainRecord(
                self.entry_num.get(),
                self.entry_dep_st.get(),
                self.entry_arr_st.get(),
                dt_dep_str,
                dt_arr_str
            )
            self.controller.model.add_record(new_record)
            self.controller.update_table()
            self.destroy()
            messagebox.showinfo("Успех", "Запись успешно добавлена!")
        except ValueError:
            messagebox.showerror("Ошибка", "Неверный формат времени. Используйте ЧЧ:ММ.")