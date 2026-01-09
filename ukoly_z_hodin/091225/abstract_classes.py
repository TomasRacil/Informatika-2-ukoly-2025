from abc import ABC, abstractmethod

class Platba(ABC):
    def proved_platbu(self, castka):
        pass

class PlatbaKartou(Platba):
    def __init__(self, card_number):
        self.card_number = card_number
        pass

    def proved_platbu(self, castka):
        print(f"Provedena platba kartou, s cislem ${self.card_number} v hodnote: {castka}!")
        pass

class PlatbaPrevodem(Platba):
    def __init__(self, account_number):
        self.account_number = account_number
        pass 

    def proved_platbu(self, castka):
        print(f"Provedena platba prevodem, s cislem ${self.account_number} v hodnote: {castka}!")
        pass

platby = [
    [PlatbaKartou("13445"), 100],
    [PlatbaPrevodem("357445"), 250],
    [PlatbaPrevodem("77445"), 224]
]

for p in platby:
    p[0].proved_platbu(p[1])