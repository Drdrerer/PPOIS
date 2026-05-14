import json
import socket

class UDPNetwork:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setblocking(False)
        self.target_addr = None 
        self.port = 5005 
        self.is_host = False
        self.connected = False

    def host(self):
        self.is_host = True
        try:
            self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.sock.bind(('0.0.0.0', self.port))
        except: pass
        self.connected = False

    def connect(self, ip):
        self.is_host = False
        self.target_addr = (ip, self.port)
        self.connected = False

    def send_data(self, data):
        if self.target_addr:
            try:
                msg = json.dumps(data).encode('utf-8')
                self.sock.sendto(msg, self.target_addr)
            except: pass

    def receive_data(self):
        last_data = None
        while True:
            try:
                data, addr = self.sock.recvfrom(1024)
                self.connected = True 
                
                if self.is_host:
                    self.target_addr = addr
                
                last_data = json.loads(data.decode('utf-8'))
            except:
                break
        return last_data
    
    def close(self):
        try:
            if hasattr(self, 'sock') and self.sock:
                self.sock.close()
                print("[СЕТЬ] Сокет успешно закрыт")
        except Exception as e:
            print(f"[СЕТЬ] Ошибка при закрытии сокета: {e}")