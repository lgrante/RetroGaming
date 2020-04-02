#include "NCurseModule.hpp"

extern "C" Module *create()
{
    return new NCurseModule;
}

extern "C" void destroy(Module *module)
{
    delete module;
}

NCurseModule::NCurseModule()
{
}

NCurseModule::~NCurseModule()
{
}

void NCurseModule::initWindow(const size_t &width, const size_t &height, const std::string &title)
{
    _ncWindow = newwin(width, height, 0, 0);
    int keypad_stat = 0;

    mvwprintw(_ncWindow, 0, 0, title.c_str());
    if (_ncWindow == nullptr)
        throw InitWindowException("Failed to open ncurses window", __LINE__);
    keypad_stat = keypad(_ncWindow, TRUE);
    if (keypad_stat == ERR)
        throw InitKeyException("Failed to enable user's keypad", __LINE__);
}

void NCurseModule::destroyWindow()
{
    endwin();
    delete (_ncWindow);
}

void NCurseModule::setObject(
    std::map<std::string, Object> &gameDatas,
    const std::string &name, const std::string &sfTexturePath, const std::string &ncTexturePath, 
    const int &x, const int &y
)
{
    if (x >= 0 && x < (int) _width && y >= 0 && y < (int) _height) {
        Object newObject(sfTexturePath, ncTexturePath, x, y);

        gameDatas.emplace(name, newObject);
    }
}

void NCurseModule::setObjectCoordinates(std::map<std::string, Object> &gameDatas, const std::string &name, const int &x, const int &y)
{
    std::map<std::string, Object>::iterator it = gameDatas.find(name);

    if (it != gameDatas.end() && x >= 0 && x < (int) _width && y >= 0 && y < (int) _height) {
        it->second.setX(x);
        it->second.setY(y);
    }
}

void NCurseModule::render(const std::map<std::string, Object> &gamesData)
{
    for (std::pair<std::string, Object> i : gamesData)
        mvwprintw(_ncWindow, i.second.getY(), i.second.getX(), i.second.getNcTexture().getTexture().c_str());
}

int NCurseModule::getInputs()
{
    return getch();
}