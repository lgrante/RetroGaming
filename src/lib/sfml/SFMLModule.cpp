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
    _sizeUnit.x = size.ws_xpixel / size.ws_col;
    _sizeUnit.y = size.ws_ypixel / size.ws_row;
    _width = _sizeUnit.x * width;
    _height = _sizeUnit.y * height;
    _sfWindow.setSize(sf::Vector2u(_width, _height));
    _sfWindow.setTitle(title);
}

void SFMLModule::destroyWindow()
{
    _sfWindow.clear();
    _sfWindow.close();
}

void SFMLModule::setObject(
    std::map<std::string, Object> &gameDatas,
    const std::string &name, const std::string &sfTexturePath, const std::string &ncTexturePath, 
    const int &x, const int &y
)
{
    sf::Vector2u coordinatesPxl(x * _sizeUnit.x, y * _sizeUnit.y);

    if (x >= 0 && x <= (int) coordinatesPxl.x && y >= 0 && y <= (int) coordinatesPxl.y) {
        Object newObject(sfTexturePath, ncTexturePath, x * _sizeUnit.x, y * _sizeUnit.y);

        gameDatas.emplace(name, newObject);
    }
}

void SFMLModule::setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);
    sf::Vector2u coordinatesPxl(x * _sizeUnit.x, y * _sizeUnit.y);

    if (x >= 0 && x <= (int) coordinatesPxl.x && y >= 0 && y <= (int) coordinatesPxl.y) {
        it->second.setX(coordinatesPxl.x);
        it->second.setY(coordinatesPxl.y);
    }
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

    while (_sfWindow.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed)
            return event.key.code;
    }
    return -1;
}