#pragma once
#include <vector>
#include "../Math/Ray.h"
#include "Sphere.h"
#include <iostream>

struct Scene {
    std::vector<Spheref> objects;

    void add(const Spheref& sphere) {
        objects.push_back(sphere);
    }

    // Находит ближайшее пересечение среди всех объектов
    bool intersect(const Rayf& ray, float& t, const Spheref*& hit) const {
        t = 1e9f; // очень большое число
        hit = nullptr;

        for (const auto& sphere : objects) {
            float temp;
            if (sphere.intersect(ray, temp) && temp < t) {
                t = temp;
                hit = &sphere;
            }
        }
        return hit != nullptr;
    }

    void render(int width = 80, int height = 40) const {
    Vec3f lightDir = Vec3f(-1, 1, 1).normalize();
    const char* shading = " .:;+*#@";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float u = (float(x) / width)  * 2.0f - 1.0f;
            float v = ((float(y) / height) * 2.0f - 1.0f) * 0.5f;

            Rayf ray(Vec3f(0,0,0), Vec3f(u, -v, -1));

            float t;
            const Spheref* hit;
            if (intersect(ray, t, hit)) {
                Vec3f point  = ray.at(t);
                Vec3f normal = (point - hit->center).normalize();
                float brightness = normal.dot(lightDir);
                if (brightness < 0) brightness = 0;
                std::cout << shading[int(brightness * 7)];
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}
};