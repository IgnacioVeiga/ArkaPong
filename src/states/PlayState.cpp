#include "PlayState.h"
#include "PauseState.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"
#include "../managers/TextureManager.h"

PlayState::PlayState()
	: playerLeft(PlayerSide::PLAYER_LEFT),
	  playerRight(PlayerSide::PLAYER_RIGHT)
{
	scoreManager = new ScoreManager();
	collisionManager = new CollisionManager();

	audioManager = new AudioManager();
	audioManager->loadSound("round_start", "assets/audio/bgm/round_start.wav");

	textManager = new TextManager();

	TextureManager::loadTexture("vaus", "assets/sprites/vaus.bmp");
	TextureManager::loadTexture("blocks_and_bg", "assets/sprites/blocks_backgrounds.bmp");

	// Showing round number
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Game::renderer);
	textManager->renderText("Round 1", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TextAlignment::CENTER);
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

	if (collisionManager->CheckWallCollisions(ball))
		return;
	if (collisionManager->CheckPaddleCollision(playerLeft, ball))
		return;
	if (collisionManager->CheckPaddleCollision(playerRight, ball))
		return;

	switch (collisionManager->CheckBallOutOfBounds(ball))
	{
	case CollisionSide::LEFT:
	{
		scoreManager->increaseScore(PlayerSide::PLAYER_RIGHT);
		// TODO: do destroy animation of player left
		break;
	}
	case CollisionSide::RIGHT:
	{
		scoreManager->increaseScore(PlayerSide::PLAYER_LEFT);
		// TODO: do destroy animation of player right
		break;
	}
	default:
		return;
	}

	ball.center();
	playerLeft.center();
	playerRight.center();
	render();
	SDL_Delay(1000);
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

	SDL_Rect wall = { 72, 32, 8, 8 };
	int i = 0;
	while (i < SCREEN_WIDTH)
	{
		TextureManager::drawTexture("blocks_and_bg", i, 0, &wall);
		TextureManager::drawTexture("blocks_and_bg", i, SCREEN_HEIGHT - (8 * SCALE), &wall);
		i += 8 * SCALE;
	}

	textManager->renderText(
		leftScore,			// Text
		PADDLE_OFFSET,		// X
		PADDLE_OFFSET,		// Y
		{6, 186, 221, 255}, // Blue
		TextAlignment::LEFT);
	textManager->renderText(
		rightScore,					  // Text
		SCREEN_WIDTH - PADDLE_OFFSET, // X
		PADDLE_OFFSET,				  // Y
		{245, 110, 100, 255},		  // Red
		TextAlignment::RIGHT);
	SDL_RenderPresent(Game::renderer);
}
