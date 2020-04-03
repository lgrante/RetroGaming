#include "Module.hpp"

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
        if (it->second.getSdlTexture() != nullptr)
            SDL_FreeSurface(it->second.getSdlTexture());
        gameDatas.erase(it);
    }
}