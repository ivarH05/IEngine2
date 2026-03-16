#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Object.h"

namespace IEngine
{
	class GameObject : public Object
	{
	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);
		unsigned int shaderProgram;
		unsigned int VAO;
		unsigned int VBO;
		int positionLoc;
		int rotationLoc;
		int scaleLoc;

		static std::string ReadTextFile(const char* path)
		{
			std::ifstream file(path);
			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}

		void instantiate(const char* shader = "Engine/Rendering/Shaders/DefaultFragmentShader.glsl")
		{
			// Initiate materiald
			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSrc = ReadTextFile("Engine/Rendering/Shaders/DefaultVertexShader.glsl");
			std::string fragSrc = ReadTextFile(shader);
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

			positionLoc = glGetUniformLocation(shaderProgram, "position");
			rotationLoc = glGetUniformLocation(shaderProgram, "rotation");
			scaleLoc = glGetUniformLocation(shaderProgram, "scale");


			// Initiate mesh
			float vertices[] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			};

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}

		void OnRender()
		{
			glUseProgram(shaderProgram);
			glUniform3f(positionLoc, position.x, position.y, position.z);
			glUniform3f(rotationLoc, rotation.x, rotation.y, rotation.z);
			glUniform3f(scaleLoc, scale.x, scale.y, scale.z);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		~GameObject()
		{
			glDeleteProgram(shaderProgram);
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
	};
}