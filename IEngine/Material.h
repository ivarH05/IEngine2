#pragma once
#include "Object.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>

namespace IEngine
{
    class Material : public Object
    {
    private:
        std::string vertexScript = "Engine/Rendering/Shaders/DefaultVertexShader.glsl";
        std::string fragmentScript = "Engine/Rendering/Shaders/DefaultFragmentShader.glsl";

        unsigned int shaderProgram = 0;

        static std::string ReadTextFile(std::string path)
        {
            std::ifstream file(path);
            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }

    public:
        void Compile()
        {
            unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
            unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

            std::string vertSrc = ReadTextFile(vertexScript);
            std::string fragSrc = ReadTextFile(fragmentScript);

            const char* vSrc = vertSrc.c_str();
            const char* fSrc = fragSrc.c_str();

            glShaderSource(vertexShader, 1, &vSrc, NULL);
            glCompileShader(vertexShader);

            glShaderSource(fragmentShader, 1, &fSrc, NULL);
            glCompileShader(fragmentShader);

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void Bind()
        {
            glUseProgram(shaderProgram);
        }

        int GetUniformLocation(const char* name)
        {
            return glGetUniformLocation(shaderProgram, name);
        }

        virtual void OnDestroy() override
        {
            glDeleteProgram(shaderProgram);
        }
    };
}