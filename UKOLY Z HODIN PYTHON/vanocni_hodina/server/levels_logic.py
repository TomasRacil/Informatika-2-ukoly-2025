from collections import Counter
import time
import random
import multiprocessing
import sys

class BaseLevel:
    """Základní blok pro všechny herní úrovně."""
    def __init__(self, config, players_count):
        self.id = config["id"]
        self.type = config["type"]
        self.title = config["title"]
        self.description = config["description"]
        self.time_limit = config.get("time_limit", 60)
        self.start_time = time.time()
        self.finished = False

    def get_time_left(self):
        """Vrací zbývající čas do konce úrovně v sekundách."""
        return max(0, int(self.time_limit - (time.time() - self.start_time)))

    def check_victory(self, players):
        """Metoda pro kontrolu vítězství, kterou musí implementovat konkrétní úrovně."""
        return False

class FormationLevel(BaseLevel):
    """Level, kde studenti doplňují chybějící body v komplexním vánočním obrazu."""
    def __init__(self, config, players_count, shapes_config):
        super().__init__(config, players_count)
        # Získáme všechny body definovaného tvaru z konfigurace
        shape_points = shapes_config.get(config["shape_key"], [])
        
        # Náhodně vybereme body, které musí obsadit studenti (podle aktuálního počtu hráčů).
        # Tyto body jsou pro studenty neviditelné (musí je odhadnout).
        if len(shape_points) >= players_count:
            self.target_points = random.sample(shape_points, players_count)
        else:
            # Pokud je hráčů více než bodů v definici, použijeme všechny body
            self.target_points = list(shape_points)
            
        # Ostatní body obrazu, které tam zůstanou jako statická nápověda (šablona)
        self.static_points = [p for p in shape_points if p not in self.target_points]

    def check_victory(self, players):
        """Kontroluje, zda jsou všechny chybějící body (target_points) obsazeny hráči."""
        if not players or not self.target_points: 
            return False
            
        occupied_count = 0
        # Převedeme aktuální pozice hráčů na seznam n-tic pro snadné porovnání
        p_positions = [(p['x'], p['y']) for p in players.values()]
        
        # Zkontrolujeme každý cílový bod
        for target in self.target_points:
            # Bod musí být obsazen alespoň jedním hráčem
            if tuple(target) in p_positions:
                occupied_count += 1
        
        # Vítězství: Počet obsazených unikátních cílových bodů odpovídá celkovému počtu cílů
        return occupied_count >= len(self.target_points)
    
class QuizLevel(BaseLevel):
    """Týmový kvíz s demokratickým hlasováním."""
    def __init__(self, config, players_count):
        super().__init__(config, players_count)
        self.pool = config["pool"]
        self.target_score = config.get("target_score", 10)
        self.score = 0
        self.current_q = random.choice(self.pool)
        self.votes = {} # player_id -> choice_index

    def process_vote(self, player_id, choice_idx):
        """Uloží hlas konkrétního hráče."""
        self.votes[player_id] = choice_idx

    def evaluate_votes(self, total_players):
        """Vyhodnotí hlasování, pokud všichni odhlasovali."""
        if len(self.votes) < total_players or total_players == 0:
            return False # Ještě neodhlasovali všichni
        
        # Zjisti nejčastější hlas (většina)
        counts = Counter(self.votes.values())
        majority_choice = counts.most_common(1)[0][0]
        
        # Kontrola správnosti
        correct_idx = int(self.current_q["a"])
        if majority_choice == correct_idx:
            self.score += 1
        
        # Vyčisti hlasy a vyber novou otázku
        self.votes = {}
        if self.score >= self.target_score:
            return True # Level dokončen
        else:
            self.current_q = random.choice(self.pool)
            return False # Pokračujeme s další otázkou

    def check_victory(self, players):
        # Vítězství je řízeno přes evaluate_votes, ne přes pozice
        return self.score >= self.target_score
    
