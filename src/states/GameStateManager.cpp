#include "GameStateManager.h"
#include "GameConstants.h"

GameStateManager::GameStateManager(SDL_Renderer *rend) : renderer(rend),
                                                         playerLeft(rend, PADDLE_OFFSET, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT),
                                                         playerRight(rend, SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT),
                                                         ball(rend, SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE),
                                                         playerLeftScore(0),
                                                         playerRightScore(0),
                                                         status(GameStatus::START_MENU),
                                                         countdown(3)
{
    textManager = new TextManager(renderer);
    audioManager = new AudioManager();
}

GameStateManager::~GameStateManager()
{
    delete textManager;
    delete audioManager;
}

void GameStateManager::handleInput()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (status == GameStatus::START_MENU && state[SDL_SCANCODE_SPACE])
    {
        audioManager->playPauseStartSound();
        status = GameStatus::START_COUNTDOWN;
        startCountdown();
    }
    else if (status == GameStatus::PAUSED && state[SDL_SCANCODE_P])
    {
        status = GameStatus::PLAYING;
        audioManager->playPauseStartSound();
    }
    else if (status == GameStatus::PLAYING && state[SDL_SCANCODE_P])
    {
        status = GameStatus::PAUSED;
        audioManager->playPauseStartSound();
    }

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

void GameStateManager::update()
{
    if (status == GameStatus::START_COUNTDOWN)
    {
        Uint32 now = SDL_GetTicks();
        Uint32 elapsed = now - countdownStart;

        if (elapsed >= 1000)
        {                         // Ha pasado 1 segundo
            countdown--;          // Reduce el contador por un segundo
            countdownStart = now; // Reinicia el tiempo de referencia

            if (countdown <= 0)
            {
                status = GameStatus::PLAYING; // Cambia el estado a jugar
            }
        }
    }
    else if (status == GameStatus::PLAYING)
    {
        // Lógica del juego
        ball.move();
        checkCollision();
    }
}

void GameStateManager::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
    SDL_RenderClear(renderer);

    if (status == GameStatus::START_MENU)
    {
        textManager->renderText("Push SPACE to start", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    else if (status == GameStatus::START_COUNTDOWN)
    {
        std::string countdownText = "Starting: " + std::to_string(countdown);
        textManager->renderText(countdownText, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    else if (status == GameStatus::PAUSED)
    {
        textManager->renderText("Game Paused [P to continue]", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    else if (status == GameStatus::PLAYING)
    {
        textManager->renderText(std::to_string(getPlayerLeftScore()), 50, 50);
        textManager->renderText(std::to_string(getPlayerRightScore()), SCREEN_WIDTH - 100, 50);

        // Dibuja todos los objetos del juego
        playerLeft.render();
        playerRight.render();
        ball.render();
    }

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);

    // 60 FPS
    SDL_Delay(1000 / 60);
}

void GameStateManager::startCountdown()
{
    countdown = 3;                   // Comienza el contador en 3 segundos
    countdownStart = SDL_GetTicks(); // Guarda el tiempo actual
}

int GameStateManager::getPlayerLeftScore() const
{
    return playerLeftScore;
}

int GameStateManager::getPlayerRightScore() const
{
    return playerRightScore;
}

void GameStateManager::increaseScoreLeft()
{
    playerLeftScore++;
}

void GameStateManager::increaseScoreRight()
{
    playerRightScore++;
}

void GameStateManager::checkCollision()
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

void GameStateManager::resetBall()
{
    ball.reset((SCREEN_WIDTH - BALL_SIZE) / 2, (SCREEN_HEIGHT - BALL_SIZE) / 2);
    ball.setInitialDirection();
}