#include <iostream>
#include "main.h"
#include "GameManager.h"
int main(int, char **)
{
    std::cout << "hello spaceshoot" << std::endl;
    GameManager &game = GameManager::getInstance();
    game.init();
    game.run();
    return 0;
}
