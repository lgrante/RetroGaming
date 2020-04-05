#ifndef __NCURSE_MODULE_H__
#define __NCURSE_MODULE_H__

#include "Module.hpp"

namespace arcade
{
    class NCurseModule;
}

class NCurseModule : public Module
{
    private:
        int _colorPair;
    public:
        NCurseModule();
        ~NCurseModule();

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
        void renderText(const std::string &text, const int &x = 0, const int &y = 0, uint16_t alignment = TOP | LEFT, uint16_t style = NORMAL, color color = WHITE);

        /**
         * @brief Clear the whole screen.
         * 
         */
        void clear() final;
        
        /**
         * @brief Get the value of the current pressed key.
         * 
         * @return int 
         */
        int getInputs() final;
};

#endif