#pragma once

#include "BasicInclude.hpp"
#include "glErrorCheck.hpp"
#include "math/Vectors.hpp"
#include "Vertex.hpp"

class Mesh
{
private:
public:
    GLuint vao = 0, vbo = 0, ebo = 0;
    uint32_t vboSize, iboSize;

    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint64> &indices)
    {
        this->vboSize = vertices.size();
        this->iboSize = indices.size();
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
            glCheckError();

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint64), indices.data(), GL_STATIC_DRAW);
            glCheckError();

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Vertex::pos));
        }

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~Mesh()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }
};
