#ifndef __SDL_MODULE_H__
#define __SDL_MODULE_H__

#include "Module.hpp"

namespace arcade
{
    class SDLModule;
}

class SDLModule : public Module
{
    public:
        SDLModule();
        ~SDLModule();

        /**
         * @brief Create a window of type sf::RenderWindow or SDL_Surface* or WINDOW* depending on the graphical lib used.
         * 
         * @param width Width of the window in cols and not in pixels.
         * @param height Height of the window in rows and not in pixels.
         * @param x X coordinate of the window in pixels.
         * @param y Y coordinate of the window in pixels.
         * @param title Title of the window.
         */
        void initWindow(const size_t &width = 800, const size_t &height = 600, const std::string &title = "Arcade Game") final;

        /**
         * @brief Destroy the current window.
         * 
         */
        void destroyWindow() final;

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