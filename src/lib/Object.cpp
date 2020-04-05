#include "Object.hpp"

Object::Object(const std::string &sfTexturePath, const std::string &ncTexturePath, const std::string &sdlTexturePath)
{
    setTexture(sfTexturePath, ncTexturePath, sdlTexturePath);
}

Object::Object(const std::string &sfTexturePath, const std::string &ncTexturePath, const std::string &sdlTexturePath, const int &x, const int &y)
    : _x(x), _y(y)
{
    setTexture(sfTexturePath, ncTexturePath, sdlTexturePath);
}

void Object::setTexture(const std::string &sfTexturePath, const std::string &ncTexturePath, const std::string &sdlTexturePath)
{
    SDL_Surface *buffer = NULL;

    /**
     * @note Loading SFML Texture.
     */
    if (_sfTexture.loadFromFile(sfTexturePath) == false)
        throw InitTextureException("Failed to laod texture from file" + sfTexturePath, __FILE__, __LINE__);
    _sprite = sf::Sprite(_sfTexture);

    /**
     * @note Loading SDL Texture.
     */
    buffer = SDL_LoadBMP(sdlTexturePath.c_str());
	_sdlTexture = SDL_DisplayFormat(buffer);
	SDL_FreeSurface(buffer);

    /**
     * @note Loading NCurse Texture.
     */
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

void Object::setWidth(int width)
{
    _width = width;
}

void Object::setHeight(int height)
{
    _height = height;
}

const sf::Sprite &Object::getSfSprite() const
{
    return _sprite;
}

const sf::Texture &Object::getSfTexture() const
{
    return _sfTexture;
}

SDL_Surface *Object::getSdlTexture() const
{
    return _sdlTexture;
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

const int &Object::getWidth() const
{
    return _width;
}

const int &Object::getHeight() const
{
    return _height;
}