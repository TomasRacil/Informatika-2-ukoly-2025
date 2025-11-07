#pragma once

#include <string>
#include "Student.h"

// definuje strukturu Node

class Node{
private:
    Student student;
    Node *next;

public:
    Node();
    Node(Student newStudent);
    Node* get_next();
    Student get_student();
    void set_next(Node* next);
    void vypis_node();
    friend std::ostream& operator<<(std::ostream& out, Node& m);
};