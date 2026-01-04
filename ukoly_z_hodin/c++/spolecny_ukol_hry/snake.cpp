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

// Terminal raw mode management (set once)
static struct termios orig_termios;
static int orig_flags = -1;
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    if (orig_flags != -1) fcntl(STDIN_FILENO, F_SETFL, orig_flags);
}
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    orig_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, orig_flags | O_NONBLOCK);
}

// non-blocking read single char, returns -1 if none
int readCharNonBlocking() {
    char c;
    int n = (int)read(STDIN_FILENO, &c, 1);
    if (n == 1) return (unsigned char)c;
    if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) return -1;
    return -1;
}

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
std::vector<int> tailX;
std::vector<int> tailY;
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    // had zacne se vyskytovat pouze po prvnim stisku - ale uz jede automaticky
    dir = RIGHT;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    tailX.clear();
    tailY.clear();
}

void Draw() {
    system("clear");
    for (int i = 0; i < width + 2; i++) std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) std::cout << "#";
            if (i == y && j == x) std::cout << "O";
            else if (i == fruitY && j == fruitX) std::cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) { std::cout << "o"; print = true; break; }
                }
                if (!print) std::cout << " ";
            }
            if (j == width - 1) std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++) std::cout << "#";
    std::cout << std::endl;
    std::cout << "Skóre: " << score << std::endl;
}

void Input() {
    int c = readCharNonBlocking();
    if (c == -1) return;
    switch (c) {
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

void Logic() {
    int prevX = nTail > 0 ? tailX[0] : x;
    int prevY = nTail > 0 ? tailY[0] : y;
    int prev2X, prev2Y;

    if (nTail > 0) { tailX[0] = x; tailY[0] = y; }
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i]; prev2Y = tailY[i];
        tailX[i] = prevX; tailY[i] = prevY;
        prevX = prev2X; prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default: break;
    }

    // kolize se stenou -> konec
    if (x < 0 || x >= width || y < 0 || y >= height) { gameOver = true; return; }

    for (int i = 0; i < nTail; i++) if (tailX[i] == x && tailY[i] == y) gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        // nove ovoce mimo hada
        while (true) {
            fruitX = rand() % width; fruitY = rand() % height;
            bool onTail = false;
            for (int i = 0; i < nTail; ++i) if (tailX[i] == fruitX && tailY[i] == fruitY) { onTail = true; break; }
            if (!onTail && !(fruitX == x && fruitY == y)) break;
        }
        nTail++;
        tailX.push_back(0); tailY.push_back(0);
    }
}

int main() {
    srand((unsigned)time(nullptr));
    enableRawMode();
    atexit(disableRawMode);

    Setup();
    using clock = std::chrono::steady_clock;
    auto last_move = clock::now();
    const std::chrono::milliseconds move_interval(400); // pomalejsi (400 ms)

    while (!gameOver) {
        Draw();
        Input();
        auto now = clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_move) >= move_interval) {
            Logic();
            last_move = now;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }

    disableRawMode();
    std::cout << "Konec hry. Skóre: " << score << std::endl;
    return 0;
}