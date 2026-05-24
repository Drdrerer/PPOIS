import unittest
import coverage
import os
import tempfile
import tkinter as tk
from unittest.mock import patch, MagicMock

# 1. Инициализация покрытия
_cov = coverage.Coverage(source=['AppController', 'SearchDialog', 'DeleteDialog', 'AddRecordDialog', 'model', 'view'])
_cov.start()

from AppController import AppController
from SearchDialog import SearchDialog
from DeleteDialog import DeleteDialog
from AddRecordDialog import AddRecordDialog   
from model import TrainRecord, ScheduleModel
from view import Paginator

class TestFinalSprint(unittest.TestCase):
    def setUp(self):
        self.root = tk.Tk()
        self.root.withdraw()
        self.app = AppController(self.root)
        self.model = self.app.model
        # Базовые данные для тестов поиска
        self.model.add_record(TrainRecord("101", "Минск", "Брест", "2026-05-14 10:00", "2026-05-14 14:00"))
        self.model.add_record(TrainRecord("202", "Гомель", "Витебск", "2026-05-15 08:00", "2026-05-15 12:00"))

    def tearDown(self):
        self.root.destroy()

    def test_direct_dialog_coverage(self):
        """Прямое покрытие классов диалогов (строки 13-75 в main.py)"""
        # Тест AddRecordDialog
        add_dlg = AddRecordDialog(self.root, self.app)
        add_dlg.entry_num.insert(0, "303")
        with patch('tkinter.messagebox.showinfo'):
            add_dlg.save_record()
        add_dlg.destroy()

        # Тест SearchDialog + пагинация внутри (строки 335-348)
        search_dlg = SearchDialog(self.root, self.model)
        search_dlg.perform_search()
        search_dlg.next_page()
        search_dlg.prev_page()
        search_dlg.destroy()

        # Тест DeleteDialog (строки 351-362)
        del_dlg = DeleteDialog(self.root, self.app)
        del_dlg.entry_del.insert(0, "101")
        with patch('tkinter.messagebox.showinfo'):
            del_dlg.execute_delete()
        del_dlg.destroy()

    def test_model_and_view_final(self):
        """Закрытие model.py (строка 108) и view.py (100%)"""
        # match = False ветка в поиске
        self.model.search_records(train_num="101", dep_station="Гомель")
        
        # XML логика
        with tempfile.NamedTemporaryFile(delete=False, suffix=".xml") as tmp:
            path = tmp.name
        try:
            self.model.save_to_xml(path)
            self.model.load_from_xml(path)
        finally:
            if os.path.exists(path): os.remove(path)

    def test_main_logic_and_errors(self):
        """Ошибки файлов и контроллер (строки 126, 171, 181)"""
        # Ошибка загрузки
        with patch('tkinter.filedialog.askopenfilename', return_value="err.xml"):
            with patch('model.ScheduleModel.load_from_xml', side_effect=Exception):
                with patch('tkinter.messagebox.showerror'):
                    self.app.load_file()
        
        # Навигация контроллера
        self.app.next_page()
        self.app.last_page()
        self.app.first_page()
        
        # Комбобокс
        with patch.object(self.app.page_size_combo, 'get', return_value="50"):
            self.app.change_per_page(None)

if __name__ == "__main__":
    try:
        unittest.main(exit=False)
    finally:
        _cov.stop()
        _cov.save()
        print("\n" + "="*60 + "\nИТОГОВОЕ ПОКРЫТИЕ\n" + "="*60)
        _cov.report(show_missing=True)