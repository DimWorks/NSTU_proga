import json

def generate_html_report(filename, column_order, html_file):
    # Чтение данных из JSON файла
    with open(filename, 'r') as file:
        data = json.load(file)

    # Создание словарей для хранения количества повторений URL, IP и Time
    url_count = {}
    ip_count = {}
    time_count = {}

    
    
    # Подсчет количества повторений URL, IP и Time
    for entry in data:
        url = entry["URL"]
        ip = entry["IP"]
        time = entry["Time"]
        
        url_count[url] = url_count.get(url, 0) + 1
        ip_count[ip] = ip_count.get(ip, 0) + 1
        time_count[time] = time_count.get(time, 0) + 1
    
    # Создание HTML таблицы
    html = "<h1 align='center'>Отчёт</h1><table align='center' border='1'>"
    html += "<tr>"
    
    # Создание заголовков таблицы в заданном пользователем порядке
    for column in column_order:
        html += f"<th>{column}</th>"
    
    html += "</tr>"
    
    # Вывод уникальных значений URL, IP и Time и их количества повторений
    for url, count in url_count.items():
        html += "<tr>"
        
        # Вывод URL, IP и Time только один раз для каждого уникального значения
        html += f"<td rowspan='{count}'>{url}</td>"
        
        ips = [entry["IP"] for entry in data if entry["URL"] == url]
        unique_ips = list(set(ips))
        
        for i, ip in enumerate(unique_ips):
            if i > 0:
                html += "<tr>"
            
            # Вывод IP и соответствующего времени для каждого уникального значения
            html += f"<td rowspan='{ips.count(ip)}'>{ip}</td>"
            
            times = [entry["Time"] for entry in data if entry["URL"] == url and entry["IP"] == ip]
            unique_times = list(set(times))
            
            for j, time in enumerate(unique_times):
                if j > 0:
                    html += "<tr>"
                
                html += f"<td>{time}</td>"
                html += "</tr>"

        html += f'<tr><td>{count}</td><td>{ips.count(ip)}</td><td>{enumerate(unique_times)}</td></tr>'
    
    html += "</table>"
    # Сохраняем HTML отчет в файл
    with open(html_file, 'w') as f:
        f.write(html)

# Пример использования


# Порядок столбцов
column_order = ["URL", "IP", "Time"]

generate_html_report("statistic.json", column_order, "test.html")


