import pygame
import sys
import math

# UI Konstanty
WIDTH, HEIGHT = 800, 750
GRID_SIZE, CELL_SIZE = 20, 30
OFFSET_X, OFFSET_Y = 100, 100

class BaseScreen:
    """Základní třída pro všechny obrazovky v aplikaci."""
    def __init__(self, app):
        self.app = app
        self.font_m = pygame.font.SysFont("Arial", 24, bold=True)
        self.font_s = pygame.font.SysFont("Arial", 18)
        self.font_code = pygame.font.SysFont("Consolas", 16)

    def handle_event(self, event): pass
    def update(self): pass
    def draw(self, screen): pass

    def draw_center_text(self, screen, text, y, font, color=(255, 255, 255)):
        surf = font.render(text, True, color)
        screen.blit(surf, (WIDTH // 2 - surf.get_width() // 2, y))
    
    def wrap_text(self, text, font, max_width):
        """Pomocná funkce pro zalamování dlouhého textu."""
        words = text.split(' ')
        lines = []
        current_line = ""
        for word in words:
            test_line = current_line + word + " "
            if font.size(test_line)[0] < max_width:
                current_line = test_line
            else:
                lines.append(current_line)
                current_line = word + " "
        lines.append(current_line)
        return lines

class InputScreen(BaseScreen):
    """Obrazovka pro zadávání IP adresy nebo Jména studenta."""
    def __init__(self, app, prompt, next_state):
        super().__init__(app)
        self.prompt = prompt
        self.next_state = next_state
        self.cursor_visible = True
        self.last_cursor_toggle = pygame.time.get_ticks()

    def handle_event(self, event):
        if event.type == pygame.KEYDOWN:
            self.cursor_visible = True
            self.last_cursor_toggle = pygame.time.get_ticks()

            if event.key == pygame.K_RETURN:
                if self.app.state == "INPUT_IP":
                    self.app.network.host = self.app.input_text or "127.0.0.1"
                    if self.app.network.connect():
                        self.app.state = "INPUT_NAME"
                        self.app.input_text = ""
                else:
                    self.app.player_name = self.app.input_text or "Student"
                    self.app.network.send({"type": "join", "name": self.app.player_name})
                    self.app.state = "LOBBY"
                    self.app.input_text = ""
            elif event.key == pygame.K_BACKSPACE:
                self.app.input_text = self.app.input_text[:-1]
            else:
                if event.unicode.isprintable():
                    self.app.input_text += event.unicode

    def draw(self, screen):
         self.draw_center_text(screen, "Vánoční Hodina", 100, self.font_m, (255, 215, 0))
         self.draw_center_text(screen, self.prompt, 250, self.font_m)

         # Vylepšený input box
         input_box_rect = pygame.Rect(WIDTH // 2 - 150, 300, 300, 50)
         pygame.draw.rect(screen, (30, 45, 65), input_box_rect, border_radius=8)
         pygame.draw.rect(screen, (60, 80, 110), input_box_rect, 2, border_radius=8)

         # Logika blikání kurzoru
         now = pygame.time.get_ticks()
         if now - self.last_cursor_toggle > 500:
             self.cursor_visible = not self.cursor_visible
             self.last_cursor_toggle = now

         input_val = getattr(self.app, 'input_text', "")
         text_surf = self.font_m.render(input_val, True, (255, 255, 255))

         # Pozice textu
         text_rect = text_surf.get_rect(centery=input_box_rect.centery)
         if text_rect.width > input_box_rect.width - 20: # Ošetření přetečení
             text_rect.right = input_box_rect.right - 10
         else:
             text_rect.left = input_box_rect.left + 10

         # Vykreslení textu a kurzoru s ořezáním
         clip_rect = input_box_rect.copy().inflate(-10, -10)
         original_clip = screen.get_clip()
         screen.set_clip(clip_rect)
         screen.blit(text_surf, text_rect)
         if self.cursor_visible and (text_rect.right + 4) < clip_rect.right:
             pygame.draw.line(screen, (255, 255, 255), (text_rect.right + 2, text_rect.top), (text_rect.right + 2, text_rect.bottom), 2)
         screen.set_clip(original_clip)

         self.draw_center_text(screen, "Stiskněte ENTER pro potvrzení", 370, self.font_s, (150, 150, 150))
 

class LobbyScreen(BaseScreen):
    """Obrazovka čekárny před zahájením hry učitelem."""
    def draw(self, screen):
        player_count = getattr(self.app, 'player_count', 0)
        self.draw_center_text(screen, "VÁNOČNÍ LOBBY", 100, self.font_m, (255, 215, 0))
        self.draw_center_text(screen, f"Připojených studentů: {player_count}", 250, self.font_m)
        self.draw_center_text(screen, "Čekejte na pokyn učitele...", 450, self.font_s, (150, 150, 150))

class FormationScreen(BaseScreen):
    """Obrazovka pro doplňování obrazců (grid, pohyb, statické body)."""
    def handle_event(self, event):
        if event.type == pygame.KEYDOWN:
            players = getattr(self.app, 'players', {})
            player_name = getattr(self.app, 'player_name', "")
            me = next((p for p in players.values() if p["name"] == player_name), None)
            
            if me:
                nx, ny = me["x"], me["y"]
                if event.key == pygame.K_UP: ny -= 1
                elif event.key == pygame.K_DOWN: ny += 1
                elif event.key == pygame.K_LEFT: nx -= 1
                elif event.key == pygame.K_RIGHT: nx += 1
                
                if nx != me["x"] or ny != me["y"]:
                    self.app.network.send({"type": "move", "x": nx, "y": ny})

    def draw(self, screen):
        time_left = getattr(self.app, 'time_left', 0)
        self.draw_center_text(screen, f"ČAS: {time_left}s", 30, self.font_m)
        
        players = getattr(self.app, 'players', {})
        player_name = getattr(self.app, 'player_name', "")
        me = next((p for p in players.values() if p["name"] == player_name), None)
        
        static_set = {tuple(s) for s in getattr(self.app, 'static_points', [])}
        walls_set = {tuple(w) for w in getattr(self.app, 'walls', [])}
        use_fog = getattr(self.app, 'use_fog', False)
        target_pos = getattr(self.app, 'target_pos', None)
        
        # Vykreslení hrací plochy (mřížka)
        for x in range(GRID_SIZE):
            for y in range(GRID_SIZE):
                visible = True
                if use_fog and me:
                    dist = max(abs(x - me["x"]), abs(y - me["y"]))
                    if dist > 2: visible = False
                
                rect = (OFFSET_X + x * CELL_SIZE, OFFSET_Y + y * CELL_SIZE, CELL_SIZE, CELL_SIZE)
                
                if visible:
                    pygame.draw.rect(screen, (40, 50, 60), rect, 1)
                    
                    # Statické části obrazce (zelené)
                    if (x, y) in static_set:
                        pygame.draw.rect(screen, (30, 80, 30), (rect[0]+2, rect[1]+2, CELL_SIZE-4, CELL_SIZE-4))
                        pygame.draw.rect(screen, (50, 120, 50), (rect[0]+2, rect[1]+2, CELL_SIZE-4, CELL_SIZE-4), 1)
                    
                    # Zdi pro bludiště
                    if (x, y) in walls_set:
                        pygame.draw.rect(screen, (100, 100, 100), rect)
                    
                    # Cílová pozice bludiště
                    if target_pos and target_pos == [x, y]:
                        pygame.draw.rect(screen, (0, 150, 255), rect, 3)
                else:
                    pygame.draw.rect(screen, (0, 0, 0), rect)

        # Vykreslení hráčů
        for p in players.values():
            if use_fog and me:
                if max(abs(p["x"] - me["x"]), abs(p["y"] - me["y"])) > 2:
                    continue
            
            px, py = OFFSET_X + p["x"] * CELL_SIZE, OFFSET_Y + p["y"] * CELL_SIZE
            pygame.draw.rect(screen, p["color"], (px + 2, py + 2, CELL_SIZE - 4, CELL_SIZE - 4), border_radius=4)
            
            if p["name"] == player_name:
                name_surf = self.font_s.render("TY", True, (255, 255, 255))
                screen.blit(name_surf, (px + (CELL_SIZE // 2 - name_surf.get_width() // 2), py - 20))

class QuizScreen(BaseScreen):
    """Speciální obrazovka pro kvízové otázky."""
    def handle_event(self, event):
        if event.type == pygame.KEYDOWN:
            keys = {pygame.K_1: 0, pygame.K_2: 1, pygame.K_3: 2, pygame.K_4: 3}
            if event.key in keys:
                choice = keys[event.key]
                self.app.my_vote = choice # Uložíme si lokálně naši volbu
                self.app.network.send({"type": "vote", "choice": choice})

    def draw(self, screen):
        self.draw_center_text(screen, f"ZBÝVAJÍCÍ ČAS: {self.app.time_left}s", 50, self.font_m, (255, 200, 0))
        
        # Horní panel informací
        self.draw_center_text(screen, f"Úspěšné odpovědi: {self.app.score}", 110, self.font_m, (100, 255, 100))
        
        # Průběh hlasování
        votes = self.app.votes
        total = self.app.player_count
        progress_color = (0, 200, 255) if votes < total else (0, 255, 100)
        self.draw_center_text(screen, f"Odhlasovalo: {votes} z {total} studentů", 150, self.font_s, progress_color)

        if self.app.question:
            # Box s otázkou
            q_rect = pygame.Rect(80, 200, WIDTH - 160, 420)
            pygame.draw.rect(screen, (30, 45, 65), q_rect, border_radius=15)
            pygame.draw.rect(screen, (60, 80, 110), q_rect, 2, border_radius=15)
            
            # Otázka
            self.draw_center_text(screen, self.app.question["q"], 240, self.font_m)
            
            # Možnosti
            for i, option in enumerate(self.app.question["o"]):
                y_pos = 330 + i * 60
                is_selected = (self.app.my_vote == i)
                
                # Pozadí pro vybranou možnost
                opt_rect = pygame.Rect(120, y_pos - 10, WIDTH - 240, 45)
                if is_selected:
                    pygame.draw.rect(screen, (40, 100, 80), opt_rect, border_radius=8)
                    pygame.draw.rect(screen, (0, 255, 150), opt_rect, 2, border_radius=8)
                else:
                    pygame.draw.rect(screen, (45, 60, 85), opt_rect, border_radius=8)

                text = f"{i+1}) {option}"
                color = (255, 255, 255) if not is_selected else (255, 215, 0)
                screen.blit(self.font_s.render(text, True, color), (140, y_pos))

            if self.app.my_vote is not None:
                self.draw_center_text(screen, "Váš hlas byl zaznamenán. Čekejte na ostatní...", 640, self.font_s, (0, 200, 150))
            else:
                self.draw_center_text(screen, "Hlasujte stisknutím klávesy 1 - 4", 640, self.font_s, (180, 180, 180))

class MazeScreen(BaseScreen):
    """Dynamicky škálovatelná obrazovka bludiště s LOS."""
    def handle_event(self, event):
        if event.type == pygame.KEYDOWN:
            players = getattr(self.app, 'players', {})
            me = next((p for p in players.values() if p["name"] == self.app.player_name), None)
            if me:
                nx, ny = me["x"], me["y"]
                grid_size = getattr(self.app, 'grid_size', 20)
                if event.key == pygame.K_UP: ny -= 1
                elif event.key == pygame.K_DOWN: ny += 1
                elif event.key == pygame.K_LEFT: nx -= 1
                elif event.key == pygame.K_RIGHT: nx += 1
                
                walls = getattr(self.app, 'walls', [])
                if [nx, ny] not in walls and 0 <= nx < grid_size and 0 <= ny < grid_size:
                    self.app.network.send({"type": "move", "x": nx, "y": ny})

    def is_visible(self, px, py, tx, ty, walls_set):
        """Základní Line of Sight pro poloměr 2."""
        if px == tx and py == ty: return True
        dist = math.sqrt((tx - px)**2 + (ty - py)**2)
        if dist > 2.9: return False 
        
        if abs(px - tx) <= 1 and abs(py - ty) <= 1: return True
            
        mx, my = (px + tx) / 2, (py + ty) / 2
        check_points = [(int(math.floor(mx)), int(math.floor(my))), (int(math.ceil(mx)), int(math.ceil(my)))]
        for cp in check_points:
            if cp in walls_set: return False
        return True

    def draw(self, screen):
        grid_size = getattr(self.app, 'grid_size', 20)
        if grid_size == 0:
            self.draw_center_text(screen, "Načítání bludiště...", HEIGHT // 2, self.font_m)
            return
        # Dynamický výpočet velikosti buňky, aby se bludiště vešlo na obrazovku
        cell_size = min((WIDTH - 100) // grid_size, (HEIGHT - 150) // grid_size)
        ox = (WIDTH - (grid_size * cell_size)) // 2
        oy = 100

        self.draw_center_text(screen, f"ČAS: {self.app.time_left}s", 30, self.font_m)
        
        players = getattr(self.app, 'players', {})
        me = next((p for p in players.values() if p["name"] == self.app.player_name), None)
        if not me: return

        walls_set = {tuple(w) for w in getattr(self.app, 'walls', [])}
        switches = getattr(self.app, 'switches', [])
        active_sw = getattr(self.app, 'active_switches', [])
        gate_open = getattr(self.app, 'gate_open', False)
        target = getattr(self.app, 'target_pos', None)

        # Výpočet viditelných polí (LOS)
        visible_tiles = set()
        for x in range(me["x"] - 3, me["x"] + 4):
            for y in range(me["y"] - 3, me["y"] + 4):
                if 0 <= x < grid_size and 0 <= y < grid_size:
                    if self.is_visible(me["x"], me["y"], x, y, walls_set):
                        visible_tiles.add((x, y))

        # Vykreslení mřížky
        for x in range(grid_size):
            for y in range(grid_size):
                rect = (ox + x * cell_size, oy + y * cell_size, cell_size, cell_size)
                if (x, y) in visible_tiles:
                    pygame.draw.rect(screen, (35, 45, 60), rect)
                    
                    if (x, y) in walls_set:
                        pygame.draw.rect(screen, (90, 100, 115), rect)
                    
                    # Pečetě (Spínače)
                    for i, sw in enumerate(switches):
                        if [x, y] == sw:
                            color = (0, 255, 100) if i in active_sw else (220, 60, 60)
                            pygame.draw.circle(screen, color, (rect[0]+cell_size//2, rect[1]+cell_size//2), cell_size//3, 2)
                    
                    # Cíl
                    if target == [x, y]:
                        color = (0, 200, 255) if gate_open else (70, 70, 70)
                        pygame.draw.rect(screen, color, (rect[0]+2, rect[1]+2, cell_size-4, cell_size-4), 2)
                else:
                    pygame.draw.rect(screen, (0, 0, 0), rect)

        # Spoluhráči
        for p in players.values():
            if (p["x"], p["y"]) in visible_tiles:
                px, py = ox + p["x"] * cell_size, oy + p["y"] * cell_size
                pygame.draw.rect(screen, p["color"], (px+2, py+2, cell_size-4, cell_size-4), border_radius=3)
                if p["name"] == self.app.player_name:
                    pygame.draw.rect(screen, (255, 255, 255), (px+2, py+2, cell_size-4, cell_size-4), 1, border_radius=3)

        status = f"Aktivní pečetě: {len(active_sw)} / {len(switches)}"
        self.draw_center_text(screen, status, HEIGHT - 50, self.font_s, (0, 255, 200))

class EndScreen(BaseScreen):
    """Obrazovka po skončení hry (vítězství nebo vypršení času)."""
    def draw(self, screen):
        end_msg = getattr(self.app, 'end_msg', "Konec hry")
        color = (0, 255, 100) if any(word in end_msg for word in ["Veselé", "Vítězství", "Merry"]) else (255, 100, 100)
        self.draw_center_text(screen, end_msg, HEIGHT // 2 - 50, self.font_m, color)
        self.draw_center_text(screen, "Čekejte na další pokyn učitele...", HEIGHT // 2 + 20, self.font_s, (150, 150, 150))

class CodingScreen(BaseScreen):
    """Obrazovka pro psaní a odesílání kódu s plnohodnotným pohybem kurzoru."""
    def __init__(self, app):
        super().__init__(app)
        self.editor_rect = pygame.Rect(50, 150, WIDTH - 100, 400)
        self.submit_button = pygame.Rect(WIDTH // 2 - 100, 570, 200, 50)
        self.cursor_visible = True
        self.last_cursor_toggle = pygame.time.get_ticks()
        self.cursor_idx = len(self.app.my_code) # Index v celém řetězci kódu

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.submit_button.collidepoint(event.pos):
                self.app.network.send({"type": "submit_code", "code": self.app.my_code})

        elif event.type == pygame.KEYDOWN:
            # Vždy zajistíme, aby se kurzor po akci objevil
            self.cursor_visible = True
            self.last_cursor_toggle = pygame.time.get_ticks()

            # Zpracování speciálních kláves
            if event.key == pygame.K_LEFT:
                self.cursor_idx = max(0, self.cursor_idx - 1)
            elif event.key == pygame.K_RIGHT:
                self.cursor_idx = min(len(self.app.my_code), self.cursor_idx + 1)
            elif event.key == pygame.K_UP:
                # Najdeme pozici v předchozím řádku
                self._move_cursor_vertically(-1)
            elif event.key == pygame.K_DOWN:
                # Najdeme pozici v následujícím řádku
                self._move_cursor_vertically(1)
            elif event.key == pygame.K_HOME:
                lines = self.app.my_code[:self.cursor_idx].split('\n')
                self.cursor_idx -= len(lines[-1])
            elif event.key == pygame.K_END:
                lines = self.app.my_code[self.cursor_idx:].split('\n')
                self.cursor_idx += len(lines[0])
            elif event.key == pygame.K_BACKSPACE:
                if self.cursor_idx > 0:
                    self.app.my_code = self.app.my_code[:self.cursor_idx - 1] + self.app.my_code[self.cursor_idx:]
                    self.cursor_idx -= 1
            elif event.key == pygame.K_DELETE:
                if self.cursor_idx < len(self.app.my_code):
                    self.app.my_code = self.app.my_code[:self.cursor_idx] + self.app.my_code[self.cursor_idx + 1:]
            elif event.key == pygame.K_RETURN:
                if pygame.key.get_mods() & pygame.KMOD_CTRL:
                    self.app.network.send({"type": "submit_code", "code": self.app.my_code})
                else:
                    self.app.my_code = self.app.my_code[:self.cursor_idx] + "\n" + self.app.my_code[self.cursor_idx:]
                    self.cursor_idx += 1
            elif event.key == pygame.K_TAB:
                self.app.my_code = self.app.my_code[:self.cursor_idx] + "    " + self.app.my_code[self.cursor_idx:]
                self.cursor_idx += 4
            else:
                if event.unicode.isprintable() and event.unicode != "":
                    self.app.my_code = self.app.my_code[:self.cursor_idx] + event.unicode + self.app.my_code[self.cursor_idx:]
                    self.cursor_idx += 1

    def _move_cursor_vertically(self, direction):
        """Pomocná metoda pro pohyb kurzoru nahoru/dolů."""
        lines = self.app.my_code.split('\n')
        
        # Najdeme aktuální řádek a sloupec
        current_char = 0
        current_row = 0
        current_col = 0
        
        for i, line in enumerate(lines):
            line_len = len(line)
            if current_char <= self.cursor_idx <= current_char + line_len:
                current_row = i
                current_col = self.cursor_idx - current_char
                break
            current_char += line_len + 1 # +1 za '\n'

        target_row = current_row + direction
        if 0 <= target_row < len(lines):
            # Vypočítáme nový index
            new_char_idx = 0
            for i in range(target_row):
                new_char_idx += len(lines[i]) + 1
            
            # Přidáme sloupec (omezený délkou cílového řádku)
            new_char_idx += min(current_col, len(lines[target_row]))
            self.cursor_idx = new_char_idx

    def draw(self, screen):
        # Čas a titulek
        self.draw_center_text(screen, f"ČAS: {self.app.time_left}s", 20, self.font_m)
        title = getattr(self.app, 'title', 'Coding Challenge')
        self.draw_center_text(screen, title, 60, self.font_m, (255, 215, 0))

        # Popis úkolu
        description = getattr(self.app, 'description', '')
        desc_lines = self.wrap_text(description, self.font_s, WIDTH - 100)
        for i, line in enumerate(desc_lines):
            self.draw_center_text(screen, line, 100 + i * 20, self.font_s, (180, 180, 180))

        # Editor kódu
        pygame.draw.rect(screen, (10, 20, 30), self.editor_rect)
        pygame.draw.rect(screen, (80, 90, 100), self.editor_rect, 2)
        
        # Logika blikání kurzoru
        now = pygame.time.get_ticks()
        if now - self.last_cursor_toggle > 500:
            self.cursor_visible = not self.cursor_visible
            self.last_cursor_toggle = now

        # Vykreslení kódu a kurzoru
        code_lines = self.app.my_code.split('\n')
        current_char_count = 0
        
        for i, line in enumerate(code_lines):
            line_surf = self.font_code.render(line, True, (220, 220, 220))
            line_x = self.editor_rect.x + 10
            line_y = self.editor_rect.y + 10 + i * 20
            screen.blit(line_surf, (line_x, line_y))

            # Kontrola, zda je kurzor na tomto řádku
            # Musíme ošetřit i prázdný řetězec na konci (nový řádek)
            line_len = len(line)
            if current_char_count <= self.cursor_idx <= current_char_count + line_len:
                # Pokud jsme na tomto řádku a kurzor má být vidět
                if self.cursor_visible:
                    # Vypočítáme X pozici kurzoru v rámci řádku
                    sub_str = line[:self.cursor_idx - current_char_count]
                    cursor_offset_x = self.font_code.size(sub_str)[0]
                    pygame.draw.line(screen, (255, 255, 255), 
                                     (line_x + cursor_offset_x, line_y), 
                                     (line_x + cursor_offset_x, line_y + 18), 2)
            
            current_char_count += line_len + 1 # +1 pro '\n'

        # Tlačítko Odeslat
        pygame.draw.rect(screen, (0, 150, 100), self.submit_button, border_radius=10)
        self.draw_center_text(screen, "Odeslat kód", 582, self.font_m, (255, 255, 255))
        
        # Zobrazení výsledků
        results = self.app.my_results
        if results:
            y_offset = 640
            if "error" in results:
                self.draw_center_text(screen, f"Chyba: {results['error']}", y_offset, self.font_s, (255, 100, 100))
            elif "results" in results:
                passed = sum(1 for r in results["results"] if r)
                total = len(results["results"])
                color = (0, 255, 100) if passed == total else (255, 180, 0)
                self.draw_center_text(screen, f"Výsledek testů: {passed} / {total} úspěšných", y_offset, self.font_s, color)

class GameScreen(BaseScreen):
    """
    Kontejnerová obrazovka, která automaticky přepíná mezi herními módy
    podle toho, jaká data posílá server.
    """
    def __init__(self, app):
        super().__init__(app)
        self.formation_sub = FormationScreen(app)
        self.quiz_sub = QuizScreen(app)
        self.maze_sub = MazeScreen(app)
        self.coding_sub = CodingScreen(app)

    def handle_event(self, event):
        lvl_type = getattr(self.app, 'lvl_type', "")
        if lvl_type == "QUIZ":
            self.quiz_sub.handle_event(event)
        elif lvl_type == "FORMATION":
            self.formation_sub.handle_event(event)
        elif lvl_type == "MAZE":
            self.maze_sub.handle_event(event)
        elif lvl_type == "CODING":
            self.coding_sub.handle_event(event)
        else: # Fallback pro případ, že data ještě nedorazila
            pass

    def draw(self, screen):
        lvl_type = getattr(self.app, 'lvl_type', "")
        if lvl_type == "QUIZ":
            self.quiz_sub.draw(screen)
        elif lvl_type == "FORMATION":
            self.formation_sub.draw(screen)
        elif lvl_type == "MAZE":
            self.maze_sub.draw(screen)
        elif lvl_type == "CODING":
            self.coding_sub.draw(screen)
        else:
            self.draw_center_text(screen, "Načítání úrovně...", HEIGHT // 2, self.font_m)

class EndScreen(BaseScreen):
    """Obrazovka po skončení hry (vítězství nebo vypršení času)."""
    def draw(self, screen):
        end_msg = getattr(self.app, 'end_msg', "Konec hry")
        color = (0, 255, 100) if any(word in end_msg for word in ["Veselé", "Vítězství", "Merry"]) else (255, 100, 100)
        self.draw_center_text(screen, end_msg, HEIGHT // 2 - 50, self.font_m, color)
        self.draw_center_text(screen, "Čekejte na další pokyn učitele...", HEIGHT // 2 + 20, self.font_s, (150, 150, 150))