#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Vector3.h"

namespace IEngine
{
	class GameObject
	{
	private:const char* vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;

		uniform vec3 position;
		uniform vec3 rotation;   // Euler angles in radians (x, y, z)
		uniform vec3 scale;

		void main()
		{
			vec3 pos = aPos;

			// Scale
			pos *= scale;

			// Rotation around X
			float cx = cos(rotation.x);
			float sx = sin(rotation.x);
			pos = vec3(
				pos.x,
				pos.y * cx - pos.z * sx,
				pos.y * sx + pos.z * cx
			);

			// Rotation around Y
			float cy = cos(rotation.y);
			float sy = sin(rotation.y);
			pos = vec3(
				pos.x * cy + pos.z * sy,
				pos.y,
				-pos.x * sy + pos.z * cy
			);

			// Rotation around Z
			float cz = cos(rotation.z);
			float sz = sin(rotation.z);
			pos = vec3(
				pos.x * cz - pos.y * sz,
				pos.x * sz + pos.y * cz,
				pos.z
			);

			// Translation
			pos += position;

			gl_Position = vec4(pos, 1.0);
		}
		)";

		const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 FragColor;
		void main()
		{
			FragColor = vec4(1.0, 1.0, 0.0, 1.0);
		}
		)";

	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);
		unsigned int shaderProgram;
		unsigned int VAO;
		int positionLoc;
		int rotationLoc;
		int scaleLoc;

		GameObject(unsigned int defaultShader) 
		{
			// Initiate material
			shaderProgram = defaultShader;
			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
			glCompileShader(vertexShader);

			unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
			glCompileShader(fragmentShader);

			shaderProgram = glCreateProgram();
			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);
			glLinkProgram(shaderProgram);

			positionLoc = glGetUniformLocation(shaderProgram, "position");
			rotationLoc = glGetUniformLocation(shaderProgram, "rotation");
			scaleLoc = glGetUniformLocation(shaderProgram, "scale");


			// Initiate mesh
			float vertices[] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			};

			unsigned int VBO;
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
	};
}