import xml.dom.minidom as minidom
import xml.sax
from datetime import datetime

class TrainRecord:
    def __init__(self, train_num, station_dep, station_arr, dt_dep, dt_arr):
        self.train_num = train_num
        self.station_dep = station_dep
        self.station_arr = station_arr
        self.dt_dep = datetime.strptime(dt_dep, "%Y-%m-%d %H:%M")
        self.dt_arr = datetime.strptime(dt_arr, "%Y-%m-%d %H:%M")
    
    @property
    def travel_time(self):
        delta = self.dt_arr - self.dt_dep
        return delta

class TrainSAXHandler(xml.sax.ContentHandler):
    """ SAX парсер для чтения файла """
    def __init__(self):
        self.records = []
        self.current_data = ""
        self.train_num = ""
        self.station_dep = ""
        self.station_arr = ""
        self.dt_dep = ""
        self.dt_arr = ""

    def startElement(self, tag, attributes):
        self.current_data = tag

    def characters(self, content):
        if self.current_data == "TrainNumber":
            self.train_num += content
        elif self.current_data == "DepartureStation":
            self.station_dep += content
        elif self.current_data == "ArrivalStation":
            self.station_arr += content
        elif self.current_data == "DepartureTime":
            self.dt_dep += content
        elif self.current_data == "ArrivalTime":
            self.dt_arr += content

    def endElement(self, tag):
        if tag == "Record":
            record = TrainRecord(
                self.train_num.strip(), self.station_dep.strip(), 
                self.station_arr.strip(), self.dt_dep.strip(), self.dt_arr.strip()
            )
            self.records.append(record)
            self.train_num = self.station_dep = self.station_arr = self.dt_dep = self.dt_arr = ""
        self.current_data = ""

class ScheduleModel:
    def __init__(self):
        self.records = []

    def add_record(self, record):
        self.records.append(record)

    def load_from_xml(self, filepath):
        handler = TrainSAXHandler()
        parser = xml.sax.make_parser()
        parser.setContentHandler(handler)
        parser.parse(filepath)
        self.records = handler.records

    def save_to_xml(self, filepath):
        """ DOM парсер для записи """
        doc = minidom.Document()
        root = doc.createElement("Schedule")
        doc.appendChild(root)

        for rec in self.records:
            record_elem = doc.createElement("Record")
            
            elements = {
                "TrainNumber": rec.train_num,
                "DepartureStation": rec.station_dep,
                "ArrivalStation": rec.station_arr,
                "DepartureTime": rec.dt_dep.strftime("%Y-%m-%d %H:%M"),
                "ArrivalTime": rec.dt_arr.strftime("%Y-%m-%d %H:%M")
            }
            
            for tag_name, text_val in elements.items():
                elem = doc.createElement(tag_name)
                text_node = doc.createTextNode(str(text_val))
                elem.appendChild(text_node)
                record_elem.appendChild(elem)
                
            root.appendChild(record_elem)

        with open(filepath, "w", encoding="utf-8") as f:
            doc.writexml(f, indent="  ", addindent="  ", newl="\n", encoding="utf-8")

    def search_records(self, **kwargs):
        results = []
        for r in self.records:
            match = True
            if 'train_num' in kwargs and kwargs['train_num'] and r.train_num != kwargs['train_num']:
                match = False
            if 'dep_station' in kwargs and kwargs['dep_station'] and r.station_dep != kwargs['dep_station']:
                match = False
            if 'arr_station' in kwargs and kwargs['arr_station'] and r.station_arr != kwargs['arr_station']:
                match = False
            
            if match:
                results.append(r)
        return results

    def delete_records(self, **kwargs):
        to_delete = self.search_records(**kwargs)
        count = len(to_delete)
        for r in to_delete:
            self.records.remove(r)
        return count