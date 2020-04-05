#include "SFMLModule.hpp"

extern "C" Module *create()
{
    return new SFMLModule;
}

extern "C" void destroy(Module *module)
{
    delete(module);
}

SFMLModule::SFMLModule()
{
    _module = SFML;
}

SFMLModule::~SFMLModule()
{
}

void SFMLModule::initWindow(const size_t &width, const size_t &height, const std::string &title)
{
    _size.wUnit = sf::VideoMode::getDesktopMode().width / COLS;
    _size.hUnit = sf::VideoMode::getDesktopMode().height / ROWS;
    _size.w = _size.wUnit * width;
    _size.h = _size.hUnit * height;
    _sfWindow = new sf::RenderWindow(sf::VideoMode(_size.w, _size.h), title);
}

void SFMLModule::destroyWindow()
{
    _sfWindow->clear();
    _sfWindow->close();
}

void SFMLModule::render(const std::map<std::string, Object> &gameDatas)
{
    for (std::pair<std::string, Object> i : gameDatas)
        _sfWindow->draw(i.second.getSfSprite());
    _sfWindow->display();
}

void SFMLModule::renderText(const std::string &text, const int &x, const int &y, uint16_t alignment, uint16_t style, color color)
{
    sf::Font font;
    sf::Text renderText;
    sf::FloatRect rect;
    sf::RectangleShape empty;
    int xPxl = x, yPxl = y;
    std::map<enum color, sf::Color> sfColors = {
        {BLACK, sf::Color(0, 0, 0)},
        {RED, sf::Color(255, 0, 0)},
        {GREEN, sf::Color(0, 255, 0)},
        {YELLOW, sf::Color(255, 255, 0)},
        {BLUE, sf::Color(0, 0, 255)},
        {MAGENTA, sf::Color(255, 0, 255)},
        {CYAN, sf::Color(0, 255, 255)},
        {WHITE, sf::Color(255, 255, 255)}
    };
    std::map<textStyle, sf::Text::Style> sfStyles = {
        {BOLD, sf::Text::Bold},
        {ITALIC, sf::Text::Italic},
        {UNDERLINE, sf::Text::Underlined}
    };

    if (!font.loadFromFile(FONT_PATH))
        throw InitTextException("Failed to init text", __FILE__, __LINE__);
    renderText.setString(text);
    renderText.setFont(font);
    renderText.setCharacterSize(32);
    renderText.setColor(sfColors[color]);
    for (std::pair<textStyle, sf::Text::Style> i : sfStyles)
        if (i.first & style)
            renderText.setStyle(i.second);

    rect = renderText.getLocalBounds();
    _computeTextPosition(xPxl, yPxl, alignment, rect.width);
    renderText.setPosition(xPxl, yPxl);

    empty.setSize(sf::Vector2f(rect.width + 30, rect.height));
    empty.setPosition(sf::Vector2f(xPxl, yPxl + 10));
    empty.setFillColor(sf::Color(0, 0, 0));

    //_sfWindow->draw(empty);
    _sfWindow->draw(renderText);
    _sfWindow->display();
}

void SFMLModule::clear()
{
    _sfWindow->clear();
}

int SFMLModule::getInputs()
{
    sf::Event event;

    while (_sfWindow->pollEvent(event)) {
        if (event.type == sf::Event::TextEntered) {
            std::cout << "Key pressed: " << event.text.unicode << std::endl;
            return event.text.unicode;
        }
    }
    return -1;
}
