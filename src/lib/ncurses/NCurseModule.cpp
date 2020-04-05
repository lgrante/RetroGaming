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
    _module = NCURSE;
}

NCurseModule::~NCurseModule()
{
}

void NCurseModule::initWindow(const size_t &width, const size_t &height, const std::string &title)
{
    int err_stat = 0;
    struct winsize size;

    ioctl(1, TIOCGWINSZ, &size);
    if (width > size.ws_col || height > size.ws_row)
        throw InitWindowException("Provided width and height are out of bounds", __FILE__, __LINE__); 
    initscr();
    _ncWindow = newwin(height, width, (size.ws_row / 2) - (height / 2), (size.ws_col / 2) - (width / 2));
    if (_ncWindow == nullptr) {
        endwin();
        throw InitWindowException("Failed to open ncurses window", __FILE__, __LINE__);
    }
    curs_set(0);
    start_color();
    use_default_colors();
    cbreak();
    noecho();
    err_stat = keypad(_ncWindow, TRUE);
    if (err_stat == ERR) {
        endwin();
        throw InitKeyException("Failed to enable user's keypad", __FILE__, __LINE__);
    }
    box(_ncWindow, 0, 0);
    wattron(_ncWindow, A_BOLD);
    mvwprintw(_ncWindow, 0, (width / 2) - (title.size() / 2), title.c_str());
    wattroff(_ncWindow, A_BOLD);
    wrefresh(_ncWindow);
    _size.w = width;
    _size.h = height;
    _size.wUnit = 1;
    _size.hUnit = 1;
    for (int color = COLOR_BLACK; color <= COLOR_WHITE; color++)
        init_pair(color + 1, color, -1);
}

void NCurseModule::destroyWindow()
{
    endwin();
}

/**
 * @note In render and renderText I add 1 to Y and X because 0 coordinates is the border of the box.
 * 
 */

void NCurseModule::render(const std::map<std::string, Object> &gamesData)
{
    for (std::pair<std::string, Object> i : gamesData)
        mvwprintw(_ncWindow, i.second.getY() + 1, i.second.getX() + 1, i.second.getNcTexture().getTexture().c_str());
    wrefresh(_ncWindow);
}

void NCurseModule::renderText(const std::string &text, const int &x, const int &y, uint16_t alignment, uint16_t style, color color)
{
    std::map<textStyle, int> ncStyles = {
        {NORMAL, A_NORMAL},
        {BOLD, A_BOLD},
        {ITALIC, A_ITALIC},
        {UNDERLINE, A_UNDERLINE}
    };
    int xPxl = x + 1, yPxl = y + 1;

    _computeTextPosition(xPxl, yPxl, alignment, text.size());
    for (std::pair<textStyle, int> i : ncStyles)
        if (style & i.first)
            wattron(_ncWindow, i.second);
    wattron(_ncWindow, COLOR_PAIR(color + 1));
    mvwprintw(_ncWindow, yPxl, xPxl, text.c_str());
    wattroff(_ncWindow, COLOR_PAIR(color + 1));
    for (std::pair<textStyle, int> i : ncStyles)
        if (style & i.first)
            wattroff(_ncWindow, i.second);
    wrefresh(_ncWindow);
}

void NCurseModule::clear()
{
    wclear(_ncWindow);
    box(_ncWindow, 0, 0);
}

int NCurseModule::getInputs()
{
    int key = wgetch(_ncWindow);
    
    if (key == 263)
        return 8;
    return key;
}