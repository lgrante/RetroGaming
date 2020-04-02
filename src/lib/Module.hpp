#ifndef __MODULE_H__
#define __MODULE_H__

#include "Main.hpp"
#include "Object.hpp"
#include "Errors.hpp"

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
        size_t _width; // in pixels
        size_t _height; // in pixels
        sf::RenderWindow _sfWindow;
        WINDOW *_ncWindow;
    public:
        /**
         * @brief Create a window of type sf::RenderWindow or WINDOW depending on the graphical lib used.
         * 
         * @param width Width of the window.
         * @param height Height of the window.
         * @param x X coordinate of the window.
         * @param y Y coordinate of the window.
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
         * @param ncTexturePath Path to the Ncurse module texture file.
         * @param x X coordinate of the object.
         * @param y Y coordinate of the object.
         */
        virtual void setObject(
            std::map<std::string, Object> &gameDatas,
            const std::string &name, const std::string &sfTexturePath, const std::string &ncTexturePath, 
            const int &x = 0, const int &y = 0
        ) = 0;

        /**
         * @brief Set the coordinates of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object.
         * @param x X coordinate of the object.
         * @param y Y coordinate of the object.
         */
        virtual void setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y) = 0;

        /**
         * @brief Set the texture of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param sfTexturePath Path to the picture file storing the object texture.
         * Only displayed for others lib than ncurse.
         * @param ncTexturePath Path to the Ncurse module texture file.
         */
        void setObjectTexture(std::map<std::string, Object> &gamesData, const std::string &name, const std::string &sfTexturePath, const std::string &ncTexturePath);
        
        /**
         * @brief Destroy an object from its name.
         * 
         * @param gamesData Current game data.
         * @param name Name of the object to destroy.
         */
        void destroyObject(std::map<std::string, Object> &gameDatas, const std::string &name);

        /**
         * @brief Render all the object of the current game data.
         * 
         * @param gameDatas Current game data.
         */
        virtual void render(const std::map<std::string, Object> &gamesData) = 0;

        /**
         * @brief Get the value of the current pressed key.
         * 
         * @return int 
         */
        virtual int getInputs() = 0;
};

#endif