#ifndef __CORE_H__
#define __CORE_H__

#include "Main.hpp"
#include "Module.hpp"
#include "Game.hpp"
#include "Object.hpp"
#include "Errors.hpp"

#define SCORE_PATH "./assets/scores"

namespace arcade
{
    class Core;
}

/**
 * @class Core
 * @brief Core class stores the current module and current game and its data.
 * 
 * Core class dynamically load game or lib (.so file) and then stores
 * its instance by calling a symbol that calls the ctor. 
 * Core class stores the game data of each loaded game so that when
 * the user changes the lib it keeps all game data in order to
 * avoid to reload the game. 
 */
class Core
{
    private:
        /**
         * @brief Stores all objects of each game already loaded.
         * Exemple:
         * {
         *     {"pacman", {{"player", Object}, {"enemy1", Object}, {"wall", Object}...}} // Pacman objects.
         *     {"qix", std::map<String, Object>} // Qix objects.
         * }
         */
        std::map<const std::string, std::map<std::string, Object>> _gamesData;
        Module *_module;
        void (*_moduleDestroyer)(Module *);
        Game *_game;
        void (*_gameDestroyer)(Game *);

        std::vector<std::string> _libs;
        std::vector<std::string> _games;
        std::vector<std::string>::iterator _currentLib;
        std::vector<std::string>::iterator _currentGame;
        std::map<int, std::pair<std::string, std::string>, std::greater<int>> _scores;

        bool _inGame;

        template <typename T>
        T *_loadSharedClass(const std::string &libPath, void (**destroyer)(T *))
        {
            T* classInstance = nullptr;
            T *(*create)() = nullptr;
            void *handle = dlopen(libPath.c_str(), RTLD_LAZY);

            if (handle == nullptr) {
                std::cerr << dlerror() << std::endl;
                throw LoadSharedModuleException("Failed to load " + libPath, __FILE__, __LINE__);
            }
            create = (T *(*)()) dlsym(handle, "create");
            *destroyer = (void (*)(T *)) dlsym(handle, "destroy");
            if (create == nullptr || *destroyer == nullptr)
                throw LoadSharedModuleException("Failed to fetch ctor and dtor symbols from " + libPath, __FILE__, __LINE__);
            classInstance = (T *) create();
            return classInstance;
        }

        std::vector<std::string> _readDirectory(const std::string &path);
        std::map<int, std::pair<std::string, std::string>, std::greater<int>> _readScores();
        std::vector<std::string> _splitStr(const std::string &line, char split);

        void _readModuleKey(const int &key);
        void _scoreMenu();
        void _mainMenu();
        void _exit();
    public:
        Core();
        Core(const std::string &gamePath, const std::string &modulePath);

        void setModule(const std::string &path);
        void setGame(const std::string &path);

        const module &getModuleType() const;
        Module *getModule() const;
        Game *getGame() const;

        /**
         * @brief Initialize the _data map then call coreGame() in loop.
         * 
         * coreGame(), isEndGame(), enGame(), isGameRestart() are stored into
         * Game class.
         * 
         * Call coreGame() in loop until isEndGame() returns true. If isEndGame() 
         * returns true its calls endGame() and isGameRestart() in loop. 
         * endGame() prints out end game screen. If isGameRestart() returns 
         * true the game restart otherwise it leaves the game and go back to 
         * the arcade main menu.
         * 
         */
        void launchGame();

        /**
         * @brief Launch the UI menu where user can choose a game and lib module.
         * It's also possible to see users scores and to set username.
         * 
         */
        void launch(const std::string &lib);
};

#endif