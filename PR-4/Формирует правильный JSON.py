import json

class JSONCreator:
    def __init__(self):
        self.data = []

    def add_data(self, url, ip, time):
        data_entry = {"URL": url, "IP": ip, "Time": time}
        self.data.append(data_entry)

    def create_json(self, filename):
        with open(filename, 'w') as file:
            json.dump(self.data, file)

# Пример использования
json_creator = JSONCreator()
json_creator.add_data("https://example.com", "192.168.0.1", "2023-11-26 10:00:00")
json_creator.add_data("https://exaQple.com", "4592.168.0.1", "2893-11-26 10:00:00")
json_creator.create_json('example.json')
