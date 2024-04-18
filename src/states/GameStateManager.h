#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include "Ball.h"
#include "TextManager.h"
#include "AudioManager.h"

enum class GameStatus
{
    START_MENU,
    START_COUNTDOWN,
    PLAYING,
    PAUSED
};

class GameStateManager
{
public:
    GameStateManager(SDL_Renderer *renderer);
    ~GameStateManager();

    void handleInput();
    void update();
    void render(SDL_Renderer *renderer);

    int getPlayerLeftScore() const;
    int getPlayerRightScore() const;

    void increaseScoreLeft();
    void increaseScoreRight();

private:
    SDL_Renderer *renderer;
    GameStatus status;

    Paddle playerLeft;
    Paddle playerRight;
    Ball ball;

    TextManager *textManager;
    AudioManager *audioManager;

    int playerLeftScore;
    int playerRightScore;

    Uint32 countdownStart; // Tiempo en milisegundos cuando inicia el countdown
    int countdown;         // Valor actual del countdown en segundos
    void startCountdown();

    void checkCollision();
    void resetBall();
};

#endif
