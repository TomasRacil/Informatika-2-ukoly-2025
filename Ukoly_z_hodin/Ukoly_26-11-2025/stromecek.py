import random
import time
def stromecek(vyska):
    for i in range(vyska):
        print(" " * (vyska - i)+ "*" * (2*i+1))
    for j in range(2):
        print(" " * vyska + "|| ")

stromecek(6)