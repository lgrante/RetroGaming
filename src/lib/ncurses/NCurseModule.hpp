#ifndef __NCURSE_MODULE_H__
#define __NCURSE_MODULE_H__

#include "Module.hpp"

namespace arcade
{
    class NCurseModule;
}

class NCurseModule : public Module
{
    public:
        NCurseModule();
        ~NCurseModule();

        /**
         * @brief Create a window of type sf::RenderWindow or WINDOW depending on the graphical lib used.
         * 
         * @param width Width of the window.
         * @param height Height of the window.
         * @param x X coordinate of the window.
         * @param y Y coordinate of the window.
         * @param title Title of the window.
         */
        void initWindow(const size_t &width = 800, const size_t &height = 600, const std::string &title = "Arcade Game") final;

        /**
         * @brief Destroy the current window.
         * 
         */
        void destroyWindow() final;

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
        void setObject(
            std::map<std::string, Object> &gameDatas,
            const std::string &name, const std::string &sfTexturePath, const std::string &ncTexturePath, 
            const int &x = 0, const int &y = 0
        ) final;

        /**
         * @brief Set the coordinates of a given object into game data.
         * 
         * @param gameDatas Current game data.
         * @param name Name of the object.
         * @param x X coordinate of the object.
         * @param y Y coordinate of the object.
         */
        void setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y) final;

        /**
         * @brief Render all the object of the current game data.
         * 
         * @param gameDatas Current game data.
         */
        void render(const std::map<std::string, Object> &gamesData) final;

        /**
         * @brief Get the value of the current pressed key.
         * 
         * @return int 
         */
        int getInputs() final;
};

#endif