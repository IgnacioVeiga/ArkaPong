#pragma once

#include <stdexcept>

class Vec2 {
public:
    Vec2()
        : x(0.0f), y(0.0f) {
    }

    Vec2(const float x, const float y)
        : x(x), y(y) {
    }

    Vec2 operator+(Vec2 const &v) const {
        return {
            x + v.x,
            y + v.y
        };
    }

    Vec2 operator+=(Vec2 const &v) {
        x += v.x;
        y += v.y;

        return *this;
    }

    Vec2 operator-(Vec2 const &v) const {
        return {
            x - v.x,
            y - v.y
        };
    }

    Vec2 operator-=(Vec2 const &v) {
        x -= v.x;
        y -= v.y;

        return *this;
    }

    template<typename T>
    Vec2 operator*(T const &n) {
        return Vec2(
            x * n,
            y * n);
    }

    template<typename T>
    Vec2 operator*=(T const &n) {
        x *= n;
        y *= n;

        return *this;
    }

    bool operator==(Vec2 const &v) const {
        return x == v.x && y == v.y;
    }

    float &operator[](const int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::out_of_range("Index out of range");
    }

    const float &operator[](const int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        throw std::out_of_range("Index out of range");
    }

    [[nodiscard]] float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] Vec2 normalize() const {
        const float mag = magnitude();
        if (mag == 0) return Vec2(0.0f, 0.0f);
        return {x / mag, y / mag};
    }

    [[nodiscard]] float dot(Vec2 const &v) const {
        return x * v.x + y * v.y;
    }

    [[nodiscard]] float cross(Vec2 const &v) const {
        return x * v.y - y * v.x;
    }

    [[nodiscard]] Vec2 rotate(float angle) const {
        const float cosA = std::cos(angle);
        const float sinA = std::sin(angle);
        return {
            x * cosA - y * sinA,
            x * sinA + y * cosA
        };
    }

    float x, y;
};
