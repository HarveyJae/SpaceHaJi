#include <iostream>
#include "main.h"
#include "GameManager.h"
int main(int, char **)
{
    std::cout << "hello spaceshoot" << std::endl;
    GameManager *game = new GameManager();
    if (game == nullptr)
    {
        std::cout << "game new failed." << std::endl;
        return -1;
    }
    game->init();
    game->run();
    return 0;
}
