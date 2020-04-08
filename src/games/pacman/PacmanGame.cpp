#include "PacmanGame.hpp"

extern "C" Game *create()
{
    return new PacmanGame;
}

extern "C" void destroy(Game *game)
{
    delete(game);
}

PacmanGame::PacmanGame()
{
    _name = "Pacman";
}

PacmanGame::~PacmanGame()
{
}

void PacmanGame::initGame()
{
    int cols = 0, rows = 0;
    int xOrigin = 0, yOrigin = 0;
    std::string line;
    std::ifstream file("./src/games/pacman/level1.map");

    _wallNb = 0;
    _pacgumNb = 0;
    _bigPacgumNb = 0;
    _xDirection = 0;
    _yDirection = 0;
    _exitNb = 2;
    _module->getWindowSize(cols, rows, false);
    xOrigin = (cols / 2) - 9;
    yOrigin = (rows / 2) - 11;
    for (int x = 0, y = 0; std::getline(file, line); y++) {
        for (x = 0; x < (int) line.size(); x++) {
            if (line[x] == '#') {
                _module->setObject(_data, "wall_" + std::to_string(_wallNb), GT_PATH "pacman/wall.png", TT_PATH "pacman/wall", x + xOrigin, y + yOrigin); 
                _wallNb++;
            } if (line[x] == '.') {
                _module->setObject(_data, "pacgum_" + std::to_string(_pacgumNb), GT_PATH "pacman/pacgum.png", TT_PATH "pacman/pacgum", x + xOrigin, y + yOrigin); 
                _pacgumNb++;
            } if (line[x] == 'O') {
                _module->setObject(_data, "big_pacgum_" + std::to_string(_bigPacgumNb), GT_PATH "pacman/big_pacgum.png", TT_PATH "pacman/big_pacgum", x + xOrigin, y + yOrigin); 
                _bigPacgumNb++;
            }
        }
    }
    /**
     * @note Add player and ghost ennemies.
     */
    _module->setObject(_data, "player", GT_PATH "pacman/player.png", TT_PATH "pacman/player", xOrigin + 9, yOrigin + 12); 
    _module->setObject(_data, "ghost_1", GT_PATH "pacman/ghost_1.png", TT_PATH "pacman/ghost_1", xOrigin + 8, yOrigin + 9); 
    _module->setObject(_data, "ghost_2", GT_PATH "pacman/ghost_2.png", TT_PATH "pacman/ghost_2", xOrigin + 10, yOrigin + 9); 
    _module->setObject(_data, "ghost_3", GT_PATH "pacman/ghost_3.png", TT_PATH "pacman/ghost_3", xOrigin + 8, yOrigin + 10); 
    _module->setObject(_data, "ghost_4", GT_PATH "pacman/ghost_4.png", TT_PATH "pacman/ghost_4", xOrigin + 10, yOrigin + 10); 

    /**
     * @note Add exits that teleports the player.
     */
    _module->setObject(_data, "left_exit_1", GT_PATH "pacman/exit.png", TT_PATH "pacman/exit", xOrigin + 0, yOrigin + 9); 
    _module->setObject(_data, "left_exit_2", GT_PATH "pacman/exit.png", TT_PATH "pacman/exit", xOrigin + 0, yOrigin + 10); 
    _module->setObject(_data, "right_exit_1", GT_PATH "pacman/exit.png", TT_PATH "pacman/exit", xOrigin + 18, yOrigin + 9); 
    _module->setObject(_data, "right_exit_2", GT_PATH "pacman/exit.png", TT_PATH "pacman/exit", xOrigin + 18, yOrigin + 10); 
}

int PacmanGame::coreGame()
{
    int xObject_1 = 0, yObject_1 = 0;
    int xObject_2 = 0, yObject_2 = 0;
    int xPlayer = 0, yPlayer = 0;
    bool collision = false;
    int input = -1;

    _module->clear();
    _module->renderText("[S]: Left / [F]: Right / [E]: Top / [D]: Down", -5, 0, BOTTOM | RIGHT, ITALIC);
    _module->renderText("[R]: Restart / [H]: Menu / [Q]/[ESC]: Exit", 3, 0, BOTTOM | LEFT, ITALIC);
    _module->renderText("Score:", 40, 1, LEFT | TOP, BOLD);
    _module->renderText(std::to_string(_score), -40, 1, RIGHT | TOP, NORMAL, GREEN);

    /**
     * @note Read arrow key to move.
     */
    input = readMoveKey(_xDirection, _yDirection);

    /**
     * @note If player don't move on a wall we move it otherwise we does nothin.
     */
    _module->getObjectCoordinates(_data, "player", xPlayer, yPlayer);
    for (int i = 0; i < _wallNb; i++) {
        _module->getObjectCoordinates(_data, "wall_" + std::to_string(i), xObject_1, yObject_1);
        if (xPlayer + _xDirection == xObject_1 && yPlayer + _yDirection == yObject_1)
            collision = true;
    }
    
    /**
     * @note Check if players goes on exit, in this case we teleport it.
     */
    for (int i = 1; i <= _exitNb; i++) {
        _module->getObjectCoordinates(_data, "left_exit_" + std::to_string(i), xObject_1, yObject_1);
        _module->getObjectCoordinates(_data, "right_exit_" + std::to_string(i), xObject_2 , yObject_2);

        // If we go on left exit we teleport the player to right exit.
        if (xPlayer + _xDirection == xObject_1 && yPlayer + _yDirection == yObject_1) {
            _module->moveObject(_data, "player", "right_exit_" + std::to_string(i));
            break;
        }
        
        // If we go on right exit we teleport the player to left exit.
        if (xPlayer + _xDirection == xObject_2 && yPlayer + _yDirection == yObject_2) {
            _module->moveObject(_data, "player", "left_exit_" + std::to_string(i));
            break;
        }
    }

    /**
     * @note Finally move the player if there is no collision with a wall.
     */
    if (!collision)
        _module->moveObject(_data, "player", _xDirection, _yDirection);
    
    /**
     * @note If player goes into pacgum destroy it and increment the score.
     */
    for (int i = 0; i < _pacgumNb; i++) {
        _module->getObjectCoordinates(_data, "pacgum_" + std::to_string(i), xObject_1, yObject_1);
        if (xPlayer + _xDirection == xObject_1 && yPlayer + _yDirection == yObject_1) {
            _module->destroyObject(_data, "pacgum_" + std::to_string(i));
            _score++;
        }
    }

    
   
    _module->render(_data);

    usleep(100000);

    return input;
}

bool PacmanGame::isEndGame()
{
    return false;
}
