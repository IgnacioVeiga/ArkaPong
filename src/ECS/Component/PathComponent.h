#pragma once

#include <memory>
#include <functional>
#include <vector>

// Abstract base class for path scripts
class BasePath {
public:
	virtual ~BasePath() = default;
	virtual void UpdatePosition(Vec2& pos, float deltaTime) = 0;
};

// Example of a linear path script
class LinearPath : public BasePath {
public:
	LinearPath(float velocityX, float velocityY) : velocityX(velocityX), velocityY(velocityY) {}
	void UpdatePosition(Vec2& pos, float deltaTime) override {
		pos.x += velocityX * deltaTime;
		pos.y += velocityY * deltaTime;
	}
private:
	float velocityX;
	float velocityY;
};

// Example of a circular path script
class CircularPath : public BasePath {
public:
	CircularPath(float centerX, float centerY, float radius, float speed)
		: centerX(centerX), centerY(centerY), radius(radius), speed(speed), angle(0.0f) {}
	void UpdatePosition(Vec2& pos, float deltaTime) override {
		angle += speed * deltaTime;
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
class LinearInterpolationPath : public BasePath {
public:
	LinearInterpolationPath(float startX, float startY, float endX, float endY, float duration)
		: startX(startX), startY(startY), endX(endX), endY(endY), duration(duration), elapsedTime(0.0f) {}

	void UpdatePosition(Vec2& pos, float deltaTime) override {
		elapsedTime += deltaTime;
		float t = std::min(elapsedTime / duration, 1.0f);
		pos.x = startX + t * (endX - startX);
		pos.y = startY + t * (endY - startY);
	}

private:
	float startX, startY, endX, endY, duration, elapsedTime;
};

class BezierCurvePath : public BasePath {
public:
	BezierCurvePath(std::vector<std::pair<float, float>> controlPoints, float duration)
		: controlPoints(controlPoints), duration(duration), elapsedTime(0.0f) {}

	void UpdatePosition(Vec2& pos, float deltaTime) override {
		elapsedTime += deltaTime;
		float t = std::min(elapsedTime / duration, 1.0f);
		auto point = CalculateBezierPoint(t);
		pos.x = point.first;
		pos.y = point.second;
	}

private:
	std::vector<std::pair<float, float>> controlPoints;
	float duration;
	float elapsedTime;

	std::pair<float, float> CalculateBezierPoint(float t) {
		float x = 0.0f, y = 0.0f;
		int n = controlPoints.size() - 1;
		for (int i = 0; i <= n; ++i) {
			float binomialCoeff = Factorial(n) / (Factorial(i) * Factorial(n - i));
			float powerTerm = std::pow(1 - t, n - i) * std::pow(t, i);
			x += binomialCoeff * powerTerm * controlPoints[i].first;
			y += binomialCoeff * powerTerm * controlPoints[i].second;
		}
		return { x, y };
	}

	int Factorial(int n) {
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
