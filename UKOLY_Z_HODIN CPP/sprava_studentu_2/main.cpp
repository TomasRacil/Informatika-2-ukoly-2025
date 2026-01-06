#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

int main()
{
    string input_file = "student.txt";
    string output_file = "student_serazeno.txt";

    LinkedList ll(input_file);

    cout << "\n Pred serazenim \n";
    ll.vypisSeznam();

    cout<<ll;

    // ll.setridSeznamPodlePrumeru();

    cout << "\n Po serazeni \n";
    ll.vypisSeznam();

    Student st = Student{111,"Karel Hajek", 4.3};

    ll.pridejStudentaNaKonec(st);

    cout << "\n Po pridani \n";
    ll.vypisSeznam();

    return 0;
}