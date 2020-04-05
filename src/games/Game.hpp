#ifndef __I_GAME_H__
#define __I_GAME_H__

#include "Main.hpp"
#include "Module.hpp"
#include "Object.hpp"

namespace arcade
{
    class Game;
}

/**
 * @class Game
 * @brief Game is an interface for each game source code.
 * 
 * Game methods launchGame and coreGame() will be overriden by its
 * child class because each game hase a different source code.
 * Each game will use methods from _module field.
 * 
 */
class Game
{
    protected:
        std::string _name;
        Module *_module;
        std::map<std::string, Object> _data;
    public:
        const std::string &getName() const;
        Module *getModule() const;
        const std::map<std::string, Object> &getData() const;
        const int &getCurrentInput() const;

        void setName(const std::string &name);
        void setModule(Module *module);
        void setData(const std::map<std::string, Object> &data);

        /**
         * @brief Initialize the _data map then call coreGame().
         * Call coreGame() in loop until isEndGame() returns false.
         * If isEndGame() returns true its calls endGame() in loop
         * until isGameRestart() returns false.
         * 
         */
        void launchGame();

        /**
         * @brief The inside of the game loop
         * 
         * @param key Every user input have to stored into key parameter
         * so that the core class can process it 
         * (if user change lib/game or quit the arcade).
         */
        virtual void coreGame(int &key) = 0;

        /**
         * @brief The screen to disaplay when game is over.
         * 
         * @param key Every user input have to stored into key parameter
         * so that the core class can process it.
         * (if user change lib/game or quit the arcade).
         */
        virtual void endGame(int &key) = 0;

        /**
         * @brief This is function is called in loop at the game end.
         * It returns true if players choose to restart. False if not.
         * 
         * @return true
         * @return false
         */
        virtual bool isGameRestart() = 0;
        /**
         * @brief This function is called at each game loop.
         * It returns true if game is over. False if not.
         * 
         * @return true 
         * @return false 
         */
        virtual bool isEndGame() = 0;
};

#endif