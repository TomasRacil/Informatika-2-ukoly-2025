class Clovek:
    def __init__(self, jmeno):
        Clovek.name = jmeno

class Student(Clovek):
    def __init__(self, jmeno):
        super().__init__(jmeno)

print(Clovek("hello").name)