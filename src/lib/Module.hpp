#ifndef __MODULE_H__
#define __MODULE_H__

#include "Main.hpp"
#include "Errors.hpp"
#include "Object.hpp"
#include "Constants.hpp"

namespace arcade
{
    class Module;
}

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
        virtual void _computePosition(int &x, int &y, uint16_t alignment, uint16_t textWidth);
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
         * @brief Get the size of the window.
         * 
         * @param width Reference where window's width will be stored.
         * @param height Reference where window's height will be stored.
         * @param pixelSize If set to true returns size in pixel otherwise it returns
         * the size in columns and rows.
         */
        virtual void getWindowSize(int &width, int &height, bool pixelSize);
        
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
         * @param alignment How the object is aligned: Left, center, right, top, middle or bottom.
         * These flags can be combined like this: TOP | RIGHT.
         */
        virtual void setObject(
            std::map<std::string, Object> &gameDatas, const std::string &name, 
            const std::string &graphicTexturePath, const std::string &textTexturePath, 
            const int &x = 0, const int &y = 0, uint16_t alignment = TOP | LEFT
        );

        /**
         * @brief Set the coordinates of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object.
         * @param x X coordinate of the object in cols and not in pixels.
         * @param y Y coordinate of the object in rows and not in pixels.
         * @param alignment How the object is aligned: Left, center, right, top, middle or bottom.
         * These flags can be combined like this: TOP | RIGHT.
         */
        virtual void setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y, uint16_t alignment = TOP | LEFT);

        /**
         * @brief Get the coordinates of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object.
         * @param x X coordinate of the object to write in.
         * @param y Y coordinate of the object to write in.
         */
        virtual void getObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, int &x, int &y);

        /**
         * @brief Move the object by incrementing its coordinates by given coordinates.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object.
         * @param x X offset of the object in cols and not in pixels.
         * @param y Y offset of the object in rows and not in pixels.
         */
        virtual void moveObject(std::map<std::string, Object> &gameDatas, const std::string &name, const int &xOff, const int &yOff);
        
        /**
         * @brief Move the object to a another object.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object to move.
         * @param targetName Name of the object to move to.
         */
        virtual void moveObject(std::map<std::string, Object> &gameDatas, const std::string &name, const std::string &targetName);

        /**
         * @brief Set the texture of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param sfTexturePath Path to the picture file storing the object texture.
         * Only displayed for others lib than ncurse.
         * @param ncTexturePath Path to the Ncurse module texture file.
         * @param sdlTexturePath Path to the SDL texture file (must be .bmp file).
         */
        virtual void setObjectTexture(std::map<std::string, Object> &gamesData, const std::string &name, const std::string &graphicTexturePath, const std::string &textTexturePath);
        
        /**
         * @brief Destroy an object from its name.
         * 
         * @param gamesData Current game data.
         * @param name Name of the object to destroy.
         */
        virtual void destroyObject(std::map<std::string, Object> &gameDatas, const std::string &name);

        /**
         * @brief Destroy all objects.
         * 
         * @param gameDatas Current game data.
         */
        virtual void destroyAll(std::map<std::string, Object> &gameDatas);

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
        virtual void renderText(const std::string &text, const int &x = 0, const int &y = 0, uint16_t alignment = TOP | LEFT, uint16_t style = NORMAL, color color = DEFAULT) = 0;

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