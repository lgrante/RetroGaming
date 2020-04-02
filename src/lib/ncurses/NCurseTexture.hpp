#ifndef __NCURSE_TEXTURE_H__
#define __NCURSE_TEXTURE_H__

#include "Main.hpp"
#include "Errors.hpp"

class NCurseTexture
{
    public:
        enum style {
            NORMAL,
            BOLD,
            FAINT,
            ITALIC,
            UNDERLINE,
            SLOW_BLINK,
            RAPID_BLINK,
        };
        enum ground {
            FOREGROUND,
            BACKGROUND
        };

        NCurseTexture() = default;
        NCurseTexture(const std::string &texturePath);

        const NCurseTexture &operator=(const NCurseTexture &copy);

        void setCharacter(const wchar_t &character);
        void setColor(
            const enum ground &ground = FOREGROUND, 
            const uint8_t &red = 255, const uint8_t &green = 255, const uint8_t &blue = 255
        );
        void setStyle(const uint16_t &style);

        const wchar_t &getCharacter() const;
        const enum ground &getGround() const; 
        const uint8_t &getRed() const;
        const uint8_t &getGreen() const;
        const uint8_t &getBlue() const;
        const uint16_t &getStyle() const;

        /**
         * @brief Load a file texture to fill all class attributes.
         * 
         * @param teturePath 
         */
        void loadFromFile(const std::string &teturePath);
        /**
         * @brief Return a colored and styled texture.
         * 
         * @return const std::string& 
         */
        const std::string getTexture() const;
    private:
        wchar_t _character;
        ground _ground;
        uint8_t _red;
        uint8_t _green;
        uint8_t _blue;
        uint16_t _style;
        std::map<enum ground, std::string> _ansiCodeGround = {
            {FOREGROUND, "\x1B[38;2;"},
            {BACKGROUND, "\x1B[48;2;"}
        };
        std::map<enum style, std::string> _ansiCodeStyle = {
            {NORMAL, "\x1B[0m"},
            {BOLD, "\x1B[1m"},
            {FAINT, "\x1B[2m"},
            {ITALIC,    "\x1B[3m"},
            {UNDERLINE, "\x1B[4m"},
            {SLOW_BLINK, "\x1B[5m"},
            {RAPID_BLINK, "\x1B[6m"}
        };
        std::vector<std::string> _splitStr(const std::string &line, char split);
};

#endif