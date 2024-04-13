#include "GameState.h"
#include "GameConstants.h"

GameState::GameState(SDL_Renderer *rend) : renderer(rend),
                                           playerLeft(rend, PADDLE_OFFSET, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT),
                                           playerRight(rend, SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT),
                                           ball(rend, SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE),
                                           playerLeftScore(0),
                                           playerRightScore(0)
{
    textManager = new TextManager(renderer);
    audioManager = new AudioManager();
}

GameState::~GameState()
{
    delete textManager;
    delete audioManager;
}

void GameState::handleInput()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        playerLeft.moveUp();
    }
    if (state[SDL_SCANCODE_S])
    {
        playerLeft.moveDown();
    }
    if (state[SDL_SCANCODE_UP])
    {
        playerRight.moveUp();
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        playerRight.moveDown();
    }
}

void GameState::update()
{
    ball.move();
    checkCollision();
    // También necesitarías controlar si la pelota sale de los límites
}

void GameState::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color de fondo negro
    SDL_RenderClear(renderer);

    textManager->renderText(std::to_string(getPlayerLeftScore()), 50, 50);
    textManager->renderText(std::to_string(getPlayerRightScore()), SCREEN_WIDTH - 100, 50);

    // Dibuja todos los objetos del juego
    playerLeft.render();
    playerRight.render();
    ball.render();

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);

    // 60 FPS
    SDL_Delay(1000 / 60);
}

int GameState::getPlayerLeftScore() const
{
    return playerLeftScore;
}

int GameState::getPlayerRightScore() const
{
    return playerRightScore;
}

void GameState::increaseScoreLeft()
{
    playerLeftScore++;
}

void GameState::increaseScoreRight()
{
    playerRightScore++;
}

void GameState::checkCollision()
{
    if (ball.checkCollision(playerLeft.getRect()))
    {
        ball.changeDirection(playerLeft);
        audioManager->playBounceSound();
    }
    if (ball.checkCollision(playerRight.getRect()))
    {
        ball.changeDirection(playerRight);
        audioManager->playBounceSound();
    }
    // Comprueba los límites del campo para modificar los puntajes y resetear la posición de la pelota
    if (ball.getRect().x < 0)
    {
        playerRightScore++;
        resetBall();
        audioManager->playScoreSound();
    }
    else if (ball.getRect().x > SCREEN_WIDTH - BALL_SIZE)
    {
        playerLeftScore++;
        resetBall();
        audioManager->playScoreSound();
    }
}

void GameState::resetBall()
{
    ball.reset((SCREEN_WIDTH - BALL_SIZE) / 2, (SCREEN_HEIGHT - BALL_SIZE) / 2);
    ball.setInitialDirection();
}