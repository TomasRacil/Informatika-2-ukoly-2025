#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

void vypisPole(int *pole, int velikost, int n = 10)
{
    cout << "[";
    for (int i = 0; i < velikost && i < n; ++i)
    {
        cout << pole[i] << (i == velikost - 1 || i == n - 1 ? "" : ", ");
    }
    if (velikost > n)
    {
        cout << "...";
    }
    cout << "]" << endl;
}

void tridiciFunkce(int *pole, int velikost, string algoritmus)
{
    if (algoritmus == "selection")
    {
        for (int i = 0; i < velikost; i++)
        {
            int minIndex = i;

            for (int j = i + 1; j < velikost; j++)
            {
                int current = pole[j];

                if (current < pole[minIndex])
                {
                    minIndex = j;
                }
            }

            int nejmensi_prvek = pole[minIndex];

            swap(&pole[minIndex], &pole[i]);
        }
    }

    vypisPole(pole, velikost);
}

int main()
{
    cout << "Zadejte pocet generovanych cisel: ";
    int n;
    cin >> n;
    srand(time(0));
    int *pole = new int[n];
    for (int i = 0; i < n; ++i)
    {
        pole[i] = rand();
    }
    vypisPole(pole, n);

    auto start = chrono::high_resolution_clock::now();
    tridiciFunkce(pole, n, "selection");
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Algoritmus trval: " << duration.count() << " ms" << endl;
}