#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <stdnoreturn.h>
#include <string>
#include <unordered_set>


class GLFW_Window
{
public:
private:
    std::unique_ptr<GLFWwindow, void (*)(GLFWwindow*)> window;

    static void windowDelete(GLFWwindow *window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

public:
    GLFW_Window(const std::string &title, int width = 1280, int height = 720)
        : window(nullptr, windowDelete)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("glfwInit failed");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        window.reset(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr));

        if (!window.get())
        {
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow failed");
        }

        glfwMakeContextCurrent(window.get());
        glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("gladLoadGLLoader failed");
        }
    }

    GLFW_Window(GLFW_Window &&other)
        : window(std::move(other.window))
    {
    }

private:
public:
    operator GLFWwindow *() const
    {
        return window.get();
    }

    GLFWwindow *get() const
    {
        return window.get();
    }
};

class GLFW
{
private:
    struct WindowSize
    {
        int width, height;
    };

    GLFW_Window window;

public:
    GLFW(GLFW_Window &&other)
        : window(std::move(other))
    {
        setCallbacks();
        glEnable(GL_DEPTH_TEST);
    }

private:
    void setCallbacks()
    {
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, mousePosCallback);
        glfwSetKeyCallback(window, keyCallback);
        glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    }

    static void windowResizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
    }

    static void mousePosCallback(GLFWwindow *window, double x, double y)
    {
    }

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        static std::unordered_set<int> unhandledKeys;

        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        default:
        {
            if (action == GLFW_PRESS && unhandledKeys.find(key) == unhandledKeys.end())
            {
                unhandledKeys.insert(key);
                printf("unhandled key: %d\n", key);
            }
            break;
        }
        }
    }

public:
    bool shouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    static void pollEvents()
    {
        glfwPollEvents();
    }

    void swapBuffer()
    {
        glfwSwapBuffers(window);
    }

    WindowSize getWindowSize()
    {
        WindowSize size;
        glfwGetWindowSize(window, &(size.width), &(size.height));
        return size;
    }
};

