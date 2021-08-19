#include <iostream>
#include "PhysicsGame.h"
int main()
{
    PhysicsGame* game = new PhysicsGame();

    game->run("PhysicsGame", 1280, 720, false);

    delete game;

    return 0;
}
