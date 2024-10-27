#pragma once

class Vec2
{
public:
    Vec2()
        : x(0.0f), y(0.0f)
    {
    }

    Vec2(float x, float y)
        : x(x), y(y)
    {
    }

    Vec2 operator+(Vec2 const &v)
    {
        return Vec2(
            x + v.x,
            y + v.y);
    }

    Vec2 operator+=(Vec2 const &v)
    {
        x += v.x;
        y += v.y;

        return *this;
    }

    Vec2 operator-(Vec2 const &v)
    {
        return Vec2(
            x - v.x,
            y - v.y);
    }

    Vec2 operator-=(Vec2 const &v)
    {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    template <typename T>
    Vec2 operator*(T const& n)
    {
        return Vec2(
            x * n,
            y * n);
    }

    template <typename T>
    Vec2 operator*=(T const& n)
    {
        x *= n;
        y *= n;

        return *this;
    }

    bool operator==(Vec2 const& v) const
    {
        return x == v.x && y == v.y;
    }

    float& operator[](int index)
    {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::out_of_range("Index out of range");
    }

    const float& operator[](int index) const
    {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::out_of_range("Index out of range");
    }

    float magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalize() const
    {
        float mag = magnitude();
        return Vec2(x / mag, y / mag);
    }

    float dot(Vec2 const& v) const
    {
        return x * v.x + y * v.y;
    }

    float cross(Vec2 const& v) const
    {
        return x * v.y - y * v.x;
    }

    Vec2 rotate(float angle) const
    {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return Vec2(
            x * cosA - y * sinA,
            x * sinA + y * cosA
        );
    }

    float x, y;
};
