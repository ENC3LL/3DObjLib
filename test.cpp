#include <3DObjLib.h>
#include <SceneRenderer.h>

int main() {
    SceneRenderer renderer;

    renderer
        .add(SphereBuilder::create(1.5f)
            .position(0, 0, -4)
            .color(1, 0, 0)
            .metallic(0.0f)
            .build())
        .add(SphereBuilder::create(1.0f)
            .position(2.5f, 0, -5)
            .color(0.8f, 0.8f, 0.8f)
            .metallic(1.0f)
            .build())
        .add(SphereBuilder::create(1.0f)
            .position(-2.5f, 0, -5)
            .color(0, 0.5f, 1)
            .metallic(0.5f)
            .build())
        .run();
}