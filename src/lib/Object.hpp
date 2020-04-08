#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Main.hpp"
#include "Errors.hpp"
#include "Constants.hpp"

class Object
{
    private:
        int _x;
        int _y;
        int _width;
        int _height;

        std::shared_ptr<sf::Sprite> _sfSprite;
        std::shared_ptr<sf::Texture> _sfTexture;

        SDL_Surface *_sdlTexture;

        wchar_t _ncTexture;
        color _ncFgColor; 
        color _ncBgColor;
        uint16_t _ncStyle;

        std::vector<std::string> _splitStr(const std::string &line, char split);
        void _loadNCurseTexture(const std::string &texturePath);
    public:
        Object();

        void setTexture(const std::string &graphicTexturePath, const std::string &textTexturePath);
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        
        sf::Sprite *getSfSprite() const;
        sf::Texture *getSfTexture() const;
        SDL_Surface *getSdlTexture() const;
        const wchar_t &getNcTexture() const;
        const color &getNcFgColor() const;
        const color &getNcBgColor() const;
        const uint16_t &getNcStyle() const;
        const int &getX() const;
        const int &getY() const;
        const int &getWidth() const;
        const int &getHeight() const;
};

#endif