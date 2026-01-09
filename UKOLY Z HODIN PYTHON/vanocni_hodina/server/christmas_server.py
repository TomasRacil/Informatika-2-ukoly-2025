import random
import socket
import threading
import json
import time
import os
import sys
from levels_logic import FormationLevel, QuizLevel, MazeLevel, CodingLevel

class ChristmasServer:
    def __init__(self):
        self.host = '0.0.0.0'
        self.port = 5555
        self.clients = {} # socket: addr
        self.player_data = {} # socket: dict
        self.game_started = False
        self.current_level = None
        self.level_idx = 0
        
        # Optimization: Track state to avoid redundant broadcasts
        self.last_sync_data = {}
        self.state_dirty = False
        
        with open('levels.json', 'r', encoding='utf-8') as f:
            self.config = json.load(f)

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.host, self.port))
        self.sock.listen(20)

    def log(self, msg):
        print(f"[*] {msg}")
        sys.stdout.flush()

    def broadcast(self, data):
        msg = (json.dumps(data) + "\n").encode('utf-8')
        for client in list(self.clients.keys()):
            try:
                client.sendall(msg)
            except:
                self.remove_client(client)
    
    def send_to_client(self, conn, data):
        """Pošle zprávu jen jednomu klientovi."""
        try:
            msg = (json.dumps(data) + "\n").encode('utf-8')
            conn.sendall(msg)
        except:
            self.remove_client(conn)

    def remove_client(self, conn):
        if conn in self.clients: del self.clients[conn]
        if conn in self.player_data: del self.player_data[conn]
        conn.close()
        self.broadcast({"type": "lobby_sync", "count": len(self.clients)})

    def start_level(self):
        if self.level_idx >= len(self.config["level_sequence"]):
            self.broadcast({"type": "victory", "msg": "Merry Christmas! All levels cleared!"})
            self.game_started = False
            return

        conf = self.config["level_sequence"][self.level_idx]
        p_count = len(self.player_data)
        
        if conf["type"] == "QUIZ" and "questions" in conf:
            # Vytvoříme kopii seznamu, abychom při případném restartu hry měli k dispozici původní data
            quiz_questions = list(conf["questions"])
            random.shuffle(quiz_questions)
            conf["questions"] = quiz_questions

        if conf["type"] == "FORMATION":
            self.current_level = FormationLevel(conf, p_count, self.config["shapes"])
        elif conf["type"] == "MAZE":
            self.current_level = MazeLevel(conf, p_count)
        elif conf["type"] == "QUIZ":
            self.current_level = QuizLevel(conf, p_count)
        elif conf["type"] == "CODING":
            self.current_level = CodingLevel(conf, p_count)

        start_msg = {
            "type": "start_level",
            "lvl_type": self.current_level.type,
            "title": self.current_level.title,
            "desc": self.current_level.description,
            "time_limit": self.current_level.time_limit
        }

        if conf["type"] == "MAZE":
            start_msg["walls"] = self.current_level.walls
            start_msg["grid_size"] = self.current_level.size
            start_msg["switches"] = self.current_level.switches
            start_msg["target_pos"] = self.current_level.target
        elif conf["type"] == "FORMATION":
            start_msg["static_points"] = self.current_level.static_points
            start_msg["targets"] = self.current_level.target_points
        elif conf["type"] == "CODING":
            start_msg["template"] = self.current_level.template

        self.broadcast(start_msg)
        self.state_dirty = True

    def game_loop(self):
        last_tick = time.time()
        while True:
            now = time.time()
            if self.game_started and self.current_level:
                active_count = len(self.player_data)
                
                if self.current_level.type == "QUIZ":
                    if self.current_level.evaluate_votes(active_count):
                        self.level_idx += 1
                        self.start_level()
                elif self.current_level.check_victory(self.player_data):
                    self.level_idx += 1
                    self.start_level()
                
                if self.current_level.get_time_left() <= 0:
                    self.broadcast({"type": "game_over", "msg": "Čas vypršel! Zpět do lobby."})
                    self.game_started = False
                    self.current_level = None
                
                # Sync broadcast (heartbeat 10Hz nebo okamžitě při změně)
                if self.state_dirty or (now - last_tick) > 0.1:
                    self.sync_players()
                    last_tick = now
                    self.state_dirty = False

            time.sleep(0.01)

    def sync_players(self):
        """Optimized sync: Only send dynamic data (positions, scores, time)."""
        if not self.current_level: return
        
        # Dynamic players data
        players_minimal = {id(s): {"x": d["x"], "y": d["y"], "name": d["name"], "color": d["color"]} 
                          for s, d in self.player_data.items()}

        base_data = {
            "type": "sync",
            "time_left": self.current_level.get_time_left(),
            "players": players_minimal
        }

        if self.current_level.type == "MAZE":
            base_data["active_switches"] = self.current_level.active_switches
            base_data["gate_open"] = self.current_level.gate_open
            self.broadcast(base_data)
        elif self.current_level.type == "QUIZ":
            base_data["question"] = self.current_level.current_q
            base_data["score"] = self.current_level.score
            base_data["votes"] = len(self.current_level.votes) 
            self.broadcast(base_data)
        elif self.current_level.type == "FORMATION":
            # Just broadcast players, static points were sent in start_level
            self.broadcast(base_data)
        elif self.current_level.type == "CODING":
            base_data["solved_by"] = list(self.current_level.solved_by)
            for conn, p_data in self.player_data.items():
                personal_data = base_data.copy()
                personal_data["my_results"] = self.current_level.player_progress.get(id(conn))
                self.send_to_client(conn, personal_data)

    def handle_client(self, conn, addr):
        player_id = id(conn)
        self.clients[conn] = addr
        self.broadcast({"type": "lobby_sync", "count": len(self.clients)})
        
        buffer = ""
        try:
            while True:
                data = conn.recv(4096).decode('utf-8')
                if not data: break
                buffer += data
                while "\n" in buffer:
                    line, buffer = buffer.split("\n", 1)
                    if not line.strip(): continue
                    msg = json.loads(line)
                    
                    if msg["type"] == "join":
                        import random
                        self.player_data[conn] = {
                            "name": msg["name"], "x": 10, "y": 10,
                            "color": (random.randint(50,255), random.randint(50,255), random.randint(50,255)),
                            "id": player_id
                        }
                        self.log(f"Student {msg['name']} joined.")
                        self.broadcast({"type": "lobby_sync", "count": len(self.clients)})
                    
                    elif msg["type"] == "move":
                        if conn in self.player_data and self.current_level:
                            # Boundary checks
                            old_x, old_y = self.player_data[conn]["x"], self.player_data[conn]["y"]
                            max_c = self.current_level.size - 1 if hasattr(self.current_level, 'size') else 19
                            
                            new_x = max(0, min(max_c, msg["x"]))
                            new_y = max(0, min(max_c, msg["y"]))
                            
                            if old_x != new_x or old_y != new_y:
                                self.player_data[conn]["x"] = new_x
                                self.player_data[conn]["y"] = new_y
                                self.state_dirty = True # Trigger faster broadcast
                    
                    elif msg["type"] == "vote":
                        if self.current_level and self.current_level.type == "QUIZ":
                            self.current_level.process_vote(player_id, msg["choice"])
                            self.state_dirty = True
                            if self.current_level.check_victory(self.player_data):
                                self.level_idx += 1
                                self.start_level()

                    elif msg["type"] == "submit_code":
                        if self.current_level and self.current_level.type == "CODING":
                            results = self.current_level.run_tests(msg["code"])
                            self.current_level.player_progress[player_id] = results
                            if "results" in results and all(results["results"]):
                                self.current_level.solved_by.add(player_id)
                            self.state_dirty = True

        except: pass
        finally: self.remove_client(conn)


    def admin_console(self):
        """Command line interface for the teacher."""
        while True:
            cmd = input("ADMIN > ").strip().lower()
            if cmd == "start":
                if not self.player_data:
                    print("[!] Nelze spustit hru bez studentů.")
                else:
                    self.level_idx = 0
                    self.game_started = True
                    self.start_level()
                    print("[OK] Hra spuštěna.")
            elif cmd == "status":
                print(f"--- STAV ---")
                print(f"Studentů: {len(self.player_data)}")
                print(f"Hra běží: {self.game_started}")
                if self.current_level:
                    print(f"Level: {self.current_level.title} ({self.current_level.type})")
            elif cmd == "list":
                print("--- SEZNAM STUDENTŮ ---")
                for data in self.player_data.values():
                    print(f"- {data['name']} (pozice: [{data['x']}, {data['y']}])")
            elif cmd == "exit":
                print("[*] Vypínám server...")
                os._exit(0)
            elif cmd == "help":
                print("Příkazy: start, status, list, exit")

    def run(self):
        threading.Thread(target=self.admin_console, daemon=True).start()
        threading.Thread(target=self.game_loop, daemon=True).start()
        self.log(f"Server listening on {self.host}:{self.port}")
        while True:
            conn, addr = self.sock.accept()
            threading.Thread(target=self.handle_client, args=(conn, addr), daemon=True).start()