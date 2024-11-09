#pragma once

#include <cmath>

class Vector2D {
public:
    Vector2D(float x, float y) :x(x), y(y) {}
    float x;
    float y;
    float norm()const {
        return std::sqrt(x * x + y * y);
    }
    void normalize() {
        if (norm() == 0) {
            return;
        }
        float r = norm();
        x = x / r;
        y = y / r;
    }
    void scalar(float r) {
        x = r * x;
        y = r * y;
    }
};