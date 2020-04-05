#include "Module.hpp"

void Module::_computeTextPosition(int &x, int &y, uint16_t alignment, uint16_t textWidth)
{
    /*
    std::cout << "Text width: " << textWidth << std::endl;
    std::cout << "X unit: " << _size.wUnit << " | Y unit: " << _size.hUnit << std::endl;
    std::cout << "Width: " << _size.w << " | Height: " << _size.h << std::endl;
    */
    x *= _size.wUnit;
    y *= _size.hUnit;
    //std::cout << "X: " << x << " | Y: " << y << std::endl;
    x += (alignment & CENTER) ? ((_size.w / 2) - (textWidth / 2)) : 0;
    //std::cout << "X: " << x << " | Y: " << y << std::endl;
    x += (alignment & RIGHT) ? (_size.w - _size.wUnit - textWidth) : 0;
    //std::cout << "X: " << x << " | Y: " << y << std::endl;
    y += (alignment & MIDDLE) ? (_size.h / 2) : 0;
    //std::cout << "X: " << x << " | Y: " << y << std::endl;
    y += (alignment & BOTTOM) ? (_size.h - _size.hUnit) : 0; 
    //std::cout << "X: " << x << " | Y: " << y << std::endl;
}

const module &Module::getModule() const
{
    return _module;
}

void Module::setObject(
    std::map<std::string, Object> &gameDatas, const std::string &name, 
    const std::string &sfTexturePath, const std::string &sdlTexturePath, const std::string &ncTexturePath, 
    const int &x, const int &y
)
{
    Object newObject(sfTexturePath, sdlTexturePath, ncTexturePath, 0, 0);

    if (x >= 0 && x <= _size.getWidthInUnit() && y >= 0 && y <= _size.getHeightInUnit()) {
        newObject.setX(x * _size.wUnit);
        newObject.setY(y * _size.hUnit);
        newObject.setWidth(_size.wUnit);
        newObject.setHeight(_size.wUnit);
    }
    gameDatas.emplace(name, newObject);
}

void Module::setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end() && x >= 0 && x <= _size.getWidthInUnit() && y >= 0 && y <= _size.getHeightInUnit()) {
        it->second.setX(x * _size.wUnit);
        it->second.setY(y * _size.hUnit);
    }
}

void Module::setObjectTexture(std::map<std::string, Object> &gameDatas, const std::string &name, const std::string &sfTexturePath, const std::string &sdlTexturePath, const std::string &ncTexturePath)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end())
        it->second.setTexture(sfTexturePath, sdlTexturePath, ncTexturePath);
}

void Module::destroyObject(std::map<std::string, Object> &gameDatas, const std::string &name)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end()) {
        /*
        if (it->second.getSdlTexture() != nullptr)
            SDL_FreeSurface(it->second.getSdlTexture());
            */
        gameDatas.erase(it);
    }
}