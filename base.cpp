#include "src/BasicInclude.hpp"
#include "src/GLFW.hpp"
#include "src/Time.hpp"
#include "src/Shader.hpp"
#include "src/Mesh.hpp"
#include "src/Scene.hpp"

#include <cmath>

void sceneUpdate(float dt, std::vector<Circle> &circles)
{
    for (Circle &circle : circles)
    {
        circle.x += rand() % 3 - 1;
        circle.y += rand() % 3 - 1;
    }
}

GLint getUniformIndex(Shader &shader, const std::string &uniformName)
{
    GLint uniformLocation = glGetUniformLocation(shader.getShaderID(), uniformName.c_str());
    if (uniformLocation < 0)
    {
        std::cerr << "[Shader] Couldn't set value for uniform " << uniformName << std::endl;
        std::cerr.flush();
        throw std::runtime_error("[Shader] Couldn't set value for uniform " + uniformName);
    }
    return uniformLocation;
}

void setShaderUniform(Shader &shader, const std::string &uniformName, const Vector3D &color)
{
    GLint uniformLocation = getUniformIndex(shader, uniformName);
    glUniform3f(uniformLocation, color.x, color.y, color.z);
}

void render(Scene &scene)
{
    Shader &circleShader = scene.shader;
    glUseProgram(circleShader.getShaderID());
    glBindVertexArray(scene.circleMesh.vao);

    for (Circle &circle : scene.circles)
    {
        // setShaderUniform(scene.shader, "uMaterial.diffuse", circle.color);
        setShaderUniform(scene.shader, "spherePos", Vector3D(circle.x, circle.y, 0));

        glDrawElements(GL_TRIANGLES, scene.circleMesh.vboSize, GL_UNSIGNED_INT, nullptr);
    }
    glBindVertexArray(0);
    glUseProgram(0);
}

void sceneDraw(Scene &shader)
{
    glClearColor(0.2, 0.2, 0.2, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render(shader);

    glBindVertexArray(0);
    glUseProgram(0);
}

void addCircles(std::vector<Circle> &circles, int count)
{
    uint8_t rangeX = 10;
    uint8_t rangeY = 10;
    for (int i = 0; i < count; i++)
    {
        circles.push_back(Circle(
            (rand() % rangeX) - rangeX / 2,
            (rand() % rangeY) - rangeY / 2,
            1));
    }
}

Mesh createCircleMesh()
{
    constexpr uint16_t numSegments = 32;
    constexpr float angleStep = 2 * M_PI / numSegments;
    constexpr float radius = 10;
    std::vector<Vertex> vertices(numSegments);
    std::vector<GLuint64> indices(numSegments);
    for (uint32_t i = 0; i < vertices.size(); i++)
    {
        vertices[i].pos = Vector3D(cos(angleStep * i), sin(angleStep * i), 0) * radius;
        indices[i] = i;
    }
    return Mesh(vertices, indices);
}

int main()
{
    // Init
    GLFW_Window window("My Window");
    GLFW glfw(std::move(window));
    Shader circleShader("src/shaders/shader.vert", "src/shaders/color.frag");
    std::vector<Circle> circles;
    Mesh mesh = createCircleMesh();
    Scene scene{
        glfw,
        circleShader,
        circles,
        mesh};

    addCircles(circles, 100);

    Time time;
    // Run
    while (!glfw.shouldClose())
    {
        glfw.pollEvents();
        sceneUpdate(time.reset_s(), circles);

        sceneDraw(scene);
        glfw.swapBuffer();
    }
    return 0;
}
