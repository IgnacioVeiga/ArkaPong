#pragma once

#include <memory>
#include <functional>

// Abstract base class for movement scripts
class BaseMovementScript {
public:
	virtual ~BaseMovementScript() = default;
	// Pure virtual function to update the position of the entity
	virtual void UpdatePosition(float& x, float& y, float deltaTime) = 0;
};

// Example of a linear movement script
class LinearMovementScript : public BaseMovementScript {
public:
	LinearMovementScript(float velocityX, float velocityY)
		: velocityX(velocityX), velocityY(velocityY) {}

	// Override to update the position linearly
	void UpdatePosition(float& x, float& y, float deltaTime) override {
		x += velocityX * deltaTime;
		y += velocityY * deltaTime;
	}
private:
	float velocityX;
	float velocityY;
};

// Example of a circular movement script
class CircularMovementScript : public BaseMovementScript {
public:
	CircularMovementScript(float centerX, float centerY, float radius, float speed)
		: centerX(centerX), centerY(centerY), radius(radius), speed(speed), angle(0.0f) {}

	// Override to update the position in a circular path
	void UpdatePosition(float& x, float& y, float deltaTime) override {
		angle += speed * deltaTime;
		x = centerX + radius * cos(angle);
		y = centerY + radius * sin(angle);
	}
private:
	float centerX;
	float centerY;
	float radius;
	float speed;
	float angle;
};

// Example of a linear interpolation script
class LinearInterpolationScript : public BaseMovementScript
{
public:
	LinearInterpolationScript(float startX, float startY, float endX, float endY, float duration)
		: startX(startX), startY(startY), endX(endX), endY(endY), duration(duration), elapsedTime(0.0f) {}

	// Override to update the position using linear interpolation
	void UpdatePosition(float& x, float& y, float deltaTime) override
	{
		elapsedTime += deltaTime;
		float t = std::min(elapsedTime / duration, 1.0f);
		x = startX + t * (endX - startX);
		y = startY + t * (endY - startY);
	}

private:
	float startX, startY, endX, endY, duration, elapsedTime;
};

// Example of a Bezier curve movement script
class BezierCurveScript : public BaseMovementScript
{
public:
	BezierCurveScript(std::vector<std::pair<float, float>> controlPoints, float duration)
		: controlPoints(controlPoints), duration(duration), elapsedTime(0.0f) {}

	// Override to update the position using a Bezier curve
	void UpdatePosition(float& x, float& y, float deltaTime) override
	{
		elapsedTime += deltaTime;
		float t = std::min(elapsedTime / duration, 1.0f);
		auto point = CalculateBezierPoint(t);
		x = point.first;
		y = point.second;
	}

private:
	std::vector<std::pair<float, float>> controlPoints;
	float duration;
	float elapsedTime;

	// Calculate a point on the Bezier curve for a given t
	std::pair<float, float> CalculateBezierPoint(float t)
	{
		float x = 0.0f, y = 0.0f;
		int n = controlPoints.size() - 1;
		for (int i = 0; i <= n; ++i)
		{
			float binomialCoeff = Factorial(n) / (Factorial(i) * Factorial(n - i));
			float powerTerm = std::pow(1 - t, n - i) * std::pow(t, i);
			x += binomialCoeff * powerTerm * controlPoints[i].first;
			y += binomialCoeff * powerTerm * controlPoints[i].second;
		}
		return { x, y };
	}

	// Helper function to calculate factorial
	int Factorial(int n)
	{
		return (n == 0 || n == 1) ? 1 : n * Factorial(n - 1);
	}
};

// Struct to define a movement event
struct MovementEvent
{
	float triggerX;
	float triggerY;
	std::function<void(Entity)> action; // Action to execute when event triggers
};

// Component to hold the movement script and events for an entity
struct MovementScriptComponent {
	std::shared_ptr<BaseMovementScript> script; // Movement script to execute
	std::vector<MovementEvent> events; // List of movement events
};
