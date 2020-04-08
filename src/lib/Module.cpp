#include "Module.hpp"

void Module::_computePosition(int &x, int &y, uint16_t alignment, uint16_t textWidth)
{
    x *= _size.wUnit;
    y *= _size.hUnit;
    x += (alignment & CENTER) ? ((_size.w / 2) - (textWidth / 2)) : 0;
    x += (alignment & RIGHT) ? (_size.w - _size.wUnit - textWidth) : 0;
    y += (alignment & MIDDLE) ? (_size.h / 2) : 0;
    y += (alignment & BOTTOM) ? (_size.h - _size.hUnit * 2) : 0;
}

const module &Module::getModule() const
{
    return _module;
}

void Module::getWindowSize(int &width, int &height, bool pixelSize)
{
    width = (pixelSize) ? _size.w : _size.getWidthInUnit();
    height = (pixelSize) ? _size.h : _size.getHeightInUnit();
}

void Module::setObject(
    std::map<std::string, Object> &gameDatas, const std::string &name, 
    const std::string &graphicTexturePath, const std::string &textTexturePath, 
    const int &x, const int &y, uint16_t alignment
)
{
    Object newObject;
    int xPxl = x, yPxl = y;

    _computePosition(xPxl, yPxl, alignment, _size.wUnit);
    if (xPxl >= 0 && xPxl <= (int) _size.w && yPxl >= 0 && yPxl <= (int) _size.h) {
        newObject.setX(xPxl);
        newObject.setY(yPxl);
        newObject.setWidth(_size.wUnit);
        newObject.setHeight(_size.hUnit);
        newObject.setTexture(graphicTexturePath, textTexturePath);
        gameDatas.emplace(name, newObject);
    }
}

void Module::setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y, uint16_t alignment)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);
    int xPxl = x, yPxl = y;

    _computePosition(xPxl, yPxl, alignment, _size.wUnit);
    if (it != gameDatas.end() && xPxl >= 0 && xPxl <= (int) _size.w && yPxl >= 0 && yPxl <= (int) _size.h) {
        it->second.setX(xPxl);
        it->second.setY(yPxl);
    }
}

void Module::getObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, int &x, int &y)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end()) {
        x = it->second.getX() / _size.wUnit;
        y = it->second.getY() / _size.hUnit;
    }
}

void Module::moveObject(std::map<std::string, Object> &gameDatas, const std::string &name, const int &xOff, const int &yOff)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);
    int xPxl = 0, yPxl = 0;

    if (it == gameDatas.end())
        return;
    xPxl = it->second.getX() + (xOff * _size.wUnit);
    yPxl = it->second.getY() + (yOff * _size.hUnit);
    if (xPxl >= 0 && xPxl <= (int) _size.w && yPxl >= 0 && yPxl <= (int) _size.h) {
        it->second.setX(xPxl);
        it->second.setY(yPxl);
    }
}

void Module::moveObject(std::map<std::string, Object> &gameDatas, const std::string &name, const std::string &targetName)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);
    int targetX = 0, targetY = 0;

    getObjectCoordinates(gameDatas, targetName, targetX, targetY);
    _computePosition(targetX, targetY, TOP | LEFT, _size.wUnit);
    it->second.setX(targetX);
    it->second.setY(targetY);
}

void Module::setObjectTexture(std::map<std::string, Object> &gameDatas, const std::string &name, const std::string &graphicTexturePath, const std::string &textTexturePath)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end())
        it->second.setTexture(graphicTexturePath, textTexturePath);
}

void Module::destroyObject(std::map<std::string, Object> &gameDatas, const std::string &name)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end()) {
        if (it->second.getSdlTexture() != nullptr)
            SDL_FreeSurface(it->second.getSdlTexture());
        gameDatas.erase(it);
    }
}

void Module::destroyAll(std::map<std::string, Object> &gameDatas)
{
    for (std::pair<std::string, Object> i : gameDatas)
        SDL_FreeSurface(i.second.getSdlTexture());
    gameDatas.clear();
}