# 3DObjLib

> ⚠️ **This project is in early demo stage.** API may change, features are limited, and it is not production-ready. Contributions and feedback are welcome.

A lightweight, header-only C++20 ray tracing library for creating and rendering 3D scenes. Built from scratch using modern C++ templates, concepts, and a clean fluent API — no engine required.

---

## ✨ Features

- Header-only — just include and use
- Ray-sphere intersection
- Diffuse lighting and surface normals
- Metallic reflections
- Fluent builder API for scene objects
- SFML-powered render window

---

## 📋 Requirements

- C++20 compiler (clang++ or MSVC)
- [SFML 3.x](https://www.sfml-dev.org/) (via [vcpkg](https://github.com/microsoft/vcpkg))

---

## 🚀 Quick Start

### 1. Install SFML via vcpkg

```bash
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg install sfml
```

### 2. Clone 3DObjLib

```bash
git clone https://github.com/ENC3LL/3DObjLib.git
```

### 3. Add to your compiler flags

```
-std=c++20
-I<path_to_3DObjLib>
-I<path_to_vcpkg>/installed/x64-windows/include
-L<path_to_vcpkg>/installed/x64-windows/lib
-lsfml-graphics -lsfml-window -lsfml-system
```

---

## 📖 Usage

```cpp
#include "SceneRenderer.h"

int main() {
    SceneRenderer renderer;

    renderer
        // Red matte sphere in the center
        .add(SphereBuilder::create(1.5f)
            .position(0.0f, 0.0f, -4.0f)
            .color(1.0f, 0.0f, 0.0f)
            .metallic(0.0f)
            .build())

        // Silver metallic sphere on the right — reflects the scene
        .add(SphereBuilder::create(1.0f)
            .position(2.5f, 0.0f, -5.0f)
            .color(0.8f, 0.8f, 0.8f)
            .metallic(1.0f)
            .build())

        // Blue semi-metallic sphere on the left
        .add(SphereBuilder::create(1.0f)
            .position(-2.5f, 0.0f, -5.0f)
            .color(0.0f, 0.5f, 1.0f)
            .metallic(0.5f)
            .build())

        .run(); // Opens window and renders
}
```

---

## 🗂️ Project Structure

```
3DObjLib/
├── 3DObjLib.h          ← Main include (pulls everything in)
├── SceneRenderer.h     ← Window + render loop
├── Math/
│   ├── Vec3.h          ← 3D vector math
│   └── Ray.h           ← Ray (origin + direction)
├── Scene/
│   ├── Sphere.h        ← Sphere geometry + ray intersection
│   ├── Scene.h         ← Scene (list of objects + intersect)
│   └── SphereBuilder.h ← Fluent builder API
└── Material/
    └── Material.h      ← Color, metallic, roughness
```

---

## 🔧 SphereBuilder API

| Method | Description |
|---|---|
| `SphereBuilder::create(radius)` | Start building a sphere with given radius |
| `.position(x, y, z)` | Set world position |
| `.color(r, g, b)` | Set albedo color (0.0 – 1.0) |
| `.metallic(value)` | Set metallic intensity (0.0 = matte, 1.0 = mirror) |
| `.roughness(value)` | Set surface roughness (not yet used in shading) |
| `.build()` | Returns the final `Spheref` object |

---

## 🗺️ Roadmap

- [ ] Plane and cube primitives
- [ ] Shadow casting between objects
- [ ] Roughness-based reflection blur
- [ ] Camera controls
- [ ] Physics simulation layer

---

## 📄 License

MIT — free to use, modify, and distribute.
