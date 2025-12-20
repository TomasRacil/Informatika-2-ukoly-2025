#include "Node.h"
#include <iostream>
#include <iomanip>

Node::Node(){
    student = Student();
    next = nullptr;
}
Node::Node(Student newStudent)
{
    student = newStudent;
    next = nullptr;
}
Node* Node::get_next(){
    return next;
}

Student Node::get_student(){
    return student;
}

void Node::set_next(Node* next){
    this->next = next;
}

void Node::vypis_node(){
    std::cout << student <<std::endl;
}

std::ostream& operator<<(std::ostream& out, Node& m){
    out<<m.student;
    // out<<"Student: "<<m.student<< ", Adresa následujícího: "<< m.next <<std::endl;
    return out;
}

// Node *operator[](int index)
// {
//     Node *current = this;
//     for (int i = 0; i < index; i++)
//     {
//         if (current == nullptr)
//         {
//             return nullptr;
//         }
//         current = current->next;
//     }
//     return current;
// }