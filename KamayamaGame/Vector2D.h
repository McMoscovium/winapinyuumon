#pragma once

#include <cmath>

template <typename T>
class Vector2D {
public:
    Vector2D(T x, T y) :x(x), y(y) {}
    T x;
    T y;
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
    void scalar(T r) {
        x = x * r;
        y = y * r;
    }
};

