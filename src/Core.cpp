#include "Core.hpp"

Core::Core()
    : _module(nullptr), _moduleDestroyer(nullptr), _game(nullptr), _gameDestroyer(nullptr), _inGame(false)
{
}

Core::Core(const std::string &gamePath, const std::string &modulePath)
    : _module(nullptr), _moduleDestroyer(nullptr), _game(nullptr), _gameDestroyer(nullptr), _inGame(false)
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
    //std::map<const std::string, std::map<std::string, Object>>::iterator it = _gamesData.end(); 

    /**
     * @note First we save the current game data and then we destroy it. 
     */
    if (_game != nullptr) {
        /*
        it = _gamesData.find(_game->getName());
        if (it == _gamesData.end())
            _gamesData.emplace(_game->getName(), _game->getData());
        else
            _gamesData.at(_game->getName()) = _game->getData();
        */    
        if (_gameDestroyer != nullptr)
            _gameDestroyer(_game);
        else if (_game != nullptr)
            delete(_game);
    }

    /**
     * @note We load the new game and store the current module in the new
     * loaded game.
     */
    _game = _loadSharedClass<Game>(path, &_gameDestroyer);
    if (_module != nullptr)
        _game->setModule(_module);

    /**
     * @note We launch the game and if the game has alredy been loaded before
     * we store back its data into it.
     */
    //if (it != _gamesData.end())
    //    _game->setData(it->second);
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

std::map<int, std::pair<std::string, std::string>, std::greater<int>> Core::_readScores()
{
    std::map<int, std::pair<std::string, std::string>, std::greater<int>> userScores;
    std::string line;
    std::ifstream file(SCORE_PATH);

    if (file) {
        while (std::getline(file, line)) {
            std::vector<std::string> words = _splitStr(line, ':');
            char *checkNbr = nullptr;
            long score = 0;

            if (line[0] == '#' || line.size() == 0 || line[0] == '\n')
                continue;
            if (words.size() != 3)
                throw LoadUserScoresException("Wrong syntax in user scores files", __FILE__, __LINE__);
            score = std::strtol(words[1].c_str(), &checkNbr, 10);
            if (*checkNbr)
                throw LoadUserScoresException("Wrong syntax in user scores files", __FILE__, __LINE__);
            userScores.emplace((int) score, std::pair<std::string, std::string>(words[0], words[2]));
        }
    } else
        throw LoadUserScoresException("Failed to open user scores files", __FILE__, __LINE__);
    return userScores;
}

std::vector<std::string> Core::_splitStr(const std::string &line, char split)
{
    std::vector<std::string> words;
    std::stringstream stream(line);
    std::string word;

    while (std::getline(stream, word, split)) {
        if (word.size() != 0)
            words.push_back(word);
    }
    return words;
}

void Core::_readModuleKey(const int &key)
{
    switch (key) {
        case 'a':
            _currentLib = (_currentLib == _libs.begin()) ? (_libs.end() - 1) : _currentLib - 1;
            break;
        case 'z':
            _currentLib = (_currentLib == _libs.end() - 1) ? (_libs.begin()) : _currentLib + 1;
            break;
        case 'o':
            _currentGame = (_currentGame == _games.begin()) ? (_games.end() - 1) : _currentGame - 1;
            break;
        case 'p':
            _currentGame = (_currentGame == _games.end() - 1) ? (_games.begin()) : _currentGame + 1;
            break;
        case 'q':
        case 27:
            _exit();
            break;
    }
    if (key == 'a' || key == 'z') {
        _module->destroyWindow();
        setModule("./lib/" + *_currentLib);
        _module->initWindow(100, 40, "ARCADE");
    } else if ((key == 'o' || key == 'p') && _inGame) {
        setGame("./games/" + *_currentGame);
        launchGame();
    }
}

void Core::_scoreMenu()
{
    int i = 1, input = -1;
    bool exit = false;
    
    _module->clear();
    while (!exit) {
        i = 1;
        _module->renderText("Score menu", 0, 2, TOP | CENTER, BOLD | UNDERLINE, WHITE);
        _module->renderText("[H]: Quit score menu", 0, 6, TOP | CENTER, ITALIC, WHITE);
        if (_scores.size() == 0)
            _module->renderText("No scores...", 0, 8, TOP | CENTER, BOLD | ITALIC);
        else {
            for (auto it : _scores) {
                _module->renderText(std::to_string(i) + ". " + it.second.first, 25, 8 + i, TOP | LEFT, BOLD, WHITE);
                _module->renderText(":", 0, 8 + i, TOP | CENTER);
                _module->renderText(std::to_string(it.first) + "(" + it.second.second + ")", -25, 8 + i, TOP | RIGHT, NORMAL, GREEN);
                i++;
            }
        }
        if ((input = _module->getInputs()) == 'h')
            exit = true;
        _readModuleKey(input);
    }
    _module->clear();
}

