import socket
import json
import threading

class NetworkManager:
    """Třída pro správu síťové komunikace se serverem."""
    def __init__(self, host, port=5555):
        self.host = host
        self.port = port
        self.sock = None
        self.connected = False
        self.on_message_callback = None

    def connect(self):
        """Naváže spojení se serverem."""
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((self.host, self.port))
            self.connected = True
            threading.Thread(target=self._receive_loop, daemon=True).start()
            return True
        except Exception as e:
            print(f"Chyba připojení: {e}")
            return False

    def send(self, data):
        """Odešle data ve formátu JSON."""
        if self.connected:
            try:
                msg = json.dumps(data) + "\n"
                self.sock.sendall(msg.encode('utf-8'))
            except Exception as e:
                print(f"Chyba odesílání: {e}")
                self.connected = False

    def _receive_loop(self):
        """Vlákno pro neustálý příjem dat."""
        buffer = ""
        while self.connected:
            try:
                data = self.sock.recv(4096).decode('utf-8')
                if not data: break
                buffer += data
                while "\n" in buffer:
                    line, buffer = buffer.split("\n", 1)
                    if line.strip() and self.on_message_callback:
                        msg = json.loads(line)
                        self.on_message_callback(msg)
            except Exception as e:
                print(f"Chyba příjmu: {e}")
                break
        self.connected = False