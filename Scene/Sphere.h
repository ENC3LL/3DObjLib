#pragma once
#include "../Math/Vec3.h"
#include "../Material/Material.h"

template<typename T>
struct Sphere {
    Vec3<T> center;   // центр сферы
    T radius;         // радиус
    Material material; // материал

    Sphere() : center(Vec3f(0,0,0)), radius(1.0f) {}

    Sphere(Vec3<T> center, T radius)
        : center(center), radius(radius) {}

    
        bool intersect(const Ray<T>& ray, T& t) const {
    Vec3<T> oc = ray.origin - center;
    
    T a = ray.direction.dot(ray.direction);
    T b = oc.dot(ray.direction) * 2.0f;
    T c = oc.dot(oc) - radius * radius;
    
    T discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) return false;
    
    t = (-b - std::sqrt(discriminant)) / (2.0f * a);
    return true;
    }
};

using Spheref = Sphere<float>;