void Core::_mainMenu()
{
    bool insertMode = false;
    int input = 0;
    std::string username = "";

    _module->clear();
    /**
     * @note Main loop to display menu.
     */
    while (1) {
        /**
         * @note First display the keys.
         */
        _module->renderText("Welcome on Arcade !", 0, 2, TOP | CENTER, BOLD | UNDERLINE, WHITE);
        _module->renderText("[Q]/[ESC]: Quit the program", 0, 6, TOP | CENTER, ITALIC);
        _module->renderText("[A]: Previous lib / [Z]: Next lib", 0, 7, TOP | CENTER, ITALIC);
        _module->renderText("[O]: Previous game / [P]: Next game", 0, 8, TOP | CENTER, ITALIC);
        _module->renderText("[I]: Insert your username, insert mode: ", 0, 9, TOP | CENTER, ITALIC);
        _module->renderText((insertMode) ? "activated" : "disabled", 25, 9, TOP | CENTER, NORMAL, (insertMode) ? CYAN : RED);
        _module->renderText("[S]: Users scores", 0, 10, TOP | CENTER, ITALIC);
        _module->renderText("[ENTER]: Launch game!", 0, 11, TOP | CENTER, ITALIC);

        /**
         * @note Then display the games and libs.
         */
        _module->renderText((_libs.size() == 0) ? "No libs found..." : "List of library:", 0, 15, TOP | CENTER, BOLD, WHITE);
        for (size_t i = 0; i < _libs.size(); i++)
            _module->renderText(_libs[i], 0, 17 + i, TOP | CENTER, NORMAL, (_libs[i] == *_currentLib) ? CYAN : DEFAULT);
        _module->renderText((_games.size() == 0) ? "No games found..." : "List of game:", 0, 23, TOP | CENTER, BOLD, WHITE);
        for (size_t i = 0; i < _games.size(); i++)
            _module->renderText(_games[i], 0, 25 + i, TOP | CENTER, NORMAL, (_games[i] == *_currentGame) ? CYAN : DEFAULT);
        _module->renderText("USERNAME", 0, 31, TOP | CENTER, BOLD | ITALIC, WHITE);
        _module->renderText("[" + username + "]", 0, 32, TOP | CENTER, ITALIC | BOLD);

        /**
         * @note And last we read the keys pressed by user and process it.
         */
        if ((input = _module->getInputs()) != 8 && input != 27 && input != -1 && insertMode && username.size() <= 16) {
            _module->clear();
            username.push_back(input);
        } else if (input == 8 && insertMode && username.size() > 0) {
            _module->clear();
            username.pop_back();
        } else if (input == 27 && insertMode) {
            _module->clear();
            insertMode = false;
        } else if (!insertMode) {
            switch (input) {
                case 'i':
                    _module->clear();
                    insertMode = true;
                    break;
                case 's':
                    _scoreMenu();
                    break;
                case 13:
                    _module->clear();
                    setGame("./games/" + *_currentGame);
                    launchGame();
                    break;
                default:
                    _readModuleKey(input);
            }
        }
    }
}

void Core::_exit()
{
    if (_game != nullptr) {
        if (_gameDestroyer == nullptr)
            delete(_game);
        else
            _gameDestroyer(_game);
    }
    if (_module != nullptr) {
        _module->destroyWindow();
        if (_moduleDestroyer == nullptr)
            delete(_module);
        else
            _moduleDestroyer(_module);
    }
    exit(0);
}

void Core::launchGame()
{
    int input = -1;

    if (_game == nullptr)
        return;

    /**
     * @note First we launch the game.
     */
    _module->clear();
    _inGame = true;
    _game->initGame();

    /**
     * @note Here is the game loop.
     */
    bool debug = false;
    while (!(debug = _game->isEndGame())) {
        input = _game->coreGame();
        _readModuleKey(input);
        if (input == 'r') {
            _module->clear();
            _game->endGame();
            _game->initGame();
        }
        if (input == 'h') {
            _game->endGame();
            _module->clear();
            return;
        }
    }
    
    /**
     * @note Exiting the while loop upper means that the game is over
     * in this case we print out Game Over screen.
     */
    _game->endGame();
    _module->clear();
    for (int i = -30; i <= -5; i++) {
        _module->clear();
        _module->renderText("GAME OVER!", 0, i, CENTER | MIDDLE, NORMAL, RED);
        _readModuleKey(_module->getInputs());
        usleep(100000);
    }
    while (1) {
        // Reprint GAME OVER to keep it on the screen wether the module changes.
        _module->renderText("GAME OVER!", 0, -5, CENTER | MIDDLE, NORMAL, RED);
        _module->renderText("Score:", 40, 0, LEFT | MIDDLE, BOLD, WHITE);
        _module->renderText(std::to_string(_game->getScore()), -40, 0, RIGHT | MIDDLE, NORMAL, GREEN);
        _module->renderText("[R]: Restart game", 0, 4, CENTER | MIDDLE, ITALIC, WHITE);
        _module->renderText("[H]: Go back to main menu", 0, 5, CENTER | MIDDLE, ITALIC, WHITE);
        input = _module->getInputs();
        _readModuleKey(input);
        if (input == 'r')
            break;
        else if (input == 'h') {
            _module->clear();
            return;
        }
    }
    launchGame();
}

void Core::launch(const std::string &lib)
{
    if (_module == nullptr)
        return;

    /**
     * @note Get the list of libs and games.
     */
    _libs = _readDirectory("./lib");
    _games = _readDirectory("./games");
    _currentLib = std::find(_libs.begin(), _libs.end(), lib.substr(4));
    _currentGame = _games.begin();
    _scores = _readScores();

    /**
     * @note Open the main menu.
     */
    _module->initWindow(100, 40, "ARCADE");
    _mainMenu();
    _module->destroyWindow();
}