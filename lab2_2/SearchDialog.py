import tkinter as tk
from tkinter import ttk
from view import Paginator

class SearchDialog(tk.Toplevel):
    def __init__(self, parent, model):
        super().__init__(parent)
        self.title("Поиск записей")
        self.geometry("700x500")
        self.model = model
        self.paginator = Paginator([], records_per_page=5)

        # Панель поиска
        search_frame = tk.Frame(self)
        search_frame.pack(fill=tk.X, padx=10, pady=10)
        
        ttk.Label(search_frame, text="№ поезда:").pack(side=tk.LEFT, padx=5)
        self.search_num = ttk.Entry(search_frame, width=10)
        self.search_num.pack(side=tk.LEFT, padx=5)
        
        ttk.Label(search_frame, text="Ст. отправления:").pack(side=tk.LEFT, padx=5)
        self.search_dep = ttk.Entry(search_frame, width=15)
        self.search_dep.pack(side=tk.LEFT, padx=5)
        
        ttk.Button(search_frame, text="Искать", command=self.perform_search).pack(side=tk.LEFT, padx=15)

        columns = ("train_num", "dep_station", "arr_station", "dep_time", "arr_time")
        self.tree = ttk.Treeview(self, columns=columns, show="headings", height=10)
        self.tree.heading("train_num", text="№")
        self.tree.heading("dep_station", text="Откуда")
        self.tree.heading("arr_station", text="Куда")
        self.tree.heading("dep_time", text="Отправление")
        self.tree.heading("arr_time", text="Прибытие")
        
        for col in columns:
            self.tree.column(col, width=100, anchor=tk.CENTER)
        self.tree.pack(expand=True, fill=tk.BOTH, padx=10, pady=5)

        pag_frame = tk.Frame(self)
        pag_frame.pack(side=tk.BOTTOM, fill=tk.X, pady=10)
        
        ttk.Button(pag_frame, text="< Назад", command=self.prev_page).pack(side=tk.LEFT, padx=10)
        self.lbl_page = ttk.Label(pag_frame, text="Страница 0 из 0")
        self.lbl_page.pack(side=tk.LEFT, expand=True)
        ttk.Button(pag_frame, text="Вперед >", command=self.next_page).pack(side=tk.RIGHT, padx=10)

    def perform_search(self):
        kwargs = {}
        if self.search_num.get():
            kwargs['train_num'] = self.search_num.get()
        if self.search_dep.get():
            kwargs['dep_station'] = self.search_dep.get()
            
        results = self.model.search_records(**kwargs)
        
        self.paginator = Paginator(results, records_per_page=5)
        self.update_results_table()

    def update_results_table(self):
        for item in self.tree.get_children():
            self.tree.delete(item)
            
        for rec in self.paginator.get_current_page_data():
            self.tree.insert("", tk.END, values=(
                rec.train_num, rec.station_dep, rec.station_arr, 
                rec.dt_dep.strftime("%Y-%m-%d %H:%M"), rec.dt_arr.strftime("%Y-%m-%d %H:%M")
            ))
            
        self.lbl_page.config(text=f"Страница {self.paginator.current_page} из {self.paginator.total_pages} | Найдено: {len(self.paginator.data_list)}")

    def prev_page(self):
        self.paginator.prev_page()
        self.update_results_table()

    def next_page(self):
        self.paginator.next_page()
        self.update_results_table()
