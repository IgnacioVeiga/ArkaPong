#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

inline const char *GAME_TITLE = "PONG GAME";
inline const int SCREEN_WIDTH = 854;
inline const int SCREEN_HEIGHT = 480;

inline const int AUDIO_FREQUENCY = 44100;

inline const int BALL_SPEED = 8;
inline const int BALL_SIZE = 15;

inline const int PADDLE_SPEED = 5;
inline const int PADDLE_OFFSET = 32;
inline const int PADDLE_WIDTH = 12;
inline const int PADDLE_HEIGHT = 86;

inline const char *BOUNCE_FILEPATH = "assets/sounds/bouce.wav";
inline const char *PAUSE_START_FILEPATH = "assets/sounds/pause_start.wav";
inline const char *SCORE_FILEPATH = "assets/sounds/score.wav";
inline const char *FONT_FILEPATH = "assets/fonts/PressStart2P-vaV7.ttf";

#endif