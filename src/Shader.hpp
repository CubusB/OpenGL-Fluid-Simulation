#pragma once

#include "BasicInclude.hpp"

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
private:
    GLuint shaderID = 0;
    GLuint vertexID = 0;
    GLuint fragmentID = 0;

public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath)
    {
        std::stringstream vertexStream = openShaderFile(vertexPath);
        std::stringstream fragmentStream = openShaderFile(fragmentPath);
        createShader(vertexStream.str(), fragmentStream.str());
    }

private:
    void createShader(const std::string &vertexSource, const std::string &fragmentSource)
    {
        this->shaderID = glCreateProgram();
        this->vertexID = glCreateShader(GL_VERTEX_SHADER);
        this->fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        if (!shaderID || !vertexID || !fragmentID)
        {
            throw std::runtime_error("[Shader] Couldn't create shader program.");
        }

        compileShader(vertexID, vertexSource.c_str(), vertexSource.size());
        glAttachShader(shaderID, vertexID);

        compileShader(fragmentID, fragmentSource.c_str(), fragmentSource.size());
        glAttachShader(shaderID, fragmentID);

        linkShader(shaderID);
    }

    std::stringstream openShaderFile(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("[Shader] Couldn't open shader \"" + path + "\".");
        }
        std::stringstream shaderStream;
        shaderStream << file.rdbuf();
        file.close();
        return shaderStream;
    }

    static void compileShader(GLuint handle, const char *source, const int size)
    {
        GLint compileResult = 0;
        glShaderSource(handle, 1, &source, &size);
        glCompileShader(handle);
        glGetShaderiv(handle, GL_COMPILE_STATUS, &compileResult);

        if (compileResult == GL_FALSE)
        {
            GLint infoLenth = 0;
            std::string shaderLog;

            glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLenth);
            shaderLog.resize(static_cast<std::size_t>(infoLenth));
            glGetShaderInfoLog(handle, infoLenth, nullptr, shaderLog.data());

            throw std::runtime_error("[Shader] ERROR compiling shader:\n" + shaderLog);
        }
    }

    static void linkShader(GLuint handle)
    {
        glLinkProgram(handle);

        GLint result = 0;
        glGetProgramiv(handle, GL_LINK_STATUS, &result);

        if (result == GL_FALSE)
        {
            GLint messageLenth = 0;
            std::string programLog;

            glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &messageLenth);

            if (messageLenth > 0)
            {
                programLog.resize(static_cast<std::size_t>(messageLenth));
                glGetProgramInfoLog(handle, messageLenth, nullptr, programLog.data());

                std::cerr << "[Shader] ERROR link shaderprogram: \n"
                          << programLog << std::endl;
                std::cerr.flush();
            }

            throw std::runtime_error("[Shader] ERROR compiling shader:\n" + programLog);
        }
    }

public:
    GLuint getShaderID()
    {
        return shaderID;
    }

    GLuint getVertexID()
    {
        return vertexID;
    }

    GLuint getFragmentID()
    {
        return fragmentID;
    }
};