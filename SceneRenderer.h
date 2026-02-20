#pragma once
#include "3DObjLib.h"
#include <SFML/Graphics.hpp>
#include <functional>

class SceneRenderer {
    int width, height;
    Scene scene;
    Vec3f lightDir;
    sf::RenderWindow window;

public:
    SceneRenderer(int w = 800, int h = 600)
        : width(w), height(h)
        , lightDir(Vec3f(-1, 1, 1).normalize())
        , window(sf::VideoMode({(unsigned)w, (unsigned)h}), "3DObjLib") {}

    // Добавление сферы через лямбду
    SceneRenderer& add(Spheref sphere) {
        scene.add(sphere);
        return *this;
    }

    void run() {
        sf::Image image({(unsigned)width, (unsigned)height}, sf::Color::Black);
        renderToImage(image);

        sf::Texture texture(image);
        sf::Sprite sprite(texture);

        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent())
                if (event->is<sf::Event::Closed>())
                    window.close();

            window.clear();
            window.draw(sprite);
            window.display();
        }
    }

private:
    void renderToImage(sf::Image& image) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float u = (float(x) / width)  * 2.0f - 1.0f;
                float v = ((float(y) / height) * 2.0f - 1.0f) * 0.75f;

                Rayf ray(Vec3f(0,0,0), Vec3f(u, -v, -1));
                auto color = trace(ray, 0);

                image.setPixel({(unsigned)x, (unsigned)y}, sf::Color(
                    (uint8_t)(color.r * 255),
                    (uint8_t)(color.g * 255),
                    (uint8_t)(color.b * 255)
                ));
            }
        }
    }

    Color trace(const Rayf& ray, int depth) {
        if (depth > 3) return Color(0, 0, 0);

        float t;
        const Spheref* hit = nullptr;
        if (!scene.intersect(ray, t, hit))
            return Color(0.1f, 0.1f, 0.1f); // фон

        Vec3f point  = ray.at(t);
        Vec3f normal = (point - hit->center).normalize();
        float brightness = normal.dot(lightDir);
        if (brightness < 0) brightness = 0;

        auto& m = hit->material;

        // Отражение для металлических объектов
        if (m.metallic > 0.0f) {
            Vec3f reflected = reflect(ray.direction, normal);
            Rayf reflectedRay(point + normal * 0.001f, reflected);
            Color reflectedColor = trace(reflectedRay, depth + 1);

            // Смешиваем цвет объекта и отражение
            float m_ = m.metallic;
            return Color(
                m.albedo.r * brightness * (1 - m_) + reflectedColor.r * m_,
                m.albedo.g * brightness * (1 - m_) + reflectedColor.g * m_,
                m.albedo.b * brightness * (1 - m_) + reflectedColor.b * m_
            );
        }

        return Color(
            m.albedo.r * brightness,
            m.albedo.g * brightness,
            m.albedo.b * brightness
        );
    }

    Vec3f reflect(const Vec3f& dir, const Vec3f& normal) {
        return dir - normal * 2.0f * dir.dot(normal);
    }
};