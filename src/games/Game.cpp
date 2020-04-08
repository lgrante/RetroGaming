#include "Game.hpp"

const std::string &Game::getName() const
{
    return _name;
}

Module *Game::getModule() const
{
    return _module;
}

const std::map<std::string, Object> &Game::getData() const
{
    return _data;
}

const uint16_t &Game::getScore() const
{
    return _score;
}

void Game::setName(const std::string &name)
{
    _name = name;
}

void Game::setModule(Module *module)
{
    _module = module;
}

void Game::setData(const std::map<std::string, Object> &data)
{
    _data = data;
}

void Game::setScore(const uint16_t &score)
{
    _score = score;
}

int Game::readMoveKey(int &xOff, int &yOff)
{
    int input = -1;

    switch((input = _module->getInputs())) {
        case 'e':
            xOff = 0;
            yOff = -1;
            break;
        case 'd':
            xOff = 0;
            yOff = 1;
            break;
        case 's':
            xOff = -1;
            yOff = 0;
            break;
        case 'f':
            xOff = 1;
            yOff = 0;
    }
    return input;
}

void Game::endGame()
{
    _module->destroyAll(_data);
}