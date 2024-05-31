#include "PlayState.h"
#include "PauseState.h"
#include "GameConstants.h"
#include <Game.h>

PlayState::PlayState()
    : playerLeft(
          PADDLE_OFFSET),
      playerRight(
          SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH),
      ball()
{
    scoreManager = new ScoreManager();
    collisionManager = new CollisionManager(scoreManager);

    audioManager = new AudioManager();
    audioManager->loadSound("round_start", "assets/audio/bgm/round_start.wav");

    textManager = new TextManager();

    // Showing round number
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    textManager->renderText("Round 1", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(Game::renderer);
    SDL_Delay(3000);

    // Round starts
    audioManager->playSound("round_start");
    render();
    SDL_Delay(3000);
}

PlayState::~PlayState()
{
    delete scoreManager;
    delete collisionManager;
    delete audioManager;
    delete textManager;
}

void PlayState::handleInput()
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W])
    {
        playerLeft.moveUp();
    }
    else if (keystate[SDL_SCANCODE_S])
    {
        playerLeft.moveDown();
    }

    if (keystate[SDL_SCANCODE_UP])
    {
        playerRight.moveUp();
    }
    else if (keystate[SDL_SCANCODE_DOWN])
    {
        playerRight.moveDown();
    }

    if (keystate[SDL_SCANCODE_SPACE])
    {
        Game::flowManager->changeState(new PauseState());
    }
    else if (keystate[SDL_SCANCODE_ESCAPE])
    {
        Game::game_on = false;
    }
}

void PlayState::update()
{
    ball.move();
    collisionManager->handleWallCollisions(ball);
    collisionManager->handlePaddleCollision(ball, playerLeft);
    collisionManager->handlePaddleCollision(ball, playerRight);
}

void PlayState::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    playerLeft.render();
    playerRight.render();
    ball.render();

    std::string leftScore = "P1: " + std::to_string(scoreManager->getPlayerLeftScore());
    std::string rightScore = "P2: " + std::to_string(scoreManager->getPlayerRightScore());

    // FOR DEBUG REASONS ONLY
    // TODO: Remove later
    // int velX, velY;
    // ball.getVelocity(velX, velY);
    // float vel = sqrt(velX ^ 2 + velY ^ 2);
    // float ang = tanf(velY / velX);
    // std::string ballVel = "Vx: " + std::to_string(velX) + " Vy: " + std::to_string(velY) + " V: " + std::to_string(vel) + " Ang: " + std::to_string(ang);
    // textManager->renderText(ballVel, PADDLE_OFFSET, SCREEN_HEIGHT - PADDLE_OFFSET);

    textManager->renderText(leftScore, PADDLE_OFFSET, PADDLE_OFFSET);
    textManager->renderText(rightScore, SCREEN_WIDTH - 109, PADDLE_OFFSET);
    SDL_RenderPresent(Game::renderer);
}
