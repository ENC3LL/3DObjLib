#pragma once
#include <cmath>
#include <concepts>

template<typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

template<Arithmetic T>
struct Vec3 {
    T x, y, z;

    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec3() : x(0), y(0), z(0) {}

    Vec3 operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(T scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    T dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    T length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    Vec3 normalize() const {
        T len = length();
        return Vec3(x/len, y/len, z/len);
    }
};

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;
using Vec3i = Vec3<int>;