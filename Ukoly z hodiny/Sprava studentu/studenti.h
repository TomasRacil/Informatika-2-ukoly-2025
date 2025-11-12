#include <iostream>

using namespace std;

class Studenti{
    public:
        int id;
        string name;
        double prumer;
};

class LinkedList {
    private:
        Node **pHead;
        Studenti newStudent;
    public:
        Node(Studenti newStudent){
            Studenti = newStudent
        }

};

class Node {
    public:
        Studenti student;
        Node *next;

        Node(Studenti newStudent){
            student = newStudent;
            next = nullptr;
        }

        Node *operator[](int index){
            Node *current = this;
            for(int i = 0; i < index; i++){
                if(current == nullptr){
                    return nullptr;
                }
                current = current -> next;
            }
            return current;
        }
};