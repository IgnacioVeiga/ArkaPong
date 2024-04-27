#include "PlayState.h"
#include "PauseState.h"
#include "GameConstants.h"
#include <Game.h>

PlayState::PlayState(GameFlowManager *flowMgr)
    : scoreManager(new ScoreManager()),
      collisionManager(new CollisionManager(scoreManager)),
      playerLeft(
          PADDLE_OFFSET),
      playerRight(
          SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH),
      ball(),
      flowMgr(flowMgr),
      countdown(3),
      countdownTimer(SDL_GetTicks()),
      isCountingDown(true)
{
    audioManager = new AudioManager();
    audioManager->loadSound("round_start", "assets/audio/bgm/round_start.wav");

    textManager = new TextManager();
}

PlayState::~PlayState()
{
    delete audioManager;
    delete textManager;
}

void PlayState::handleInput()
{
    if (isCountingDown)
        return;

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
        flowMgr->changeState(new PauseState());
    }
    else if (keystate[SDL_SCANCODE_ESCAPE])
    {
        // TODO: exit
    }
}

void PlayState::update()
{
    // Eliminar la logica del countdown si no se va a utilizar
    Uint32 currentTime = SDL_GetTicks();
    if (isCountingDown)
    {
        if (currentTime - countdownTimer > 1000)
        {
            countdown--;
            countdownTimer = currentTime;
            if (countdown <= 0)
            {
                isCountingDown = false;
                audioManager->playSound("round_start");
                render();
                SDL_Delay(3000);
            }
        }
        return;
    }

    ball.move();
    collisionManager->handleWallCollisions(ball);
    collisionManager->handlePaddleCollision(ball, playerLeft);
    collisionManager->handlePaddleCollision(ball, playerRight);
}

void PlayState::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    if (isCountingDown)
    {
        textManager->renderText("Stage 1", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100);

        std::string countdownText = "Starting in " + std::to_string(countdown);
        textManager->renderText(countdownText, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    }
    else
    {
        playerLeft.render();
        playerRight.render();
        ball.render();

        std::string leftScore = "P1: " + std::to_string(scoreManager->getPlayerLeftScore());
        std::string rightScore = "P2: " + std::to_string(scoreManager->getPlayerRightScore());

        // FOR DEBUG REASONS ONLY
        // TODO: Remove later
        int velX, velY;
        ball.getVelocity(velX, velY);
        float vel = sqrt(velX ^ 2 + velY ^ 2);
        float ang = tanf(velY / velX);
        std::string ballVel = "Vx: " + std::to_string(velX) + " Vy: " + std::to_string(velY) + " V: " + std::to_string(vel) + " Ang: " + std::to_string(ang);
        textManager->renderText(ballVel, PADDLE_OFFSET, SCREEN_HEIGHT - PADDLE_OFFSET);

        textManager->renderText(leftScore, PADDLE_OFFSET, PADDLE_OFFSET);
        textManager->renderText(rightScore, SCREEN_WIDTH - 109, PADDLE_OFFSET);
    }
    SDL_RenderPresent(Game::renderer);
}
