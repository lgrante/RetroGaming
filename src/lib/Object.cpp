#include "Object.hpp"

Object::Object(const std::string &sfTexturePath, const std::string &ncTexturePath)
{
    setTexture(sfTexturePath, ncTexturePath);
}

Object::Object(const std::string &sfTexturePath, const std::string &ncTexturePath, const int &x, const int &y)
    : _x(x), _y(y)
{
    setTexture(sfTexturePath, ncTexturePath);
}

void Object::setTexture(const std::string &sfTexturePath, const std::string &ncTexturePath)
{
    if (_sfTexture.loadFromFile(sfTexturePath) == false)
        throw InitTextureException("Failed to laod texture from file" + sfTexturePath, __LINE__);
    _sprite = sf::Sprite(_sfTexture);
    _ncTexture = NCurseTexture(ncTexturePath);
}

void Object::setX(int x)
{
    _x = x;
}

void Object::setY(int y)
{
    _y = y;
}

const sf::Sprite &Object::getSfSprite() const
{
    return _sprite;
}

const sf::Texture &Object::getSfTexture() const
{
    return _sfTexture;
}

const NCurseTexture &Object::getNcTexture() const
{
    return _ncTexture;
}

const int &Object::getX() const
{
    return _x;
}

const int &Object::getY() const
{
    return _y;
}