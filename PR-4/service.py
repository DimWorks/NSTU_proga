from flask import Flask, render_template, request, redirect
from urllib.parse import quote
import socket
import datetime
import json

class JSONCreator:
    def __init__(self, filename):
        self.filename = filename
        self.data = self.load_data()

    def load_data(self):
        try:
            with open(self.filename, 'r') as file:
                return json.load(file)
        except (FileNotFoundError, json.JSONDecodeError):
            return []

    def add_data(self, url, ip, time):
        if isinstance(time, datetime.datetime):
            time = time.strftime('%Y-%m-%d %H:%M:%S')
        data_entry = {"URL": url, "IP": ip, "Time": time}
        self.data.append(data_entry)

    def create_json(self):
        with open(self.filename, 'w') as file:
            json.dump(self.data, file)

def reduction(text):     
    # Добиваем строку, до кратности 8-ми
    while ((len(text) % 8) != 0):
        text += "#"
 
    output = ['\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0']
    # Определяем размер блоков
    length = len(text) // 8

    for i in range(0, 9):
        res = 0
        for j in range(0, (length * i)):
            res += ord(text[j]) * ord(text[j]) * j

        res %= 1000
        resulto = 0

        while (res > 0):
            resulto += res % 10
            res //= 10
   
        resulto += 65

        if resulto > 90:
            resulto -= 4
        output[i - 1] = chr(resulto)

    return ''.join(output)

app = Flask(__name__)
server_address = ('127.0.0.1', 5656)


@app.route('/', methods=['GET', 'POST'])
def home():
    generated_link = None
    if request.method == 'POST':
        original_link = request.form['user_input']

        short_link = reduction(original_link)

        # Сохраняем короткую ссылку в базе данных
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            try:
                s.connect(server_address)
                s.sendall(f"PUSH#{short_link}#{original_link}\0'".encode())
                print("Message sent successfully.")
                data = s.recv(1024)
                print(f"Response from server: {data.decode()}")
                s.sendall(f"end".encode())
            except ConnectionRefusedError:
                print("Connection to the server failed.")

        # Возвращаем короткую ссылку
        generated_link = f"http://127.0.0.1:5000/{short_link}"

    return render_template('index.html', output_link=generated_link)

@app.route('/<short_link>')
def redirect_to_original(short_link):
    if short_link == 'favicon.ico':
        return "Not Found"
    
    # Получаем оригинальную ссылку из базы данных
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect(server_address)
            s.sendall(f"GET#{short_link}\0".encode())
            data = s.recv(1024)
            original_link = data.decode()
            #print("catch: " + original_link + "|end")
            s.sendall(f"end".encode())
        except ConnectionRefusedError:
            print("Connection to the server failed.")
            return "Internal Server Error"

    # Открытие оригинальной ссылки
    if original_link != "NOT_FOUND":
        json_creator = JSONCreator('statistic.json')
        json_creator.add_data(original_link + "(" + short_link+ ")", request.environ['REMOTE_ADDR'], datetime.datetime.now().replace(microsecond=0))
        json_creator.create_json()
        return redirect(original_link)        
    else:
        return render_template('!index.html')


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000, debug=True)