#pragma once
#include <cstdint>

struct Color {
    float r, g, b;  // значения от 0.0 до 1.0

    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    Color() : r(0), g(0), b(0) {}
};

struct Material {
    Color albedo;       // цвет поверхности
    float metallic;     // 0.0 = не металл, 1.0 = металл
    float roughness;    // 0.0 = зеркало, 1.0 = матовый

    Material() : metallic(0.0f), roughness(1.0f) {}
};