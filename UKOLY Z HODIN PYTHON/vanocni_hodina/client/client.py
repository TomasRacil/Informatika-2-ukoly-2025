import pygame
import sys
from network_manager import NetworkManager
from screens import InputScreen, LobbyScreen, GameScreen, EndScreen

pygame.init()
pygame.mixer.init()

# Inicializace okna
pygame.init()
WIDTH, HEIGHT = 800, 750
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Vánoční Programátorská Výzva")

class GameApp:
    def __init__(self):
        self.network = NetworkManager("127.0.0.1")
        self.network.on_message_callback = self.on_message
        
        self.state = "INPUT_IP" 
        self.player_name = ""
        self.input_text = ""
        
        # State Data
        self.player_count = 0
        self.players = {}
        self.time_left = 0
        self.lvl_type = ""
        self.end_msg = ""
        
        # Titulek a popis pro zobrazení na obrazovkách
        self.title = ""
        self.description = ""
        
        # Level Static Cache (Updated only on start_level)
        self.walls = []
        self.grid_size = 20
        self.switches = []
        self.static_points = []
        self.targets = []
        self.target_pos = None
        self.code_template = ""
        
        # Dynamic Level State
        self.active_switches = []
        self.gate_open = False
        self.question = None
        self.score = 0
        self.votes = 0
        self.my_vote = None
        self.my_code = ""
        self.my_results = None
        self.solved_by = []

        self.screens = {
            "INPUT_IP": InputScreen(self, "IP", "INPUT_NAME"),
            "INPUT_NAME": InputScreen(self, "Jméno", "LOBBY"),
            "LOBBY": LobbyScreen(self),
            "GAME": GameScreen(self),
            "END": EndScreen(self)
        }
        self.play_background_music()

    def play_background_music(self):
        """Načte a spustí vánoční skladbu v nekonečné smyčce."""
        try:
            # Předpokládáme, že soubor 'christmas.mp3' je v adresáři s klientem.
            # Pokud soubor chybí, odchytíme chybu, aby se aplikace spustila i bez zvuku.
            pygame.mixer.music.load("Jingle-Bells.mp3")
            pygame.mixer.music.set_volume(0.2) # Nastavení nižší hlasitosti (20%)
            pygame.mixer.music.play(-1) # Parametr -1 zajistí opakování po skončení
        except pygame.error:
            print("Upozornění: Soubor 'christmas.mp3' nebyl nalezen. Hra bude bez hudby.")


    def on_message(self, msg):
        m_type = msg.get("type")
        
        if m_type == "lobby_sync":
            self.player_count = msg["count"]
            
        elif m_type == "start_level":
            self.state = "GAME"
            self.lvl_type = msg.get("lvl_type", "")
            self.title = msg.get("title", "Vánoční výzva")
            self.description = msg.get("description", "")
            self.end_msg = ""
            self.my_vote = None
            self.my_results = None
            
            # Cache static data
            self.walls = msg.get("walls", [])
            self.grid_size = msg.get("grid_size", 20)
            self.switches = msg.get("switches", [])
            self.target_pos = msg.get("target_pos")
            self.static_points = msg.get("static_points", [])
            self.targets = msg.get("targets", [])
            self.code_template = msg.get("template", "")
            if not self.my_code or self.lvl_type == "CODING":
                self.my_code = self.code_template

        elif m_type == "sync":
            self.time_left = msg.get("time_left", 0)
            self.players = msg.get("players", {})
            
            # Sync dynamic parts only
            if self.lvl_type == "QUIZ":
                new_q_data = msg.get("question")
                new_votes_count = msg.get("votes", 0)
                
                is_new_round = False
                if new_q_data:
                    if not self.question:
                        is_new_round = True
                    # V levels.json je text otázky pod klíčem 'q'
                    elif self.question.get("q") != new_q_data.get("q"):
                        is_new_round = True
                    elif new_votes_count == 0 and self.votes > 0:
                        # Server právě vyhodnotil a vyčistil hlasy
                        is_new_round = True

                if is_new_round:
                    self.my_vote = None
                    self.question = new_q_data

                if is_new_round:
                    self.my_vote = None
                    self.question = new_q_data
                
                self.score = msg.get("score", 0)
                self.votes = new_votes_count
            elif self.lvl_type == "MAZE":
                self.active_switches = msg.get("active_switches", [])
                self.gate_open = msg.get("gate_open", False)
            elif self.lvl_type == "CODING":
                self.my_results = msg.get("my_results")
                self.solved_by = msg.get("solved_by", [])

        elif m_type in ["victory", "game_over"]:
            self.state = "END"
            self.end_msg = msg.get("msg", "Konec hry")

    def run(self):
        clock = pygame.time.Clock()
        while True:
            current_screen = self.screens.get(self.state)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if current_screen:
                    current_screen.handle_event(event)

            if current_screen:
                screen.fill((20, 30, 40))
                current_screen.draw(screen)
            
            pygame.display.flip()
            clock.tick(30)

if __name__ == "__main__":
    app = GameApp()
    app.run()