#include "GameA.hpp"

extern "C" Game *create()
{
    return new NibblerGame;
}

extern "C" void destroy(Game *game)
{
    delete(game);
}

NibblerGame::NibblerGame()
{
    _name = "Nibbler";
}

NibblerGame::~NibblerGame()
{
}

void NibblerGame::launchGame()
{
    _module->renderText("Nibbler game launched!", 0, 0, CENTER | MIDDLE, NORMAL, CYAN);
    while (1);
}

void NibblerGame::coreGame()
{
}