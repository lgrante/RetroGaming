#include "Object.hpp"

Object::Object()
    : _x(0), _y(0), _width(0), _height(0), 
    _sfTexture(nullptr), _sfSprite(nullptr), _sdlTexture(nullptr),
    _ncTexture(0), _ncBgColor(DEFAULT), _ncFgColor(DEFAULT), _ncStyle(NORMAL)
{
}

std::vector<std::string> Object::_splitStr(const std::string &line, char split)
{
    std::vector<std::string> words;
    std::stringstream stream(line);
    std::string word;

    while (std::getline(stream, word, split)) {
        if (word.size() != 0)
            words.push_back(word);
    }
    return words;
}

void Object::_loadNCurseTexture(const std::string &texturePath)
{
    std::string line;
    std::ifstream file(texturePath);

    if (file) {
        while (std::getline(file, line)) {
            std::vector<std::string> words = _splitStr(line, ':');

            if (line[0] == '#' || line[0] == '\n' || line.size() == 0)
                continue;
            if (words.size() != 2)
                throw InitTextureException("Parsing error in NcurseTexture file", __FILE__, __LINE__);
            if (words[0] == "CHARACTER") {
                if (words[1].size() == 1)
                    _ncTexture = words[1][0];
                else
                    throw InitTextureException("Parsing error in NcurseTexture file", __FILE__, __LINE__);
            } else if (words[0] == "COLOR") {
                std::vector<std::string> c = _splitStr(words[1], ',');
                std::map<std::string, color> colors = {
                    {"BLACK", BLACK},
                    {"RED", RED},
                    {"GREEN", GREEN},
                    {"YELLOW", YELLOW},
                    {"BLUE", BLUE},
                    {"MAGENTA", MAGENTA},
                    {"CYAN", CYAN},
                    {"WHITE", WHITE},
                    {"DEFAULT", DEFAULT}
                };

                if (c.size() != 2)
                    throw InitTextureException("Parsing error in NcurseTexture file", __FILE__, __LINE__);
                if (colors.find(c[0]) == colors.end() || colors.find(c[1]) == colors.end())
                    throw InitTextureException("Parsing error in NcurseTexture file", __FILE__, __LINE__);
                _ncFgColor = colors.at(c[0]);
                _ncBgColor = colors.at(c[1]);
            } else if (words[0] == "STYLE") {
                std::vector<std::string> s = _splitStr(words[1], ',');
                std::map<std::string, textStyle> styles = {
                    {"NORMAL", NORMAL},
                    {"BOLD", BOLD},
                    {"ITALIC", ITALIC},
                    {"UNDERLINE", UNDERLINE}
                };

                for (std::string i : s) {
                    if (styles.find(i) == styles.end())
                        throw InitTextureException("Parsing error in NcurseTexture file", __FILE__, __LINE__);
                    _ncStyle |= styles.at(i);
                }
            } else
                throw InitTextureException("Parsing error in NcurseTexture file", __FILE__, __LINE__);
        }
    } else
        throw InitTextureException("Failed to load NCurse texture", __FILE__, __LINE__);
}

void Object::setTexture(const std::string &graphicTexturePath, const std::string &textTexturePath)
{
    sf::Vector2u size;
    
    /**
     * @note Loading SDL Texture.
     */
    _sdlTexture = IMG_Load(graphicTexturePath.c_str());
    if (_sdlTexture == nullptr)
        throw InitTextureException("Failed to laod texture from file" + graphicTexturePath, __FILE__, __LINE__);
    /*
    // Check if we can use the renderer to create the texture.
    if (renderer != nullptr) {
        // If we have already load the texture before we delete it.
        if (_sdlTexture != nullptr)
            SDL_DestroyTexture(_sdlTexture);

        // Load the surface of the texture from the picture file.
        buffer = IMG_Load(graphicTexturePath.c_str());
        if (buffer == nullptr)
            throw InitTextureException("Failed to laod texture from file" + graphicTexturePath, __FILE__, __LINE__);

        // Create the texture from the surface.
        _sdlTexture = SDL_CreateTextureFromSurface(renderer, buffer);
        if (_sdlTexture == nullptr)
            throw InitTextureException("Failed to laod texture from file" + graphicTexturePath, __FILE__, __LINE__);
        // And finally free the surface. We don't need it anymore.
        SDL_FreeSurface(buffer);
    }*/

    /**
     * @note Loading SFML Texture.
     */
    _sfTexture = std::make_shared<sf::Texture>();
    if (_sfTexture->loadFromFile(graphicTexturePath) == false)
        throw InitTextureException("Failed to laod texture from file" + graphicTexturePath, __FILE__, __LINE__);
    size = _sfTexture->getSize();
    _sfSprite = std::make_shared<sf::Sprite>(*_sfTexture);
    if (_sfSprite == nullptr)
        throw InitTextureException("Failed to laod texture from file" + graphicTexturePath, __FILE__, __LINE__);

    // The sprite must fit in one character (same behavior as Ncurse).
    _sfSprite->setScale((_width / size.x), (_height / size.y));
    _sfSprite->setPosition(_x, _y);

    /**
     * @note Loading NCurse Texture.
     */
    _loadNCurseTexture(textTexturePath);
}

void Object::setX(int x)
{
    sf::Vector2f position;

    _x = x;
    if (_sfSprite != nullptr) {
        position = _sfSprite->getPosition();
        position.x = x;
        _sfSprite->setPosition(position);
    }
}

void Object::setY(int y)
{
    sf::Vector2f position;

    _y = y;
    if (_sfSprite != nullptr) {
        position = _sfSprite->getPosition();
        position.y = y;
        _sfSprite->setPosition(position);
    }
}

void Object::setWidth(int width)
{
    _width = width;
}

void Object::setHeight(int height)
{
    _height = height;
}

sf::Sprite *Object::getSfSprite() const
{
    return _sfSprite.get();
}

sf::Texture *Object::getSfTexture() const
{
    return _sfTexture.get();
}

SDL_Surface *Object::getSdlTexture() const
{
    return _sdlTexture;
}

const wchar_t &Object::getNcTexture() const
{
    return _ncTexture;
}

const color &Object::getNcFgColor() const
{
    return _ncFgColor;
}

const color &Object::getNcBgColor() const
{
    return _ncBgColor;
}

const uint16_t &Object::getNcStyle() const
{
    return _ncStyle;
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