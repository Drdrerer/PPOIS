import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import math

from model import ScheduleModel
from SearchDialog import SearchDialog
from DeleteDialog import DeleteDialog
from AddRecordDialog import AddRecordDialog

class AppController:
    def __init__(self, root):
        self.root = root
        self.root.title("Справочник железнодорожных рейсов")
        self.root.geometry("900x600")
        
        self.model = ScheduleModel()
        
        self.records_per_page = 10
        self.current_page = 1
        
        self.setup_ui()
        self.update_table()

    def setup_ui(self):
        self.setup_menu()
        self.setup_toolbar()
        self.setup_table()
        self.setup_pagination()

    def setup_menu(self):
        """Создание верхнего меню"""
        menubar = tk.Menu(self.root)
        
        file_menu = tk.Menu(menubar, tearoff=0)
        file_menu.add_command(label="Загрузить (SAX)", command=self.load_file)
        file_menu.add_command(label="Сохранить (DOM)", command=self.save_file)
        file_menu.add_separator()
        file_menu.add_command(label="Выход", command=self.root.quit)
        menubar.add_cascade(label="Файл", menu=file_menu)
        
        edit_menu = tk.Menu(menubar, tearoff=0)
        edit_menu.add_command(label="Добавить запись", command=self.show_add_dialog)
        edit_menu.add_command(label="Поиск записей", command=self.show_search_dialog)
        edit_menu.add_command(label="Удаление записей", command=self.show_delete_dialog)
        menubar.add_cascade(label="Правка", menu=edit_menu)
        
        self.root.config(menu=menubar)

    def setup_toolbar(self):
        """Создание панели инструментов (дублирует меню)"""
        toolbar = tk.Frame(self.root, bd=1, relief=tk.RAISED)
        toolbar.pack(side=tk.TOP, fill=tk.X)
        
        tk.Button(toolbar, text="Загрузить", command=self.load_file).pack(side=tk.LEFT, padx=2, pady=2)
        tk.Button(toolbar, text="Сохранить", command=self.save_file).pack(side=tk.LEFT, padx=2, pady=2)
        tk.Button(toolbar, text="Добавить", command=self.show_add_dialog).pack(side=tk.LEFT, padx=2, pady=2)
        tk.Button(toolbar, text="Поиск", command=self.show_search_dialog).pack(side=tk.LEFT, padx=2, pady=2)
        tk.Button(toolbar, text="Удалить", command=self.show_delete_dialog).pack(side=tk.LEFT, padx=2, pady=2)

    def setup_table(self):
        """Создание таблицы для вывода записей"""
        columns = ("train_num", "dep_station", "arr_station", "dep_time", "arr_time", "travel_time")
        self.tree = ttk.Treeview(self.root, columns=columns, show="headings")
        
        self.tree.heading("train_num", text="№ поезда")
        self.tree.heading("dep_station", text="Ст. отправления")
        self.tree.heading("arr_station", text="Ст. прибытия")
        self.tree.heading("dep_time", text="Время отправления")
        self.tree.heading("arr_time", text="Время прибытия")
        self.tree.heading("travel_time", text="Время в пути")
        
        for col in columns:
            self.tree.column(col, width=130, anchor=tk.CENTER)
            
        self.tree.pack(expand=True, fill=tk.BOTH, padx=10, pady=10)

    def setup_pagination(self):
        """Создание элементов управления страницами"""
        pag_frame = tk.Frame(self.root)
        pag_frame.pack(side=tk.BOTTOM, fill=tk.X, pady=5)
        
        tk.Button(pag_frame, text="<< В начало", command=self.first_page).pack(side=tk.LEFT, padx=5)
        tk.Button(pag_frame, text="< Назад", command=self.prev_page).pack(side=tk.LEFT, padx=5)
        
        self.page_info = tk.Label(pag_frame, text="Страница 1 из 1 | Всего записей: 0")
        self.page_info.pack(side=tk.LEFT, padx=10)
        
        tk.Button(pag_frame, text="Вперед >", command=self.next_page).pack(side=tk.LEFT, padx=5)
        tk.Button(pag_frame, text="В конец >>", command=self.last_page).pack(side=tk.LEFT, padx=5)
        
        tk.Label(pag_frame, text="Записей на стр:").pack(side=tk.LEFT, padx=(20, 2))
        self.per_page_var = tk.StringVar(value=str(self.records_per_page))
        self.page_size_combo = ttk.Combobox(pag_frame, textvariable=self.per_page_var, values=["5", "10", "20", "50"], width=5, state="readonly")
        self.page_size_combo.pack(side=tk.LEFT)
        self.page_size_combo.bind("<<ComboboxSelected>>", self.change_per_page)
    
    @property
    def total_pages(self):
        return max(1, math.ceil(len(self.model.records) / self.records_per_page))

    def update_table(self):
        """Обновление данных в таблице с учетом текущей страницы"""
        for item in self.tree.get_children():
            self.tree.delete(item)
            
        start = (self.current_page - 1) * self.records_per_page
        end = start + self.records_per_page
        page_data = self.model.records[start:end]
        
        for rec in page_data:
            self.tree.insert("", tk.END, values=(
                rec.train_num, 
                rec.station_dep, 
                rec.station_arr, 
                rec.dt_dep.strftime("%Y-%m-%d %H:%M"), 
                rec.dt_arr.strftime("%Y-%m-%d %H:%M"), 
                str(rec.travel_time)
            ))
            
        self.page_info.config(text=f"Страница {self.current_page} из {self.total_pages} | Всего записей: {len(self.model.records)}")

    def change_per_page(self, event):
        self.records_per_page = int(self.per_page_var.get())
        self.current_page = 1
        self.update_table()

    def first_page(self): 
        self.current_page = 1
        self.update_table()
        
    def prev_page(self): 
        if self.current_page > 1: 
            self.current_page -= 1
            self.update_table()
            
    def next_page(self): 
        if self.current_page < self.total_pages: 
            self.current_page += 1
            self.update_table()
            
    def last_page(self): 
        self.current_page = self.total_pages
        self.update_table()

    
    def load_file(self):
        filepath = filedialog.askopenfilename(filetypes=[("XML files", "*.xml")])
        if filepath:
            try:
                self.model.load_from_xml(filepath)
                self.current_page = 1
                self.update_table()
                messagebox.showinfo("Успех", "Данные успешно загружены (SAX-парсер).")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Ошибка чтения файла:\n{e}")

    def save_file(self):
        filepath = filedialog.asksaveasfilename(defaultextension=".xml", filetypes=[("XML files", "*.xml")])
        if filepath:
            try:
                self.model.save_to_xml(filepath)
                messagebox.showinfo("Успех", "Данные успешно сохранены (DOM-парсер).")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Ошибка записи файла:\n{e}")

    def show_add_dialog(self):
        AddRecordDialog(self.root, self)

    def show_search_dialog(self):
        SearchDialog(self.root, self.model)

    def show_delete_dialog(self):
        DeleteDialog(self.root, self)