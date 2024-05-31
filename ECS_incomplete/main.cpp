#include "Game.h"

int main(int argc, char *argv[])
{
    Game game;
    game.run();

    // EntityManager entityManager;
    // ComponentManager componentManager;
    
    // std::vector<std::pair<PositionComponent, RenderComponent>> entities;

    // // Crear entidades y añadir componentes
    // Entity playerLeft = entityManager.createEntity();
    // componentManager.addComponent(playerLeft.getId(), PositionComponent{50, SCREEN_HEIGHT / 2});
    // componentManager.addComponent(playerLeft.getId(), VelocityComponent{0, 0});
    // componentManager.addComponent(playerLeft.getId(), MovementComponent{PADDLE_SPEED});
    // componentManager.addComponent(playerLeft.getId(), InputComponent{SDL_SCANCODE_W, SDL_SCANCODE_S});

    // SDL_Texture *textureLeft;
    // textureLeft = TextureManager::LoadTexture("assets/sprites/paddle.bmp");

    // // Rectangle where the texture is rendered
    // SDL_Rect rectLeft = {
    //     PADDLE_OFFSET,                                  // X
    //     SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,          // Y
    //     PADDLE_WIDTH,                                   // W
    //     PADDLE_HEIGHT                                   // H
    // };
    // componentManager.addComponent(playerLeft.getId(), RenderComponent{textureLeft, rectLeft});

    // Entity playerRight = entityManager.createEntity();
    // componentManager.addComponent(playerRight.getId(), PositionComponent{SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2});
    // componentManager.addComponent(playerRight.getId(), VelocityComponent{0, 0});
    // componentManager.addComponent(playerRight.getId(), MovementComponent{PADDLE_SPEED});
    // componentManager.addComponent(playerRight.getId(), InputComponent{SDL_SCANCODE_UP, SDL_SCANCODE_DOWN});

    // SDL_Texture *textureRight;
    // textureRight = TextureManager::LoadTexture("assets/sprites/paddle.bmp");

    // // Rectangle where the texture is rendered
    // SDL_Rect rectRight = {
    //     SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH,    // X
    //     SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,          // Y
    //     PADDLE_WIDTH,                                   // W
    //     PADDLE_HEIGHT                                   // H
    // };
    // componentManager.addComponent(playerLeft.getId(), RenderComponent{textureRight, rectRight});

    // // entities.push_back(std::make_pair(pos, render));

    // InputSystem inputSystem;
    // inputSystem.addEntity(playerLeft);
    // inputSystem.addEntity(playerRight);

    // MovementSystem movementSystem;
    // movementSystem.addEntity(playerLeft);
    // movementSystem.addEntity(playerRight);

    // RenderSystem renderSystem;

    // const int FPS = 60;
    // const int frameDelay = 1000 / FPS;

    // Uint32 frameStart;
    // int frameTime;

    // SDL_Event event;
    // while (Game::game_on)
    // {
    //     frameStart = SDL_GetTicks();

    //     while (SDL_PollEvent(&event))
    //     {
    //         if (event.type == SDL_QUIT)
    //         {
    //             Game::game_on = false;
    //         }
    //     }

    //     inputSystem.update(componentManager);
    //     movementSystem.update(componentManager);
    //     renderSystem.render(entities);

    //     frameTime = SDL_GetTicks() - frameStart;
    //     if (frameDelay > frameTime)
    //     {
    //         SDL_Delay(frameDelay - frameTime);
    //     }
    // }

    return 0;
}
