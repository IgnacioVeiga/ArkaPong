#pragma once

struct AnimationComponent {
    int currentFrame;
    int frameCount;
    int frameWidth;
    int frameHeight;
    int animationSpeed; // Time in milliseconds per frame
    int elapsedTime;
    bool loop;
    bool isPlaying;
};
