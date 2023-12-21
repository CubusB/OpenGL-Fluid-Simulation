#pragma once

#include "BasicInclude.hpp"

#include "Shader.hpp"
#include "Circle.hpp"

class Scene
{
public:
    GLFW &glfw;
    Shader &shader;
    std::vector<Circle> &circles;
    Mesh &circleMesh;

    Scene(GLFW &glfw, Shader &shader, std::vector<Circle> &circles, Mesh &mesh)
        : glfw(glfw), shader(shader), circles(circles), circleMesh(mesh)
    {
    }

    // Delete copy operations
    Scene(const Scene &) = delete;
    Scene(const Scene &&) = delete;
    Scene &operator=(const Scene &) = delete;
    Scene operator=(const Scene &&) = delete;
};