#ifndef __I_GAME_H__
#define __I_GAME_H__

#include "Main.hpp"
#include "Module.hpp"
#include "Object.hpp"

#define GT_PATH "./assets/textures/graphical/"
#define TT_PATH "./assets/textures/text/"

namespace arcade
{
    class Game;
}

/**
 * @class Game
 * @brief Game is an interface for each game source code.
 * 
 * Game methods will be overriden by its child class because each game 
 * has a different source code. Each game will use methods from _module field.
 * 
 * Core will call coreGame() in loop until isEndGame() returns true. 
 * If isEndGame() returns true its calls endGame() and isGameRestart() in loop. 
 * endGame() prints out end game screen. If isGameRestart() returns 
 * true the game restart otherwise it leaves the game and go back to 
 * the arcade main menu.
 * 
 */
class Game
{
    protected:
        std::string _name;

        Module *_module;

        std::map<std::string, Object> _data;
        uint16_t _score;

        int _xDirection;
        int _yDirection;
    public:
        const std::string &getName() const;
        Module *getModule() const;
        const std::map<std::string, Object> &getData() const;
        const uint16_t &getScore() const;

        void setName(const std::string &name);
        void setModule(Module *module);
        void setData(const std::map<std::string, Object> &data);
        void setScore(const uint16_t &score);

        int readMoveKey(int &xOff, int &yOff);
        /**
         * @brief This function initializes all the variables needed for the
         * game to run. 
         * 
         */
        virtual void initGame() = 0;

        /**
         * @brief The inside of the game loop
         * User inputs is returned so that the core class can process it 
         * (If user change lib/game or quit the arcade).
         * 
         * @return int
         */
        virtual int coreGame() = 0;
        
        /**
         * @brief This function is called at each game loop.
         * It returns true if game is over. False if not.
         * 
         * @return true 
         * @return false 
         */
        virtual bool isEndGame() = 0;

        /**
         * @brief Clear all game datas.
         * 
         */
        virtual void endGame();
};

#endif