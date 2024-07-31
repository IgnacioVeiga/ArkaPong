#pragma once

#include <SDL2/SDL_pixels.h>

#pragma region window
inline const char *GAME_TITLE = "ArkaPong";
inline const int SCREEN_WIDTH = 640;
inline const int SCREEN_HEIGHT = 320;
inline const int AUDIO_FREQUENCY = 44100;
#pragma endregion window

#pragma region entities
inline const int BALL_SPEED = 5;
inline const int BALL_SIZE = 5;

inline const int PADDLE_SPEED = 5;
inline const int PADDLE_OFFSET = 32;
inline const int PADDLE_WIDTH = 8;
inline const int PADDLE_HEIGHT = 32;

inline const int BRICK_WIDTH = 8;
inline const int BRICK_HEIGHT = 16;
#pragma endregion entities

#pragma region colors
inline const SDL_Color C_WHITE = {255, 255, 255, 255};
inline const SDL_Color C_BLACK = {0, 0, 0, 255};
inline const SDL_Color C_GRAY = {127, 127, 127, 255};
inline const SDL_Color C_RED = {255, 0, 0, 255};
inline const SDL_Color C_GREEN = {0, 255, 0, 255};
inline const SDL_Color C_BLUE = {0, 0, 255, 255};
#pragma endregion colors

#pragma region assets
inline const char *DOH_OP_BGM_FILEPATH = "assets/audio/bgm/doh_round.wav";
inline const char *ENDING_BGM_FILEPATH = "assets/audio/bgm/ending.wav";
inline const char *GAME_OVER_BGM_FILEPATH = "assets/audio/bgm/game_over.wav";
inline const char *GAME_START_BGM_FILEPATH = "assets/audio/bgm/game_start.wav";
inline const char *ROUND_START_BGM_FILEPATH = "assets/audio/bgm/round_start.wav";

inline const char *HIT_DOH_SFX_FILEPATH = "assets/audio/sfx/ball_hit_doh.wav";
inline const char *HIT_ENEMY_SFX_FILEPATH = "assets/audio/sfx/ball_hit_enemy.wav";
inline const char *HIT_OBS_SFX_FILEPATH = "assets/audio/sfx/ball_hit_obstacle.wav";
inline const char *HIT_SHIELD_SFX_FILEPATH = "assets/audio/sfx/ball_hit_shield.wav";
inline const char *HIT_VAUS_SFX_FILEPATH = "assets/audio/sfx/ball_hit_vaus.wav";
inline const char *DOH_END_SFX_FILEPATH = "assets/audio/sfx/doh_disappears.wav";
inline const char *ESCAPE_SFX_FILEPATH = "assets/audio/sfx/vaus_escape.wav";
inline const char *EXPLOSION_SFX_FILEPATH = "assets/audio/sfx/vaus_explosion.wav";
inline const char *HOLD_SFX_FILEPATH = "assets/audio/sfx/vaus_holds_ball.wav";
inline const char *LIFEUP_SFX_FILEPATH = "assets/audio/sfx/vaus_life_up.wav";
inline const char *LONG_SFX_FILEPATH = "assets/audio/sfx/vaus_longer.wav";
inline const char *SHOT_SFX_FILEPATH = "assets/audio/sfx/vaus_shot.wav";

inline const char *RETRO_FONT_FILEPATH = "assets/fonts/PressStart2P-vaV7.ttf";

inline const char *BGS_SPRITE_FILEPATH = "assets/sprites/backgrounds.bmp";
inline const char *BRICKS_SPRITE_FILEPATH = "assets/sprites/bricks.bmp";
inline const char *DOH_SPRITE_FILEPATH = "assets/sprites/doh.bmp";
inline const char *ENDING_SPRITE_FILEPATH = "assets/sprites/ending.bmp";
inline const char *ENEMIES_SPRITE_FILEPATH = "assets/sprites/enemies.bmp";
inline const char *POWERUPS_SPRITE_FILEPATH = "assets/sprites/powerups.bmp";
inline const char *VAUS_SPRITE_FILEPATH = "assets/sprites/vaus.bmp";
inline const char *WALLS_SPRITE_FILEPATH = "assets/sprites/walls.bmp";
#pragma endregion assets

inline const int CELL_GRID_SIZE = 64;