#include "SFMLModule.hpp"

extern "C" Module *create()
{
    return new SFMLModule;
}

extern "C" void destroy(Module *module)
{
    delete(module)
}

SFMLModule::SFMLModule()
{
}

SFMLModule::~SFMLModule()
{
}

void SFMLModule::initWindow(const size_t &width, const size_t &height, const std::string &title)
{
    _sfWindow = sf::RenderWindow(sf::VideoMode(width, height), title);
    
}