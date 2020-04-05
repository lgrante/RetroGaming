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
    SDL_DisplayMode size;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_GetDesktopDisplayMode(0, &size);
    _size.wUnit = size.w / COLS;
    _size.hUnit = size.h / ROWS;
    _size.w = _size.wUnit * width;
    _size.h = _size.hUnit * height;
    _sdlWindow = SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        _size.w, _size.h, SDL_WINDOW_OPENGL
    );
    if (_sdlWindow == nullptr)
        throw InitWindowException("Failed to init SDL window", __FILE__, __LINE__);
    _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (_sdlRenderer == nullptr)
        throw InitWindowException("Failed to init SDL renderer", __FILE__, __LINE__);
}

void SDLModule::destroyWindow()
{
    SDL_DestroyRenderer(_sdlRenderer);
    SDL_DestroyWindow(_sdlWindow);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDLModule::render(const std::map<std::string, Object> &gamesData)
{
    /*
    SDL_Rect rect = {0, 0, _size.wUnit, _size.hUnit};

    for (std::pair<std::string, Object> i : gamesData) {
        rect.x = i.second.getX();
        rect.y = i.second.getY();
        SDL_BlitSurface(i.second.getSdlTexture(), NULL, _sdlWindow, &rect);
    }
    SDL_UpdateRect(_sdlWindow, 0, 0, 0, 0);
    */
}

void SDLModule::renderText(const std::string &text, const int &x, const int &y, uint16_t alignment, uint16_t style, color color)
{
    std::map<enum color, SDL_Color> sdlColors = {
        {BLACK, {0, 0, 0, 255}},
        {RED, {255, 0, 0, 255}},
        {GREEN, {0, 255, 0, 255}},
        {YELLOW, {255, 255, 0, 255}},
        {BLUE, {0, 0, 255, 255}},
        {MAGENTA, {255, 0, 255, 255}},
        {CYAN, {0, 255, 255, 255}},
        {WHITE, {255, 255, 255, 255}}
    };
    std::map<textStyle, int> sdlStyle = {
        {NORMAL, TTF_STYLE_NORMAL},
        {BOLD, TTF_STYLE_BOLD},
        {ITALIC, TTF_STYLE_ITALIC},
        {UNDERLINE, TTF_STYLE_UNDERLINE}
    };

    int xPxl = x, yPxl = y, w = 0, h = 0;
    SDL_Rect position;

    TTF_Font *font = TTF_OpenFont(FONT_PATH, 32);
    SDL_Surface *textSurface = nullptr;
    SDL_Texture *textTexture = nullptr;
    SDL_Color textColor = sdlColors.at(color);

    for (std::pair<textStyle, int> i : sdlStyle)
        if (i.first & style)
            TTF_SetFontStyle(font, i.second);

    textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(_sdlRenderer, textSurface);
    SDL_QueryTexture(textTexture, NULL, NULL, &w, &h);
    _computeTextPosition(xPxl, yPxl, alignment, w);
    position.x = (Sint16) xPxl;
    position.y = (Sint16) yPxl;
    position.w = (Sint16) w;
    position.h = (Sint16) h;

    SDL_RenderCopy(_sdlRenderer, textTexture, NULL, &position);
    SDL_RenderPresent(_sdlRenderer);

    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void SDLModule::clear()
{
    SDL_SetRenderDrawColor(_sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(_sdlRenderer);
}

int SDLModule::getInputs()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
    return -1;
}