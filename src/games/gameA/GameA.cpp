#include "GameA.hpp"
#include <unistd.h>


CharPosition::CharPosition(int col, int row)
{
    x = col;
    y = row;
}

CharPosition::CharPosition()
{
    x = 0;
    y = 0;
}

fSnakeGame::fSnakeGame()
{
    srand(time(NULL));
    InitGameWindow();
    posFruit();
    DrawWindow();
    DrawSnake();
    PrintScore();
    refresh();
}

fSnakeGame::~fSnakeGame()
{
    nodelay(stdscr, false);
    getch();
    endwin();
}

void fSnakeGame::InitGameWindow()
{
    initscr();
    nodelay(stdscr,TRUE);
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    getmaxyx(stdscr, maxheight, maxwidth);
    return;
}

void fSnakeGame::DrawWindow()
{
    for (int i = 0; i < maxwidth; i++) {
        move(0, i);
        addch(edgechar);
    }
    for (int i = 0; i < maxwidth; i++) {
        move(maxheight - 2, i);
        addch(edgechar);
    }
    for (int i = 0; i < maxheight - 1; i++) {
        move(i, 0);
        addch(edgechar);
    }
    for (int i = 0; i < maxheight - 1; i++) {
        move(i, maxwidth - 1);
        addch(edgechar);
    }
    return;
}

void fSnakeGame::DrawSnake()
{
    for (int i = 0; i < 5; i++)
        snake.push_back(CharPosition(30 + i, 10));
    for (int i = 0; i < snake.size(); i++) {
        move(snake[i].y, snake[i].x);
        addch(partchar);
    }
    return;
}

void fSnakeGame::PrintScore()
{
    move(maxheight-1, 0);
    printw("Score: %d", score);
    return;
}

void fSnakeGame::posFruit()
{
    while(1) {
        int tmpx = rand() % maxwidth + 1;
        int tmpy = rand() % maxheight + 1;
        for (int i = 0; i < snake.size(); i++)
            if (snake[i].x == tmpx && snake[i].y == tmpy)
                continue;
        if (tmpx >= maxwidth-2 || tmpy >= maxheight - 3)
            continue;
        fruit.x = tmpx;
        fruit.y = tmpy;
        break;
    }
    move(fruit.y, fruit.x);
    addch(fruitchar);
    refresh();
}

bool fSnakeGame::Collision()
{
    if (snake[0].x == 0 || snake[0].x == maxwidth - 1 || snake[0].y == 0 || snake[0].y == maxheight - 2)
        return true;
    for (int i = 2; i < snake.size(); i++)
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return true;
    return false;
}

bool fSnakeGame::GetsFruit()
{
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        posFruit();
        score += 10;
        PrintScore();
        if ((score%100) == 0)
            del -= 1000;
        return eatsFruit = true;
    } else
        return eatsFruit = false;
    return eatsFruit;
}

void fSnakeGame::MoveSnake()
{
    int key = getch();

    switch(key) {
        case KEY_LEFT:
            direction = (direction != 'r') ? 'l' : direction;
            break;
        case KEY_RIGHT:
            direction = (direction != 'l') ? 'r' : direction;
            break;
        case KEY_UP:
            direction = (direction != 'd') ? 'u' : direction;
            break;
        case KEY_DOWN:
            direction = (direction != 'u') ? 'd' : direction;
            break;
        case KEY_BACKSPACE:
            direction = 'q';
            break;
    }
    if (!eatsFruit) {
        move(snake[snake.size() - 1].y, snake[snake.size() - 1].x);
        printw(" ");
        refresh();
        snake.pop_back();
    }
    switch(direction) {
        case 'l':
            snake.insert(snake.begin(), CharPosition(snake[0].x - 1, snake[0].y));
            break;
        case 'r':
            snake.insert(snake.begin(), CharPosition(snake[0].x + 1, snake[0].y));
            break;
        case 'u':
            snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y - 1));
            break;
        case 'd':
            snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y + 1));
            break;
    }
    move(snake[0].y, snake[0].x);
    addch(partchar);
    refresh();
    return;
}

void fSnakeGame::PlayGame()
{
    while(1)
    {
        if (Collision()) {
            move((maxheight - 2) / 2,(maxwidth - 5) / 2);
            printw("GAME OVER");
            break;
        }
        GetsFruit();
        MoveSnake();
        if (direction == 'q') {
            break;
        }
        usleep(del);
    }
}
