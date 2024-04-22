#include "PlayState.h"
#include "PauseState.h"
#include "GameConstants.h"

PlayState::PlayState(SDL_Renderer *rend, GameFlowManager *flowMgr)
    : renderer(rend),
      scoreManager(new ScoreManager()),
      collisionManager(new CollisionManager(scoreManager)),
      playerLeft(
          rend,
          PADDLE_OFFSET),
      playerRight(
          rend,
          SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH),
      ball(rend),
      flowMgr(flowMgr),
      countdown(3),
      countdownTimer(SDL_GetTicks()),
      isCountingDown(true)
{
    audioManager = new AudioManager();
    audioManager->loadSound("round_start", "assets/audio/bgm/round_start.wav");

    textManager = new TextManager(renderer);
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
        flowMgr->changeState(new PauseState(renderer));
    }
    else if (keystate[SDL_SCANCODE_ESCAPE])
    {
        // TODO: exit
    }
}

void PlayState::update()
{
    Uint32 currentTime = SDL_GetTicks();
    if (isCountingDown)
    {
        if (currentTime - countdownTimer > 1000)
        { // cada segundo
            countdown--;
            countdownTimer = currentTime;
            if (countdown <= 0)
            {
                isCountingDown = false;
                audioManager->playSound("round_start");
                render(renderer);
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

void PlayState::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (isCountingDown)
    {
        textManager->renderText("Stage 1", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100);

        std::string countdownText = "Starting in " + std::to_string(countdown);
        textManager->renderText(countdownText, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    }
    else
    {
        playerLeft.render(renderer);
        playerRight.render(renderer);
        ball.render(renderer);
        std::string leftScore = "P1: " + std::to_string(scoreManager->getPlayerLeftScore());
        std::string rightScore = "P2: " + std::to_string(scoreManager->getPlayerRightScore());
        textManager->renderText(leftScore, 50, 50);                  // Posición puede ajustarse según necesidad
        textManager->renderText(rightScore, SCREEN_WIDTH - 150, 50); // Ajusta la posición según sea necesario
    }
    SDL_RenderPresent(renderer);
}
