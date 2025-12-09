#include <iostream>
#include <ctime>
#include <chrono>

void prohod(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void tridiciFunkce(int* pole, int velikost, std::string algoritmus){
    for(int i=0; i<velikost-1; i++){
        int minIndex = i;
        for(int j=i+1; j<velikost; j++){
            if(pole[j] < pole[minIndex]){
                minIndex = j;
            }
        }
        if (minIndex != i){
            prohod(&pole[minIndex], &pole[i]);
        }
    }
    

}


void vypisPole(int* pole, int velikost, int n = 10) {
    std::cout << "[";
    for (int i = 0; i < velikost && i < n; ++i) {
        std::cout << pole[i] << (i == velikost - 1 || i == n - 1 ? "" : ", ");
    }
    if (velikost > n) {
        std::cout << "...";
    }
    std::cout << "]" << std::endl;
}

void vypisVysledek(int pole[], int velikost) {
    for (int i = 0; i < velikost; i++) {
        std::cout << pole[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::cout<<"Zadejte pocet generovanych cisel: ";
    int n;
    std::cin>>n;
    std::srand(std::time(0));
    int* pole = new int[n];
    for (int i = 0; i < n; ++i){
        pole[i] = std::rand();
    }
    vypisPole(pole, n);

    auto start = std::chrono::high_resolution_clock::now();
    tridiciFunkce(pole, n, "selection");
    vypisVysledek(pole, n);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Algoritmus trval: " << duration.count() << " ms" << std::endl;

}