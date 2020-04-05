#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#ifndef FSNAKEGAME_H
#define FSNAKEGAME_H

struct CharPosition
{
    int x;
    int y;
    CharPosition(int col, int row);
    CharPosition();
};

class fSnakeGame
{
private:
    int score = 0;
    int del = 110000;
    int maxwidth;
    int maxheight;
    char direction = 'l';
    char partchar = 'x';
    char edgechar = (char)219;;
    char fruitchar = '*';
    bool eatsFruit = 0;
    CharPosition fruit;
    std::vector<CharPosition> snake;

    void InitGameWindow();
    void DrawWindow();
    void DrawSnake();
    void PrintScore();
    void posFruit();
    bool Collision();
    void MoveSnake();
    bool GetsFruit();

public:
    fSnakeGame();
    ~fSnakeGame();
    void PlayGame();
};

#endif