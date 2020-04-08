#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define FONT_PATH "./assets/fonts/main_font.ttf"

#define COLS 159
#define ROWS 42

enum module {
    SFML,
    SDL,
    NCURSE
};

/**
 * @note It's possible to combine the flags like this:
 * LEFT | TOP // This will write the text in the top left corner of the screen.
 * 
 */
enum alignment {
    LEFT        = 1 << 0,
    CENTER      = 1 << 1,
    RIGHT       = 1 << 2,
    TOP         = 1 << 3,
    MIDDLE      = 1 << 4,
    BOTTOM      = 1 << 5
};

enum textStyle {
    NORMAL      = 1 << 0,
    BOLD        = 1 << 1,
    ITALIC      = 1 << 2,
    UNDERLINE   = 1 << 3
};

enum color {
    DEFAULT     = -1,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

#endif