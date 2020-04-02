#include "Module.hpp"

void Module::setObjectTexture(std::map<std::string, Object> &gameDatas, const std::string &name, const std::string &sfTexturePath, const std::string &ncTexturePath)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end())
        it->second.setTexture(sfTexturePath, ncTexturePath);
}

void Module::destroyObject(std::map<std::string, Object> &gameDatas, const std::string &name)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end())
        gameDatas.erase(it);
}