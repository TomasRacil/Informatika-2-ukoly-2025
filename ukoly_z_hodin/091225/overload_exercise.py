from __future__ import annotations

class Time:
    def __init__(self, hours, minutes):
        self.__hours = hours % 24 # private prooperty
        self.__minutes = minutes % 60 # private property

    @property
    def hours(self):
        return self.__hours
        
    @hours.setter 
    def hours(self, hours):
        if (isinstance(hours, int)):
            self.__hours = hours 
        elif hours.isdigit():
            self.__hours = hours 
        else:
            print("[!] Incorrect value")

    @property
    def minutes(self):
        return self.__minutes
    
    @minutes.setter
    def minutes(self, minutes):
        if (isinstance(minutes, int)):
            self.__minutes = minutes 
        elif minutes.isdigit():
            self.__minutes = minutes 
        else:
            print("[!] Incorrect value")
            return 
        
        if (self.__minutes >= 60):
            self.__hours += self.__minutes // 60
            self.__minutes = self.__minutes % 60

    def __add__(self, other:Time)->Time:
        return Time(self.hours + other.hours, self.minutes + other.minutes)
    
    def __str__(self):
        return f"{self.__hours}:{self.__minutes}"

    


cas = Time(14, 60)
cas2 = Time(10, 00)

print(cas+cas2)