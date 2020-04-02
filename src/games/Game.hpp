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
        virtual ~Game() = 0;

        const std::string &getName() const;
        Module *getModule() const;
        const std::map<std::string, Object> &getData() const;

        void setName(const std::string &name);
        void setModule(Module *module);
        void setData(const std::map<std::string, Object> &data);

        /**
         * @brief Initialize the _data map then call coreGame().
         * 
         */
        virtual void launchGame() = 0;
        /**
         * @brief The game loop.
         * 
         */
        virtual void coreGame() = 0;
};

#endif