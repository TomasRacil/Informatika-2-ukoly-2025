#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
void prohod(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void vypisPole(int pole[], int velikost) {
    for (int i = 0; i < velikost; i++) {
        cout << pole[i] << " ";
    }
    cout << endl;
}

/**
 * @brief Implementace algoritmu Selection Sort.
 */
void selectionSort(int velikost, int pole[]){
    for (int i = 0; i < velikost; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < velikost; j++)
        {
            if (pole[j] < pole[min_idx])
            {
                min_idx = j;
            }
            
        }
        if (min_idx != i)
        {
            prohod(&pole[min_idx], &pole[i]);
            vypisPole(pole, velikost);
        }
        
    }
    
}

int main(){
    cout<<"Zadejte pocet generovanych cisel: ";
    int n;
    cin>>n;
    srand(time(0));
    int* pole = new int[n];
    for (int i = 0; i < n; ++i){
        pole[i] = std::rand();
    }
    vypisPole(pole, n);

    auto start = chrono::high_resolution_clock::now();
    // tridici_funkce(pole, n, "selection");
    selectionSort(pole, n, "quick");
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Algoritmus trval: " << duration.count() << " ms" << endl;

    vypisPole(pole, n);

    return 0;
}