#include "SDLModule.hpp"

extern "C" Module *create()
{
    return new SDLModule;
}

extern "C" void destroy(Module *module)
{
    delete(module);
}

SDLModule::SDLModule()
{
    _module = SDL;
}

SDLModule::~SDLModule()
{
}

void SDLModule::initWindow(const size_t &width, const size_t &height, const std::string &title)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    struct winsize size;

    ioctl(1, TIOCGWINSZ, &size);
    _size.wUnit = size.ws_xpixel / size.ws_col;
    _size.hUnit = size.ws_ypixel / size.ws_row;
    _size.w = _size.wUnit * width;
    _size.h = _size.hUnit * height;
    SDL_WM_SetCaption(title.c_str(), title.c_str());
    _sdlWindow = SDL_SetVideoMode(_size.w, _size.h, 0, 0);
}

void SDLModule::destroyWindow()
{
    SDL_FreeSurface(_sdlWindow);
}

void SDLModule::render(const std::map<std::string, Object> &gamesData)
{
    SDL_Rect rect = {0, 0, _size.wUnit, _size.hUnit};

    for (std::pair<std::string, Object> i : gamesData) {
        rect.x = i.second.getX();
        rect.y = i.second.getY();
        SDL_BlitSurface(i.second.getSdlTexture(), NULL, _sdlWindow, &rect);
    }
    SDL_UpdateRect(_sdlWindow, 0, 0, 0, 0);
}

void SDLModule::renderText(const std::string &text, const int &x, const int &y, uint16_t alignment, uint16_t style, color color)
{
    int xPxl = x, yPxl = y, textWidth = 0;
    SDL_Rect position;
    TTF_Font *font = TTF_OpenFont(FONT_PATH, 24);
    SDL_Color textColor = {0, 0, 0, 0};
    SDL_Surface *textSurface  = nullptr;

    TTF_SizeText(font, text.c_str(), &textWidth, NULL);
    _computeTextPosition(xPxl, yPxl, alignment, textWidth);
    position.x = (Sint16) xPxl;
    position.y = (Sint16) yPxl;
    textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_BlitSurface(textSurface, NULL, _sdlWindow, &position);
}

int SDLModule::getInputs()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
    return -1;
}