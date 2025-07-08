#pragma once

#include "Core/Utils/Vec2.h"

// Abstract base class for path scripts
class BasePath {
public:
    virtual ~BasePath() = default;

    virtual void UpdatePosition(Vec2 &pos, float delta_time) = 0;
};

// Example of a linear path script
class LinearPath final : public BasePath {
public:
    LinearPath(const float velocityX, const float velocityY) : velocityX(velocityX), velocityY(velocityY) {
    }

    void UpdatePosition(Vec2 &pos, const float delta_time) override {
        pos.x += velocityX * delta_time;
        pos.y += velocityY * delta_time;
    }

private:
    float velocityX;
    float velocityY;
};

// Example of a circular path script
class CircularPath final : public BasePath {
public:
    CircularPath(const float centerX, const float centerY, const float radius, const float speed)
        : centerX(centerX), centerY(centerY), radius(radius), speed(speed), angle(0.0f) {
    }

    void UpdatePosition(Vec2 &pos, const float delta_time) override {
        angle += speed * delta_time;
        pos.x = centerX + radius * cos(angle);
        pos.y = centerY + radius * sin(angle);
    }

private:
    float centerX;
    float centerY;
    float radius;
    float speed;
    float angle;
};

// Other path scripts...
class LinearInterpolationPath final : public BasePath {
public:
    LinearInterpolationPath(const float startX, const float startY, const float endX, const float endY,
                            const float duration)
        : startX(startX), startY(startY), endX(endX), endY(endY), duration(duration), elapsedTime(0.0f) {
    }

    void UpdatePosition(Vec2 &pos, const float delta_time) override {
        elapsedTime += delta_time;
        const float t = std::min(elapsedTime / duration, 1.0f);
        pos.x = startX + t * (endX - startX);
        pos.y = startY + t * (endY - startY);
    }

private:
    float startX, startY, endX, endY, duration, elapsedTime;
};

class BezierCurvePath final : public BasePath {
public:
    BezierCurvePath(const std::vector<std::pair<float, float> > &controlPoints, const float duration)
        : controlPoints(controlPoints), duration(duration), elapsedTime(0.0f) {
    }

    void UpdatePosition(Vec2 &pos, const float delta_time) override {
        elapsedTime += delta_time;
        const float t = std::min(elapsedTime / duration, 1.0f);
        const auto point = CalculateBezierPoint(t);
        pos.x = point.first;
        pos.y = point.second;
    }

private:
    std::vector<std::pair<float, float> > controlPoints;
    float duration;
    float elapsedTime;

    std::pair<float, float> CalculateBezierPoint(float t) {
        float x = 0.0f, y = 0.0f;
        const int n = controlPoints.size() - 1;
        for (int i = 0; i <= n; ++i) {
            const float binomial_coeff = static_cast<float>(Factorial(n) / (Factorial(i) * Factorial(n - i)));
            const float powerTerm = static_cast<float>(std::pow(1 - t, n - i) * std::pow(t, i));

            x += binomial_coeff * powerTerm * controlPoints[i].first;
            y += binomial_coeff * powerTerm * controlPoints[i].second;
        }
        return {x, y};
    }

    int Factorial(const int n) {
        return (n == 0 || n == 1) ? 1 : n * Factorial(n - 1);
    }
};

// Structure to define a motion event that follows a trajectory
struct PathEvent {
    Vec2 trigger;

    // Action to execute when event triggers
    std::function<void(Entity)> action;
};

struct PathComponent {
    // Movement script to execute
    std::shared_ptr<BasePath> path;

    // List of movement events
    std::vector<PathEvent> events;
};
