#define SDL_MAIN_HANDLED

#include "Game.h"
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    Game game;

    if (game.Init() == 1)
        return 1;

    game.Run();
    game.CleanUp();
    return 0;
}
