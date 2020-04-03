#include "SFMLModule.hpp"
#include <sys/ioctl.h>

extern "C" Module *create()
{
    return new SFMLModule;
}

extern "C" void destroy(Module *module)
{
    delete(module);
}

SFMLModule::SFMLModule()
{
}

SFMLModule::~SFMLModule()
{
}

void SFMLModule::initWindow(const size_t &width, const size_t &height, const std::string &title)
{
    struct winsize size;

    ioctl(1, TIOCGWINSZ, &size);
    _size.wUnit = size.ws_xpixel / size.ws_col;
    _size.hUnit = size.ws_ypixel / size.ws_row;
    _size.w = _size.wUnit * width;
    _size.h = _size.hUnit * height;
    _sfWindow.setSize(sf::Vector2u(_size.w, _size.h));
    _sfWindow.setTitle(title);
}

void SFMLModule::destroyWindow()
{
    _sfWindow.clear();
    _sfWindow.close();
}

void SFMLModule::render(const std::map<std::string, Object> &gameDatas)
{
    _sfWindow.clear();
    for (std::pair<std::string, Object> i : gameDatas) {
        _sfWindow.draw(i.second.getSfSprite());
    }
    _sfWindow.display();
}

int SFMLModule::getInputs()
{
    sf::Event event;

    while (_sfWindow.pollEvent(event))
        if (event.type == sf::Event::KeyPressed)
            return event.key.code;
    return -1;
}