#ifndef __MODULE_H__
#define __MODULE_H__

#include "Main.hpp"
#include "Object.hpp"
#include "Errors.hpp"

#define FONT_PATH "./assets/fonts/main_font.ttf"
#define BG_PATH "./assets/texture/bg.jpeg"

#define COLS 159
#define ROWS 42

namespace arcade
{
    class Module;
}

enum module {
    SFML,
    SDL,
    NCURSE
};

/**
 * @note It's possible to combine the flags like this:
 * LEFT | TOP // This will write the text in the top left corner of the screen.
 * 
 */
enum textAlignement {
    LEFT        = 1 << 0,
    CENTER      = 1 << 1,
    RIGHT       = 1 << 2,
    TOP         = 1 << 3,
    MIDDLE      = 1 << 4,
    BOTTOM      = 1 << 5
};

enum textStyle {
    NORMAL      = 1 << 0,
    BOLD        = 1 << 1,
    ITALIC      = 1 << 2,
    UNDERLINE   = 1 << 3
};

enum color {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

/**
 * @class Module
 * @brief Module is interface between the games and the libraries. 
 * Contains all the lib functions.
 * 
 * Each game has a unique source code for each graphic library. Module
 * defines the methods that will be used by each game. All Module child
 * class will override this  methods for each graphic library 
 * (SFMLModule, NCurseModule...).
 * 
 */
class Module
{
    protected:
        void _computeTextPosition(int &x, int &y, uint16_t alignment, uint16_t textWidth);
        struct {
            size_t w;
            size_t h;
            uint16_t wUnit;
            uint16_t hUnit;
            uint16_t getWidthInUnit()
            {
                return (uint16_t) w / wUnit;
            }
            uint16_t getHeightInUnit()
            {
                return (uint16_t) h / hUnit;
            }
        } _size;
        sf::RenderWindow *_sfWindow;
        SDL_Window *_sdlWindow;
        SDL_Renderer *_sdlRenderer;
        WINDOW *_ncWindow;

        module _module;
    public:
        const module &getModule() const;
        /**
         * @brief Create a window of type sf::RenderWindow or SDL_Surface* or WINDOW* depending on the graphical lib used.
         * 
         * @param width Width of the window in cols and not in pixels.
         * @param height Height of the window in rows and not in pixels.
         * @param x X coordinate of the window in pixels.
         * @param y Y coordinate of the window in pixels.
         * @param title Title of the window.
         */
        virtual void initWindow(const size_t &width = 800, const size_t &height = 600, const std::string &title = "Arcade Game") = 0;

        /**
         * @brief Destroy the current window.
         * 
         */
        virtual void destroyWindow() = 0;
        
        /**
         * @brief Initialize an object and add it to the game data.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object.
         * @param sfTexturePath Path to the picture file storing the object texture.
         * Only displayed for others lib than ncurse.
         * @param sdlTexturePath Path to the SDL texture file (must be .bmp file).
         * @param ncTexturePath Path to the Ncurse module texture file.
         * @param x X coordinate of the object in cols and not in pixels.
         * @param y Y coordinate of the object in rows and not in pixels.
         */
        virtual void setObject(
            std::map<std::string, Object> &gameDatas, const std::string &name, 
            const std::string &sfTexturePath, const std::string &sdlTexturePath, const std::string &ncTexturePath, 
            const int &x = 0, const int &y = 0
        );

        /**
         * @brief Set the coordinates of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object.
         * @param x X coordinate of the object in cols and not in pixels.
         * @param y Y coordinate of the object in rows and not in pixels.
         */
        virtual void setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y);

        /**
         * @brief Set the texture of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param sfTexturePath Path to the picture file storing the object texture.
         * Only displayed for others lib than ncurse.
         * @param ncTexturePath Path to the Ncurse module texture file.
         * @param sdlTexturePath Path to the SDL texture file (must be .bmp file).
         */
        virtual void setObjectTexture(std::map<std::string, Object> &gamesData, const std::string &name, const std::string &sfTexturePath, const std::string &sdlTexturePath, const std::string &ncTexturePath);
        
        /**
         * @brief Destroy an object from its name.
         * 
         * @param gamesData Current game data.
         * @param name Name of the object to destroy.
         */
        virtual void destroyObject(std::map<std::string, Object> &gameDatas, const std::string &name);

        /**
         * @brief Render all the object of the current game data.
         * 
         * @param gameDatas Current game data.
         */
        virtual void render(const std::map<std::string, Object> &gamesData) = 0;

        /**
         * @brief Render text on the screen to given coordinates.
         * 
         * @param text Text to render on the screen.
         * @param x X coordinates of the text in cols.
         * @param y Y coordinates of the text in rows.
         * @param alignment How the text is aligned: Left, center, right, top, middle or bottom.
         * These flags can be combined like this: TOP | RIGHT.
         * @param style The style applied to the text (NORMAL, BOLD, ITALIC, UNDERLINE)
         * These flags can be combined like this: BOLD | ITALIC
         * @param color The color applied to the text as a structure composed of r, g and field each defining
         * the rate of red, green and blue.
         */
        virtual void renderText(const std::string &text, const int &x = 0, const int &y = 0, uint16_t alignment = TOP | LEFT, uint16_t style = NORMAL, color color = WHITE) = 0;

        /**
         * @brief Clear the whole screen.
         * 
         */
        virtual void clear() = 0;
        /**
         * @brief Get the value of the current pressed key.
         * 
         * @return int 
         */
        virtual int getInputs() = 0;
};

#endif