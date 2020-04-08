#include "NibblerGame.hpp"

extern "C" Game *create()
{
    return new NibblerGame;
}

extern "C" void destroy(Game *game)
{
    delete(game);
}

NibblerGame::NibblerGame()
{
    _name = "Nibbler";
}

NibblerGame::~NibblerGame()
{
}

void NibblerGame::initGame()
{
    int cols = 0, rows = 0;

    srand((unsigned int) time(nullptr));

    _module->getWindowSize(cols, rows, false);
    /**
     * @note Generate snake head and body.
     */
    _module->setObject(
        _data, "snake_0", GT_PATH "nibbler/snake_head.png", TT_PATH "nibbler/snake_head", 
        (cols / 2) - 2, rows / 2
    );
    for (int i = 1; i < 4; i++)
        _module->setObject(
            _data, "snake_" + std::to_string(i), GT_PATH "nibbler/snake_core.png", TT_PATH "nibbler/snake_core", 
            (cols / 2) + (i - 2), rows / 2 
        );
    
    /**
     * @note Generate fruit at random position.
     */
    _module->setObject(
        _data, "fruit", GT_PATH "nibbler/fruit.png", TT_PATH "nibbler/fruit", 
        (rand() % (cols - 3)) + 1, (rand() % (rows - 3)) + 1
    );

    /**
     * @note Generate walls.
     */
    _wallNb = ((rand() % 20) + 10);
    for (int i = 0; i < _wallNb; i++)
        _module->setObject(
            _data, "wall_" + std::to_string(i), GT_PATH "nibbler/wall.png", TT_PATH "nibbler/wall", 
            (rand() % (cols - 3)) + 1, (rand() % (rows - 3)) + 1
        );

    _score = 0;
    _prevXDirection = -1;
    _prevYDirection = 0;
    _xDirection = -1;
    _yDirection = 0;
    _squareNb = 4;
}

int NibblerGame::coreGame()
{
    int input = -1;
    int cols = 0, rows = 0;
    int previousSqX = 0, previousSqY = 0;
    int sqX = 0, sqY = 0;

    _module->clear();
    _module->renderText("[S]: Left / [F]: Right / [E]: Top / [D]: Down", -5, 0, BOTTOM | RIGHT, ITALIC);
    _module->renderText("[R]: Restart / [H]: Menu / [Q]/[ESC]: Exit", 3, 0, BOTTOM | LEFT, ITALIC);
    _module->renderText("Score:", 40, 1, LEFT | TOP, BOLD);
    _module->renderText(std::to_string(_score), -40, 1, RIGHT | TOP, NORMAL, GREEN);

    /**
     * @note Get the direction key and change the snake direction.
     */
    _prevXDirection = _xDirection;
    _prevYDirection = _yDirection;
    switch ((input = _module->getInputs())) {
        case 'e':
            _yDirection = -1;
            _xDirection = 0;
            break;
        case 'd':
            _yDirection = 1;
            _xDirection = 0;
            break;
        case 's':
            _xDirection = -1;
            _yDirection = 0;
            break;
        case 'f':
            _xDirection = 1;
            _yDirection = 0;
            break;
    }

    /**
     * @note Move all the snake squares.
     */
    if ((_yDirection == 0 || _yDirection != -1 * _prevYDirection) && (_xDirection == 0 || _xDirection != -1 * _prevXDirection)) {
        _module->getObjectCoordinates(_data, "snake_0", previousSqX, previousSqY);
        _module->moveObject(_data, "snake_0", _xDirection, _yDirection);
        for (int i = 1; i < _squareNb; i += 2) {
            _module->getObjectCoordinates(_data, "snake_" + std::to_string(i), sqX, sqY);
            _module->setObjectCoordinates(_data, "snake_" + std::to_string(i), previousSqX, previousSqY);
            if (i + 1 < _squareNb) {
                _module->getObjectCoordinates(_data, "snake_" + std::to_string(i + 1), previousSqX, previousSqY);
                _module->setObjectCoordinates(_data, "snake_" + std::to_string(i + 1), sqX, sqY);
            }
        }
    } else {
        _xDirection = _prevXDirection;
        _yDirection = _prevYDirection;
    }

    /**
     * @note Check if the snake eat the fruit. If it's the case we add a square to the snake,
     * remove current fruit, add a new one at random coordinates and increment the score.
     */
    // Check if coordinates of snake head are the same as the fruit coordinates.
    _module->getObjectCoordinates(_data, "snake_0", previousSqX, previousSqY);
    _module->getObjectCoordinates(_data, "fruit", sqX, sqY);
    
    if (previousSqX == sqX && previousSqY == sqY) {

        // Add new square.
        _module->getObjectCoordinates(_data, "snake_" + std::to_string(_squareNb - 1), sqX, sqY);
        _module->setObject(
            _data, "snake_" + std::to_string(_squareNb), GT_PATH "nibbler/snake_core.png", TT_PATH "nibbler/snake_core", 
            sqX - _xDirection, sqY - _yDirection
        );

        // Destroy and generate new fruit.
        _module->destroyObject(_data, "fruit");
        _module->getWindowSize(cols, rows, false);
        _module->setObject(
            _data, "fruit", GT_PATH "nibbler/fruit.png", TT_PATH "nibbler/fruit", 
            (rand() % (cols - 3)) + 1, (rand() % (rows - 3)) + 1
        );
        _squareNb++;

        // Finally we increment the score
        _score += 10;
    }

    /**
     * @note Sometimes we add one wall on the map to make the game harder :p
     */
    if (_score % 20 == 0) {
        _module->setObject(
            _data, "wall_" + std::to_string(_wallNb), GT_PATH "nibbler/wall.png", TT_PATH "nibbler/wall", 
            (rand() % (cols - 3)) + 1, (rand() % (rows - 3)) + 1
        );
        _wallNb++;
    }

    /**
     * @note Finally render all the objects.
     */
    _module->render(_data);

    usleep(100000 - (_score * 300));

    return input;
}

bool NibblerGame::isEndGame()
{
    int headX = 0, headY = 0;
    int cols = 0, rows = 0;

    _module->getObjectCoordinates(_data, "snake_0", headX, headY);
    _module->getWindowSize(cols, rows, false);

    /**
     * @note Check if the snake go out of window borders.
     */
    if (headX < 0 || headX >= cols - 2 || headY < 0 || headY >= rows - 2)
        return true;

    /**
     * @note Check if snake head touch its body.
     */
    for (int i = 1; i < _squareNb; i++) {
        int x = 0, y = 0;

        _module->getObjectCoordinates(_data, "snake_" + std::to_string(i), x, y);
        if (headX == x && headY == y)
            return true;
    }
    for (int i = 1; i < _wallNb; i++) {
        int x = 0, y = 0;

        _module->getObjectCoordinates(_data, "wall_" + std::to_string(i), x, y);
        if (headX == x && headY == y)
            return true;
    }
    return false;
}
