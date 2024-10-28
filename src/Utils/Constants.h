#pragma once

#include <SDL2/SDL_pixels.h>

#define GAME_TITLE "ArkaPong"
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 320
#define AUDIO_FREQUENCY 44100

#define BALL_SPEED 2
#define BALL_SIZE 5

#define PADDLE_SPEED 5
#define PADDLE_OFFSET 32
#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 32

#define BRICK_WIDTH 8
#define BRICK_HEIGHT 16

#define C_WHITE {255, 255, 255, 255}
#define C_BLACK {0, 0, 0, 255}
#define C_GRAY {127, 127, 127, 255}
#define C_RED {255, 0, 0, 255}
#define C_GREEN {0, 255, 0, 255}
#define C_BLUE {0, 0, 255, 255}

#define DOH_OP_BGM_FILEPATH "assets/audio/bgm/doh_round.wav"
#define ENDING_BGM_FILEPATH "assets/audio/bgm/ending.wav"
#define GAME_OVER_BGM_FILEPATH "assets/audio/bgm/game_over.wav"
#define GAME_START_BGM_FILEPATH "assets/audio/bgm/game_start.wav"
#define ROUND_START_BGM_FILEPATH "assets/audio/bgm/round_start.wav"

#define HIT_DOH_SFX_FILEPATH "assets/audio/sfx/ball_hit_doh.wav"
#define HIT_ENEMY_SFX_FILEPATH "assets/audio/sfx/ball_hit_enemy.wav"
#define HIT_OBS_SFX_FILEPATH "assets/audio/sfx/ball_hit_obstacle.wav"
#define HIT_SHIELD_SFX_FILEPATH "assets/audio/sfx/ball_hit_shield.wav"
#define HIT_VAUS_SFX_FILEPATH "assets/audio/sfx/ball_hit_vaus.wav"
#define DOH_END_SFX_FILEPATH "assets/audio/sfx/doh_disappears.wav"
#define ESCAPE_SFX_FILEPATH "assets/audio/sfx/vaus_escape.wav"
#define EXPLOSION_SFX_FILEPATH "assets/audio/sfx/vaus_explosion.wav"
#define HOLD_SFX_FILEPATH "assets/audio/sfx/vaus_holds_ball.wav"
#define LIFE_UP_SFX_FILEPATH "assets/audio/sfx/vaus_life_up.wav"
#define LONG_SFX_FILEPATH "assets/audio/sfx/vaus_longer.wav"
#define SHOT_SFX_FILEPATH "assets/audio/sfx/vaus_shot.wav"

#define RETRO_FONT_FILEPATH "assets/fonts/PressStart2P-vaV7.ttf"

#define BGS_SPRITE_FILEPATH "assets/sprites/backgrounds.bmp"
#define BRICKS_SPRITE_FILEPATH "assets/sprites/bricks.bmp"
#define DOH_SPRITE_FILEPATH "assets/sprites/doh.bmp"
#define ENDING_SPRITE_FILEPATH "assets/sprites/ending.bmp"
#define ENEMIES_SPRITE_FILEPATH "assets/sprites/enemies.bmp"
#define POWER_UPS_SPRITE_FILEPATH "assets/sprites/powerups.bmp"
#define VAUS_SPRITE_FILEPATH "assets/sprites/vaus.bmp"
#define WALLS_SPRITE_FILEPATH "assets/sprites/walls.bmp"

#define CELL_GRID_SIZE 64

#define DEBOUNCE_TIME 5 // In milliseconds.