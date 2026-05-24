import tkinter as tk
from tkinter import ttk, messagebox

class DeleteDialog(tk.Toplevel):
    def __init__(self, parent, controller):
        super().__init__(parent)
        self.title("Удаление записей")
        self.geometry("300x150")
        self.controller = controller

        ttk.Label(self, text="Удалить по номеру поезда:").pack(pady=(15, 5))
        self.entry_del = ttk.Entry(self)
        self.entry_del.pack()

        ttk.Button(self, text="Удалить", command=self.execute_delete).pack(pady=15)

    def execute_delete(self):
        t_num = self.entry_del.get()
        if not t_num:
            messagebox.showwarning("Внимание", "Введите номер поезда для удаления")
            return
            
        count = self.controller.model.delete_records(train_num=t_num)
        if count > 0:
            messagebox.showinfo("Результат", f"Успешно удалено записей: {count}")
            self.controller.current_page = 1
            self.controller.update_table()
            self.destroy()
        else:
            messagebox.showinfo("Результат", "Записи с указанными параметрами не найдены.")
