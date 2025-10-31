#include <iostream>
using namespace std;

int* genrovat_cisla(int velikost){
    int* pole = new int[velikost];
    //random
    for(int i = 0; i < velikost; i++){
        pole[i] = rand()%100; 
    }
    return pole;
}
void vypis_cisla(int* pole, int velikost){
    for(int i = 0; i < velikost; i++){
        cout << pole[i] << " ";
    }
    cout << endl;
}
int* selection_sort(int* pole, int velikost){
    for(int i = 0; i < velikost - 1; i++){
        int min_index = i;
        for(int j = i + 1; j < velikost; j++){
            if(pole[j] < pole[min_index]){
                min_index = j;
            }
        }
        swap(pole[i], pole[min_index]);
    }
    return pole;
}

int main(){
    int velikost;
    cout << "Zadejte velikost pole: ";
    cin >> velikost;
    if(velikost <= 0){
        cout << "Velikost pole musi byt kladne cislo." << endl;
        return 1;
    }
    int* pole = genrovat_cisla(velikost);
    vypis_cisla(pole, velikost);
    selection_sort(pole, velikost);
    cout << "Serazene pole: ";
    vypis_cisla(pole, velikost);
    delete[] pole;
    return 0;
}