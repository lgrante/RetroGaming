#ifndef OBJECT_H
#define OBJECT_H

#include "Main.hpp"
#include "Errors.hpp"
#include "NCurseTexture.hpp"

class Object
{
    private:
        int _x;
        int _y;

        std::map<std::string, void *> _data;

        sf::Sprite _sprite;
        sf::Texture _sfTexture;
        NCurseTexture _ncTexture;
    public:
        Object() = default;
        Object(const std::string &sfTexturePath, const std::string &ncTexturePath);
        Object(const std::string &sfTexturePath, const std::string &ncTexturePath, const int &x = 0, const int &y = 0);

        void setTexture(const std::string &sfTexturePath, const std::string &ncTexturePath);
        void setX(int x);
        void setY(int y);

        const sf::Sprite &getSfSprite() const;
        const sf::Texture &getSfTexture() const;
        const NCurseTexture &getNcTexture() const;
        const int &getX() const;
        const int &getY() const;
};

#endif