#include "Core.hpp"

Core::Core()
    : _module(nullptr), _moduleDestroyer(nullptr), _game(nullptr), _gameDestroyer(nullptr)
{
}

Core::Core(const std::string &gamePath, const std::string &modulePath)
    : _module(nullptr), _moduleDestroyer(nullptr), _game(nullptr), _gameDestroyer(nullptr)
{
    setGame(gamePath);
    setModule(modulePath);
}

void Core::setModule(const std::string &path)
{
    /**
     * @note First we destroy the current module.
     */
    if (_moduleDestroyer != nullptr)
        _moduleDestroyer(_module);
    else if (_module != nullptr)
        delete(_module);

    /**
     * @note Then we load the new module and we store it into the game instance.
     */
    _module = _loadSharedClass<Module>(path, &_moduleDestroyer);
    if (_game != nullptr)
        _game->setModule(_module);
}

void Core::setGame(const std::string &path)
{
    std::map<const std::string, std::map<std::string, Object>>::iterator it; 

    /**
     * @note First we save the current game data and then we destroy it. 
     */
    it = _gamesData.find(_game->getName());
    if (it == _gamesData.end())
        _gamesData.emplace(_game->getName(), _game->getData());
    else
        _gamesData.at(_game->getName()) = _game->getData();
    if (_gameDestroyer != nullptr)
        _gameDestroyer(_game);
    else if (_game != nullptr)
        delete(_game);

    /**
     * @note We load the new game and store the current module in the new
     * loaded game.
     */
    _game = _loadSharedClass<Game>(path, &_gameDestroyer);
    _game->setModule(_module);

    /**
     * @note We launch the game and if the game has alredy been loaded before
     * we store back its data into it.
     */
    _game->launchGame();
    if (it != _gamesData.end())
        _game->setData(it->second);
}

const module &Core::getModuleType() const
{
    return _module->getModule();
}

Module *Core::getModule() const
{
    return _module;
}

Game *Core::getGame() const
{
    return _game;
}

std::vector<std::string> Core::_readDirectory(const std::string &path)
{
    std::vector<std::string> files;
    DIR *dir = opendir(path.c_str());
    struct dirent *currentFile;

    while ((currentFile = readdir(dir)) != NULL) {
        std::string fileName(currentFile->d_name);
        
        if (fileName[0] != '.')
            files.push_back(fileName);
    }
    closedir(dir);
    return files;
}

void Core::launch(const std::string &lib)
{
    bool exit = false, insertMode = false;
    int input = 0;
    std::string username = "";
    /**
     * @note Get the list of libs and games
     */
    std::vector<std::string> libs = _readDirectory("./lib");
    std::vector<std::string> games = _readDirectory("./games");
    std::vector<std::string>::iterator currentLib = std::find(libs.begin(), libs.end(), lib.substr(4));
    std::vector<std::string>::iterator currentGame = games.begin();

    if (_module == nullptr)
        return;
    _module->initWindow(100, 40, "ARCADE");
    while (!exit) {
        /**
         * @note First display the keys.
         */
        _module->renderText("Welcome on Arcade !", 0, 2, TOP | CENTER, BOLD | UNDERLINE, CYAN);
        _module->renderText("[Q]/[ESC]: Quit the program", 0, 6, TOP | CENTER, ITALIC);
        _module->renderText("[A]: Previous lib / [Z]: Next lib", 0, 7, TOP | CENTER, ITALIC);
        _module->renderText("[O]: Previous game / [P]: Next lib", 0, 8, TOP | CENTER, ITALIC);
        _module->renderText("[I]: Insert your username, insert mode: ", 0, 9, TOP | CENTER, ITALIC);
        _module->renderText((insertMode) ? "activated" : "disabled", 25, 9, TOP | CENTER, NORMAL, (insertMode) ? CYAN : RED);
        _module->renderText("[ENTER]: Launch game!", 0, 10, TOP | CENTER, ITALIC);

        /**
         * @note Then display the games and libs.
         */
        _module->renderText((libs.size() == 0) ? "No libs found..." : "List of library:", 0, 14, TOP | CENTER, BOLD);
        for (size_t i = 0; i < libs.size(); i++)
            _module->renderText(libs[i], 0, 16 + i, TOP | CENTER, NORMAL, (libs[i] == *currentLib) ? CYAN : WHITE);
        _module->renderText((games.size() == 0) ? "No games found..." : "List of game:", 0, 22, TOP | CENTER, BOLD);
        for (size_t i = 0; i < games.size(); i++)
            _module->renderText(games[i], 0, 24 + i, TOP | CENTER, NORMAL, (games[i] == *currentGame) ? CYAN : WHITE);
        _module->renderText("USERNAME", 0, 30, TOP | CENTER, BOLD | ITALIC);
        _module->renderText(username, 0, 31, TOP | CENTER, ITALIC);

        /**
         * @note And last we read the keys pressed by user and process it.
         */
        if ((input = _module->getInputs()) != 127 && input != 27 && input != -1 && insertMode) {
            _module->clear();
            username.push_back(input);
        } else if (input == 127 && insertMode)
            username.pop_back();
        else if (input == 27 && insertMode) {
            _module->clear();
            insertMode = false;
        }
        else if (!insertMode) {
            switch (input) {
                case 'q':
                case 27:
                    exit = true;
                    break;
                case 'a':
                    currentLib = (currentLib == libs.begin()) ? (libs.end() - 1) : currentLib - 1;
                    break;
                case 'z':
                    currentLib = (currentLib == libs.end() - 1) ? (libs.begin()) : currentLib + 1;
                    break;
                case 'o':
                    currentGame = (currentGame == games.begin()) ? (games.end() - 1) : currentGame - 1;
                    break;
                case 'p':
                    currentGame = (currentGame == games.end() - 1) ? (games.begin()) : currentGame + 1;
                    break;
                case 'i':
                    _module->clear();
                    insertMode = true;
                    break;
            }
            if (input == 'a' || input == 'z')
                setModule(*currentLib);
        }
    }
    _module->destroyWindow();
}