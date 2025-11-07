#include <iostream>
#include <bitset>
#include <bit>
#include <cmath>

using namespace std;

long int generator(long int num, int factor)
{
    return (num * factor) % 2147483647;
}

int main()
{
    int a_starter = 65;   // 65; // 516;
    int b_starter = 8921; // 8921;// 190;

    int a_generator = 16807;
    int b_generator = 48271;

    long int a_result = a_starter;
    long int b_result = b_starter;

    int gen_amount = 5000000;

    int matches = 0;

    int valid_pairs = 0;

    while (valid_pairs < gen_amount)
    {
        // Generate next valid numbers
        do
        {
            a_result = generator(a_result, a_generator);
        } while (a_result % 4 != 0);
        do
        {
            b_result = generator(b_result, b_generator);
        } while (b_result % 8 != 0);

        // Compare lower 16 bits
        if ((a_result & 0xFFFF) == (b_result & 0xFFFF))
            matches++;

        valid_pairs++;
    }

    /* for (int i = 0; i < gen_amount; i++)
    {
        a_result = generator(a_result, a_generator);
        b_result = generator(b_result, b_generator);

        do
        {
            a_result = generator(a_result, a_generator);
        } while (a_result % 4 != 0);

        do
        {
            b_result = generator(b_result, b_generator);
        } while (b_result % 8 != 0);

        bitset<16> a_bits(a_result);
        bitset<16> b_bits(b_result);

        if (a_bits == b_bits)
        {
            matches++;
        }
    } */
    cout << matches;
}