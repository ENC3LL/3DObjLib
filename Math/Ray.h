#pragma once
#include "Vec3.h"

template<typename T>
struct Ray {
    Vec3<T> origin;     // откуда идёт луч
    Vec3<T> direction;  // куда идёт

    Ray(Vec3<T> origin, Vec3<T> direction)
        : origin(origin), direction(direction.normalize()) {}

    // Точка на луче на расстоянии t
    // origin + direction * t
    Vec3<T> at(T t) const {
        return origin + direction * t;
    }
};



using Rayf = Ray<float>;