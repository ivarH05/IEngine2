#pragma once
#include "Object.h"
#include <glad/glad.h>
#include <vector>

namespace IEngine
{
    class Mesh : public Object
    {
    private:
        std::vector<float> vertices =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        unsigned int VAO = 0;
        unsigned int VBO = 0;

    public:
        void Upload()
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(
                GL_ARRAY_BUFFER,
                vertices.size() * sizeof(float),
                vertices.data(),
                GL_STATIC_DRAW
            );

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindVertexArray(0);
        }

        void Bind()
        {
            glBindVertexArray(VAO);
        }

        void Draw()
        {
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
        }

        virtual void OnDestroy() override
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }
    };
}