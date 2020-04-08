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
    nodelay(_ncWindow, TRUE);
    err_stat = keypad(_ncWindow, TRUE);
    if (err_stat == ERR) {
        endwin();
        throw InitKeyException("Failed to enable user's keypad", __FILE__, __LINE__);
    }
    box(_ncWindow, 0, 0);
    wattron(_ncWindow, A_BOLD);
    mvwprintw(_ncWindow, 0, (width / 2) - (title.size() / 2), title.c_str());
    wattroff(_ncWindow, A_BOLD);
    _size.wUnit = 1920 / size.ws_col;
    _size.hUnit = 1080 / size.ws_row;
    _size.w = width * _size.wUnit;
    _size.h = height * _size.hUnit;

    /**
     * @note Default background and foreground color.
     */
    init_pair(0, -1, -1);
    /**
     * @note Only foreground colors, from 1 to 8.
     */
    for (int color = BLACK; color <= WHITE; color++)
        init_pair(color + FG_COLOR_BEGIN, color, -1);
    /**
     * @note Only background colors, from 10 to 17.
     */
    for (int color = BLACK; color <= WHITE; color++)
        init_pair(color + BG_COLOR_BEGIN, -1, color);
    /**
     * @note And all color pairs (background and foreground) from 20 to 83.
     */
    for (int i = BLACK; i <= WHITE; i++)
        for (int j = BLACK; j <= WHITE; j++)
            init_pair(PAIR_COLOR_BEGIN + ((i * 8) + j), i, j);
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
    for (std::pair<std::string, Object> i : gamesData) {
        uint16_t style = i.second.getNcStyle();
        color fgColor = i.second.getNcFgColor();
        color bgColor = i.second.getNcBgColor();
        std::string texture;

        /**
         * @note Setting character, style and color.
         */
        texture.push_back(i.second.getNcTexture());
        for (std::pair<textStyle, int> s : _ncStyles)
            if (style & s.first)
                wattron(_ncWindow, s.second);
        wattron(_ncWindow, _getColorPair(fgColor, bgColor));

        mvwprintw(_ncWindow, (i.second.getY() + 1) / _size.hUnit, (i.second.getX() + 1) / _size.wUnit, texture.c_str());
        
        /**
         * @note Unsetting color and style.
         */
        wattroff(_ncWindow, _getColorPair(fgColor, bgColor));
        for (std::pair<textStyle, int> s : _ncStyles)
            if (style & s.first)
                wattroff(_ncWindow, s.second);
    }
    wrefresh(_ncWindow);
}

void NCurseModule::renderText(const std::string &text, const int &x, const int &y, uint16_t alignment, uint16_t style, color color)
{

    int xPxl = x + 1, yPxl = y + 1;
    size_t len = text.size();

    xPxl += (alignment & CENTER) ? ((_size.getWidthInUnit() / 2) - (len / 2)) : 0;
    xPxl += (alignment & RIGHT) ? ((_size.getWidthInUnit() - 1) - len) : 0;
    yPxl += (alignment & MIDDLE) ? (_size.getHeightInUnit() / 2) : 0;
    yPxl += (alignment & BOTTOM) ? (_size.getHeightInUnit() - 3) : 0;
    for (std::pair<textStyle, int> i : _ncStyles)
        if (style & i.first)
            wattron(_ncWindow, i.second);
    wattron(_ncWindow, _getColorPair(color, -1));
    mvwprintw(_ncWindow, yPxl, xPxl, text.c_str());
    wattroff(_ncWindow, _getColorPair(color, -1));
    for (std::pair<textStyle, int> i : _ncStyles)
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
    if (key == 10)
        return 13;
    return key;
}