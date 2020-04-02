#include "NCurseTexture.hpp"

NCurseTexture::NCurseTexture(const std::string &texturePath)
{
    loadFromFile(texturePath);
}

const NCurseTexture &NCurseTexture::operator=(const NCurseTexture &copy)
{
    _character = copy.getCharacter();
    _ground = copy.getGround();
    _red = copy.getGround();
    _green = copy.getGreen();
    _blue = copy.getBlue();
    _style = copy.getStyle();
    return *this;
}

const wchar_t &NCurseTexture::getCharacter() const
{
    return _character;
}

const NCurseTexture::ground &NCurseTexture::getGround() const
{
    return _ground;
}

const uint8_t &NCurseTexture::getRed() const
{
    return _red;
}

const uint8_t &NCurseTexture::getGreen() const
{
    return _green;
}

const uint8_t &NCurseTexture::getBlue() const
{
    return _blue;
}

const uint16_t &NCurseTexture::getStyle() const
{
    return _style;
}

void NCurseTexture::setCharacter(const wchar_t &character)
{
    if (character >= ' ' && character <= '~')
        _character = character;
}

void NCurseTexture::setColor(
    const enum ground &ground, 
    const uint8_t &red, const uint8_t &green, const uint8_t &blue)
{
    _ground = ground;
    if (red <= 0 || red >= 255 || green <= 0 || green >= 255 || blue <= 0 || blue >= 255)
        throw InitTextureException("Failed to init texture with color", __LINE__);
    _red = red;
    _green = green;
    _blue = blue;
}

void NCurseTexture::setStyle(const uint16_t &style)
{
    _style = style;
}

std::vector<std::string> NCurseTexture::_splitStr(const std::string &line, char split)
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

void NCurseTexture::loadFromFile(const std::string &texturePath)
{
    std::string line;
    std::ifstream file(texturePath);
    std::map<std::string, enum style> styleStr = {
        {"NORMAL", NORMAL},
        {"BOLD", BOLD},
        {"FAINT", FAINT},
        {"ITALIC", ITALIC},
        {"UNDERLINE", UNDERLINE},
        {"SLOW_BLINK", SLOW_BLINK},
        {"RAPID_BLINK", RAPID_BLINK}
    };
    uint16_t style = NORMAL;

    if (file) {
        while (std::getline(file, line)) {
            std::vector<std::string> words = _splitStr(line, ':');

            if (words[0] == "CHARACTER") {
                if (words[1].size() == 1)
                    setCharacter(words[0][1]);
                else
                    throw InitTextureException("Failed to load texture from file", __LINE__);
            } else if (words[0] == "COLOR") {
                std::vector<std::string> c = _splitStr(words[1], ',');

                if (c[0].size() != 1 || (c[0][0] != 'F' && c[0][0] != 'B'))
                    throw InitTextureException("Failed to load texture from file", __LINE__);
                setColor((c[0][0] == 'B' ? BACKGROUND : FOREGROUND), std::stoi(c[1]), std::stoi(c[2]), std::stoi(c[3]));
            } else if (words[0] == "STYLE") {
                std::vector<std::string> s = _splitStr(words[1], ',');

                for (std::string i : s) {
                    if (styleStr.find(i) == styleStr.end())
                        throw InitTextureException("Failed to load texture from file", __LINE__);
                    style |= styleStr.at(i);
                }
                setStyle(style);
            }
        }
    } else
        throw InitTextureException("Failed to load texture from file", __LINE__);
}

const std::string NCurseTexture::getTexture() const
{
    std::string texture = _ansiCodeGround.at(_ground);

    texture += std::to_string(_red) + ";" + std::to_string(_green) + ";" + std::to_string(_blue) + "m";
    for (std::pair<style, std::string> i : _ansiCodeStyle)
        if (_style & i.first)
            texture += i.second;
    return texture;
}