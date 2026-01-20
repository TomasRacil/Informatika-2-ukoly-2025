#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include <errno.h>

static struct termios orig_termios;
static int orig_flags = -1;

static void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    if (orig_flags != -1)
        fcntl(STDIN_FILENO, F_SETFL, orig_flags);
}

static void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    orig_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, orig_flags | O_NONBLOCK);
}

static int readCharNonBlocking()
{
    char c;
    int n = static_cast<int>(read(STDIN_FILENO, &c, 1));
    if (n == 1) return static_cast<unsigned char>(c);
    if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) return -1;
    return -1;
}

static bool gameOver;
static const int width  = 20;
static const int height = 20;

static int x, y, fruitX, fruitY, score;
static std::vector<int> tailX;
static std::vector<int> tailY;
static int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
static eDirection dir;

static void Setup()
{
    gameOver = false;
    dir      = RIGHT;
    x        = width / 2;
    y        = height / 2;
    fruitX   = rand() % width;
    fruitY   = rand() % height;
    score    = 0;
    nTail    = 0;
    tailX.clear();
    tailY.clear();
}

static void Draw()
{
    system("clear");

    for (int i = 0; i < width + 2; ++i) std::cout << '#';
    std::cout << '\n';

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (j == 0) std::cout << '#';

            if (i == y && j == x)
                std::cout << 'O';
            else if (i == fruitY && j == fruitX)
                std::cout << 'F';
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; ++k)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << 'o';
                        print = true;
                        break;
                    }
                }
                if (!print) std::cout << ' ';
            }

            if (j == width - 1) std::cout << '#';
        }
        std::cout << '\n';
    }

    for (int i = 0; i < width + 2; ++i) std::cout << '#';
    std::cout << '\n';

    std::cout << "Skóre: " << score << std::endl;
}

static void Input()
{
    int c = readCharNonBlocking();
    if (c == -1) return;

    switch (c)
    {
    case 'a': case 'A':
        if (dir != RIGHT) dir = LEFT;
        break;
    case 'd': case 'D':
        if (dir != LEFT) dir = RIGHT;
        break;
    case 'w': case 'W':
        if (dir != DOWN) dir = UP;
        break;
    case 's': case 'S':
        if (dir != UP) dir = DOWN;
        break;
    case 'x': case 'X':
        gameOver = true;
        break;
    default:
        break;
    }
}

static void Logic()
{
    int prevX = nTail > 0 ? tailX[0] : x;
    int prevY = nTail > 0 ? tailY[0] : y;
    int prev2X, prev2Y;

    if (nTail > 0)
    {
        tailX[0] = x;
        tailY[0] = y;
    }

    for (int i = 1; i < nTail; ++i)
    {
        prev2X   = tailX[i];
        prev2Y   = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX    = prev2X;
        prevY    = prev2Y;
    }

    switch (dir)
    {
    case LEFT:  --x; break;
    case RIGHT: ++x; break;
    case UP:    --y; break;
    case DOWN:  ++y; break;
    default: break;
    }

    // kolize se stěnou => konec
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        gameOver = true;
        return;
    }

    // kolize se svým ocasem
    for (int i = 0; i < nTail; ++i)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // sežrání ovoce
    if (x == fruitX && y == fruitY)
    {
        score += 10;

        // nové ovoce mimo hada
        while (true)
        {
            fruitX = rand() % width;
            fruitY = rand() % height;

            bool onTail = false;
            for (int i = 0; i < nTail; ++i)
                if (tailX[i] == fruitX && tailY[i] == fruitY)
                {
                    onTail = true;
                    break;
                }

            if (!onTail && !(fruitX == x && fruitY == y))
                break;
        }

        ++nTail;
        tailX.push_back(0);
        tailY.push_back(0);
    }
}

// ------------------------------------------------------------
// VEŘEJNÁ FUNKCE – TUTO VOLÁŠ Z backend_automatu.cpp
// ------------------------------------------------------------

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    enableRawMode();
    atexit(disableRawMode); // pro jistotu, ale stejně ještě jednou voláme ručně

    Setup();

    using clock = std::chrono::steady_clock;
    auto last_move = clock::now();
    const std::chrono::milliseconds move_interval(400);

    while (!gameOver)
    {
        Draw();
        Input();

        auto now = clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_move) >= move_interval)
        {
            Logic();
            last_move = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }

    disableRawMode();
    std::cout << "Konec hry. Skóre: " << score << std::endl;
    return 0;
}