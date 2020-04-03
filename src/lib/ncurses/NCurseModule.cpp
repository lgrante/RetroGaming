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
    _size.w = width;
    _size.h = height;
    _size.wUnit = 1;
    _size.hUnit = 1;
}

void NCurseModule::destroyWindow()
{
    endwin();
    delete (_ncWindow);
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