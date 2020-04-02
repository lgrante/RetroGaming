#include "Core.hpp"

Core::Core(const std::string &gamePath, const std::string &modulePath)
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

    /** @note If game has already been loaded before we just set back its data
     *  otherwise we launch the game that will initialize its data.
     */
    _game->launchGame();
    if (it != _gamesData.end())
        _game->setData(it->second);
}

Module *Core::getModule() const
{
    return _module;
}

Game *Core::getGame() const
{
    return _game;
}