#pragma once
#include "Sphere.h"

class SphereBuilder {
    Spheref sphere;

public:
    // Точка входа — создаём с радиусом
    static SphereBuilder create(float radius) {
        SphereBuilder builder;
        builder.sphere = Spheref(Vec3f(0,0,0), radius);
        return builder;
    }

    // Позиция
    SphereBuilder& position(float x, float y, float z) {
        sphere.center = Vec3f(x, y, z);
        return *this;
    }

    // Цвет
    SphereBuilder& color(float r, float g, float b) {
        sphere.material.albedo = Color(r, g, b);
        return *this;
    }

    // Металличность
    SphereBuilder& metallic(float value) {
        sphere.material.metallic = value;
        return *this;
    }

    // Шероховатость
    SphereBuilder& roughness(float value) {
        sphere.material.roughness = value;
        return *this;
    }

    // Финальная сборка
    Spheref build() {
        return sphere;
    }
};