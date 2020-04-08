#ifndef __NIBBLER_H__
#define __NIBBLER_H__

#include "Main.hpp"
#include "Module.hpp"
#include "Game.hpp"

#define ID(x, y) (std::to_string((19 * y) + x))

namespace arcade
{
    class PacmanGame;
}

class PacmanGame : public Game
{
    private:
        int _wallNb;
        int _pacgumNb;
        int _bigPacgumNb;
        int _exitNb;
    public:
        PacmanGame();
        ~PacmanGame();

        /**
         * @brief This function initializes all the variables needed for the
         * game to run. 
         * 
         */
        void initGame() final;
        
        /**
         * @brief The inside of the game loop
         * User inputs is returne so that the core class can process it 
         * (If user change lib/game or quit the arcade).
         * 
         * @return int
         */
        int coreGame() final;

        /**
         * @brief This function is called at each game loop.
         * It returns true if game is over. False if not.
         * 
         * @return true 
         * @return false 
         */
        bool isEndGame() final;
};

#endif