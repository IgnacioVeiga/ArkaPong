#include "Core/Component/PathComponent.h"
#include "Core/Utils/Vec2.h"

void LinearPath::UpdatePosition(Vec2& pos, const float delta_time)
{
    pos.x += velocityX * delta_time;
    pos.y += velocityY * delta_time;
}

void CircularPath::UpdatePosition(Vec2& pos, const float delta_time)
{
    angle += speed * delta_time;
    pos.x = centerX + radius * cos(angle);
    pos.y = centerY + radius * sin(angle);
}

void LinearInterpolationPath::UpdatePosition(Vec2& pos, const float delta_time)
{
    elapsedTime += delta_time;
    const float t = std::min(elapsedTime / duration, 1.0f);
    pos.x = startX + t * (endX - startX);
    pos.y = startY + t * (endY - startY);
}

void BezierCurvePath::UpdatePosition(Vec2& pos, const float delta_time)
{
    elapsedTime += delta_time;
    const float t = std::min(elapsedTime / duration, 1.0f);
    const auto [x, y] = CalculateBezierPoint(t);
    pos.x = x;
    pos.y = y;
}