class MazeLevel(BaseLevel):
    """Obří bludiště s pečetěmi ve slepých uličkách."""
    def __init__(self, config, players_count):
        super().__init__(config, players_count)
        self.size = config.get("grid_size", 31) # Doporučeno liché číslo
        if self.size % 2 == 0: self.size += 1
        
        self.walls = []
        self._generate_maze()
        
        # Analýza slepých uliček
        dead_ends = self._find_dead_ends()
        floor_cells = [(x, y) for x in range(self.size) for y in range(self.size) if [x, y] not in self.walls]
        
        # Odstraníme startovní pozici (střed nebo 0,0) z možných míst pro spínače
        start_pos = (0, 0)
        if start_pos in dead_ends: dead_ends.remove(start_pos)
        
        random.shuffle(dead_ends)
        random.shuffle(floor_cells)
        
        # Cíl je náhodné místo (ideálně daleko od startu)
        self.target = floor_cells.pop()
        
        # Spínače - prioritně do slepých uliček, pak do volných míst
        self.switches = []
        num_switches = players_count if players_count > 0 else 3
        
        for _ in range(num_switches):
            if dead_ends:
                self.switches.append(list(dead_ends.pop()))
            elif floor_cells:
                self.switches.append(list(floor_cells.pop()))
        
        self.active_switches = []
        self.gate_open = False

    def _generate_maze(self):
        """Generování pomocí DFS (Recursive Backtracker)."""
        w, h = self.size // 2, self.size // 2
        visited = [[False for _ in range(h)] for _ in range(w)]
        walls_set = {(x, y) for x in range(self.size) for y in range(self.size)}

        def walk(x, y):
            visited[x][y] = True
            walls_set.discard((x*2, y*2))
            dirs = [(0, 1), (0, -1), (1, 0), (-1, 0)]
            random.shuffle(dirs)
            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                if 0 <= nx < w and 0 <= ny < h and not visited[nx][ny]:
                    walls_set.discard((x*2 + dx, y*2 + dy))
                    walk(nx, ny)

        walk(0, 0)
        self.walls = [list(w) for w in walls_set]

    def _find_dead_ends(self):
        """Najde všechny buňky, které mají pouze jednoho souseda (slepé uličky)."""
        dead_ends = []
        wall_lookup = {tuple(w) for w in self.walls}
        for x in range(self.size):
            for y in range(self.size):
                if (x, y) in wall_lookup: continue
                
                neighbors = 0
                for dx, dy in [(0,1), (0,-1), (1,0), (-1,0)]:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < self.size and 0 <= ny < self.size:
                        if (nx, ny) not in wall_lookup:
                            neighbors += 1
                
                if neighbors == 1:
                    dead_ends.append((x, y))
        return dead_ends

    def check_victory(self, players):
        p_pos = [(p['x'], p['y']) for p in players.values()]
        
        # Dynamicky počítáme aktivní spínače podle pozic
        self.active_switches = [i for i, sw in enumerate(self.switches) if tuple(sw) in p_pos]

        # Pokud brána ještě není otevřená, zkusíme ji otevřít. Jednou otevřená zůstane otevřená.
        if not self.gate_open and len(self.active_switches) >= len(self.switches):
            self.gate_open = True
        
        if self.gate_open:
            # Pokud je brána otevřená, ukážeme všechny spínače jako aktivní
            self.active_switches = list(range(len(self.switches)))

            # Vítězství: Všichni v cíli (modrý čtverec)
            at_target = sum(1 for p in players.values() if (p['x'], p['y']) == self.target)
            return at_target >= len(players) and len(players) > 0

        return False

def _execute_student_code(code, tests, result_queue):
    """Spustí kód studenta v odděleném procesu a otestuje ho."""
    try:
        # Vytvoření prostoru jmen pro exec
        local_scope = {}
        exec(code, {"__builtins__": __builtins__}, local_scope)
        
        # Předpokládáme, že kód definuje funkci se jménem z 'template'
        # Toto je zjednodušení, v praxi by se jméno funkce muselo zjistit jinak
        fn_name = "soucet" # TODO: Dynamically get function name
        student_fn = local_scope.get(fn_name)
        
        if not callable(student_fn):
            result_queue.put({"error": f"Funkce '{fn_name}' nebyla v kódu nalezena nebo se nejedná o funkci."})
            return

        results = []
        for test in tests:
            test_input = test["input"]
            expected = test["output"]
            try:
                actual = student_fn(*test_input)
                results.append(actual == expected)
            except Exception as e:
                results.append(False)
        
        result_queue.put({"results": results})

    except Exception as e:
        # Odeslání chyby při kompilaci nebo spuštění
        result_queue.put({"error": f"Chyba při spuštění kódu: {e}"})

class CodingLevel(BaseLevel):
    """Level, kde studenti píší a odesílají kód ke splnění úkolu."""
    def __init__(self, config, players_count):
        super().__init__(config, players_count)
        self.template = config.get("template", "")
        self.tests = config.get("tests", [])
        self.solved_by = set() # Množina ID hráčů, kteří úkol vyřešili
        self.player_progress = {}

    def run_tests(self, code):
        """Spustí testy pro daný kód v bezpečném sandboxu."""
        result_queue = multiprocessing.Queue()
        process = multiprocessing.Process(target=_execute_student_code, args=(code, self.tests, result_queue))
        process.start()
        
        # Počkáme na výsledek, ale s časovým limitem (např. 2 sekundy)
        process.join(2)
        
        if process.is_alive():
            process.terminate()
            process.join()
            return {"error": "Časový limit pro provedení kódu vypršel!"}
            
        try:
            return result_queue.get_nowait()
        except:
            return {"error": "Nepodařilo se získat výsledek z testovacího procesu."}

    def check_victory(self, players):
        """Vítězství nastane, když všichni hráči úspěšně vyřeší úkol."""
        return len(self.solved_by) >= len(players) and len(players) > 0
        