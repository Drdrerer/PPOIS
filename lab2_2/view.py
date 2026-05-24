import math

class Paginator:
    def __init__(self, data_list, records_per_page=10):
        self.data_list = data_list
        self.records_per_page = records_per_page
        self.current_page = 1

    @property
    def total_pages(self):
        return max(1, math.ceil(len(self.data_list) / self.records_per_page))

    def get_current_page_data(self):
        start = (self.current_page - 1) * self.records_per_page
        end = start + self.records_per_page
        return self.data_list[start:end]

    def next_page(self):
        if self.current_page < self.total_pages:
            self.current_page += 1

    def prev_page(self):
        if self.current_page > 1:
            self.current_page -= 1

    def first_page(self):
        self.current_page = 1

    def last_page(self):
        self.current_page = self.total_pages