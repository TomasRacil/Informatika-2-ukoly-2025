#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

class Ship
{
private:
    int x = 0;
    int y = 0;
    char facing = 'E';
    string file_name;
    ifstream soubor;

public:
    Ship(string file_name)
    {
        this->file_name = file_name;

        soubor.open(file_name);

        if (!soubor.is_open())
        {
            cerr << "Chyba souboru nelze otevrit: " << file_name << endl;
        }

        string line;

        while (getline(soubor, line))
        {
            char direction = line[0];
            int units = stoi(line.substr(1));

            cout << "unit: " << units << endl;
            move(direction, units);
        }

        cout << "final, x: " << x << ", y:" << y;

        int mnthn_dis = abs(x) + abs(y);

        cout << "Manhattan distance: " << mnthn_dis << endl;
    }
    void change_direction(char input, int degrees)
    {
        int turns = (degrees / 90) % 4;

        char direction = facing;

        if (input == 'L')
        {
            for (int i = 0; i < turns; i++)
            {
                switch (direction)
                {
                case 'N':
                    direction = 'W';
                    break;
                case 'W':
                    direction = 'S';
                    break;
                case 'S':
                    direction = 'E';
                    break;
                case 'E':
                    direction = 'N';
                    break;
                }
            }
        }
        else if (input == 'R')
        {
             for (int i = 0; i < turns; i++)
            {
                switch (direction)
                {
                case 'N':
                    direction = 'E';
                    break;
                case 'E':
                    direction = 'S';
                    break;
                case 'S':
                    direction = 'W';
                    break;
                case 'W':
                    direction = 'N';
                    break;
                }
            }
        }
    
        this->facing = direction;
    }

    void move(char direction, int units)
    {
        switch (direction)
        {
        case 'N':
            y += units;
            break;
        case 'S':
            y -= units;
            break;
        case 'W':
            x -= units;
            break;
        case 'E':
            x += units;
            break;
        case 'F':
            move(facing, units);
            break;
        case 'R':
            change_direction(direction, units);
            break;
        case 'L':
            change_direction(direction, units);
            break;
        default:
            break;
        }
    }
};

int main()
{
    Ship new_ship("data.txt");
}