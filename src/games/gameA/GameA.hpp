#ifndef __NIBBLER_H__
#define __NIBBLER_H__

#include "Main.hpp"
#include "Module.hpp"
#include "Game.hpp"

namespace arcade
{
    class NibblerGame;
}

class NibblerGame : public Game
{
    public:
        NibblerGame();
        ~NibblerGame();

        /**
         * @brief Initialize the _data map then call coreGame().
         * 
         */
        void launchGame();
        /**
         * @brief The game loop.
         * 
         */
        void coreGame();
};

#endif