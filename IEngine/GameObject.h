#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vector3.h"
#include "Matrix4x4.h"
#include "Object.h"
#include "Pointer.h"

namespace IEngine
{
	class Transform;
	class Component;

	class GameObject : public Object
	{
	public:
		/* TEMP */
		unsigned int shaderProgram;
		unsigned int VAO;
		unsigned int VBO;
		int transformLoc;

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

			transformLoc = glGetUniformLocation(shaderProgram, "transform");


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

		void OnRender();

		~GameObject()
		{
			glDeleteProgram(shaderProgram);
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}

		/* END OF TEMP */

		GameObject();

		template <typename T>
		Pointer<T> AddComponent();

		template <typename T>
		Pointer<T> GetComponent();

		const Pointer<Transform> transform;

	private:
		std::vector<Pointer<Component>> _components;
	};
}

#include "GameObject.inl"