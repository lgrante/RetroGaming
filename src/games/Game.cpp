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