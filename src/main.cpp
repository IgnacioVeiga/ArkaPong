#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <time.h>
#include "Game.h"

int main(int argc, char* argv[])
{
    srand(time(nullptr));

    Game game;

    if (!game.Init()) return 1;
    game.Run();
    game.CleanUp();

    return 0;
}
