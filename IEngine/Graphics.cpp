#include "Graphics.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "material.h"
#include "Matrix4x4.h"
#include "mesh.h"

namespace IEngine
{
	namespace
	{
		struct MeshResources
		{
			GLuint vertexArray = 0;
			GLuint vertexBuffer = 0;
		};

		struct MaterialResources
		{
			GLuint shaderProgram = 0;
			GLint transformLocation = -1;
		};

		GLFWwindow* _window = nullptr;
		bool _glfwInitialized = false;
		std::unordered_map<Mesh*, MeshResources> _meshResources;
		std::unordered_map<Material*, MaterialResources> _materialResources;

		std::string ReadTextFile(const std::string& path)
		{
			std::ifstream file(path);
			if (!file)
			{
				std::cerr << "Failed to open shader file: " << path << '\n';
				return {};
			}

			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}

		GLuint CompileShader(GLenum type, const std::string& source, const std::string& path)
		{
			GLuint shader = glCreateShader(type);
			const char* sourceText = source.c_str();
			glShaderSource(shader, 1, &sourceText, nullptr);
			glCompileShader(shader);

			GLint success = GL_FALSE;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (success == GL_TRUE)
				return shader;

			GLint logLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			std::string log(static_cast<std::size_t>(logLength), '\0');
			glGetShaderInfoLog(shader, logLength, nullptr, log.data());
			std::cerr << "Failed to compile shader " << path << ":\n" << log << '\n';
			glDeleteShader(shader);
			return 0;
		}

		GLuint CreateMaterialProgram(const Pointer<Material> material)
		{
			std::string vertexSource = ReadTextFile(material->GetVertexShaderPath());
			std::string fragmentSource = ReadTextFile(material->GetFragmentShaderPath());
			if (vertexSource.empty() || fragmentSource.empty())
				return 0;

			GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource, material->GetVertexShaderPath());
			if (vertexShader == 0)
				return 0;

			GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource, material->GetFragmentShaderPath());
			if (fragmentShader == 0)
			{
				glDeleteShader(vertexShader);
				return 0;
			}

			GLuint program = glCreateProgram();
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			GLint success = GL_FALSE;
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (success != GL_TRUE)
			{
				GLint logLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
				std::string log(static_cast<std::size_t>(logLength), '\0');
				glGetProgramInfoLog(program, logLength, nullptr, log.data());
				std::cerr << "Failed to link material shader program:\n" << log << '\n';
				glDeleteProgram(program);
				return 0;
			}

			return program;
		}

		GLenum ToOpenGLDepthFunction(DepthFunction function)
		{
			switch (function)
			{
			case DepthFunction::Never: return GL_NEVER;
			case DepthFunction::Less: return GL_LESS;
			case DepthFunction::Equal: return GL_EQUAL;
			case DepthFunction::LessOrEqual: return GL_LEQUAL;
			case DepthFunction::Greater: return GL_GREATER;
			case DepthFunction::NotEqual: return GL_NOTEQUAL;
			case DepthFunction::GreaterOrEqual: return GL_GEQUAL;
			case DepthFunction::Always: return GL_ALWAYS;
			default: return GL_GREATER;
			}
		}

		MeshResources& GetMeshResources(const Pointer<Mesh> mesh)
		{
			auto [iterator, inserted] = _meshResources.try_emplace(mesh.Get());
			if (inserted)
			{
				MeshResources& resources = iterator->second;
				glGenVertexArrays(1, &resources.vertexArray);
				glGenBuffers(1, &resources.vertexBuffer);
				glBindVertexArray(resources.vertexArray);
				glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBuffer);
				const std::vector<float>& vertices = mesh->GetVertices();
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
				glEnableVertexAttribArray(0);
				glBindVertexArray(0);
			}

			return iterator->second;
		}

		MaterialResources& GetMaterialResources(const Pointer<Material> material)
		{
			auto [iterator, inserted] = _materialResources.try_emplace(material.Get());
			if (inserted)
			{
				MaterialResources& resources = iterator->second;
				resources.shaderProgram = CreateMaterialProgram(material);
				if (resources.shaderProgram != 0)
					resources.transformLocation = glGetUniformLocation(resources.shaderProgram, "transform");
			}

			return iterator->second;
		}
	}

	bool Graphics::Initialize(int width, int height, const char* title)
	{
		if (_window != nullptr)
			return true;

		if (glfwInit() != GLFW_TRUE)
		{
			std::cerr << "Failed to initialize GLFW\n";
			return false;
		}
		_glfwInitialized = true;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (_window == nullptr)
		{
			std::cerr << "Failed to create window\n";
			Shutdown();
			return false;
		}

		glfwMakeContextCurrent(_window);
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cerr << "Failed to initialize GLAD\n";
			Shutdown();
			return false;
		}

		glViewport(0, 0, width, height);
		return true;
	}

	bool Graphics::IsWindowOpen()
	{
		return _window != nullptr && glfwWindowShouldClose(_window) == GLFW_FALSE;
	}

	bool Graphics::IsKeyPressed(int key)
	{
		return _window != nullptr && glfwGetKey(_window, key) == GLFW_PRESS;
	}

	void Graphics::PollEvents()
	{
		glfwPollEvents();
	}

	void Graphics::BeginFrame(float red, float green, float blue, float alpha, double depth)
	{
		glDepthMask(GL_TRUE);
		glClearColor(red, green, blue, alpha);
		glClearDepth(depth);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics::EndFrame()
	{
		if (_window != nullptr)
			glfwSwapBuffers(_window);
	}

	void Graphics::RenderMesh(const Pointer<Mesh> mesh, const Pointer<Material> material, const Matrix4x4& transform)
	{
		if (_window == nullptr)
			return;

		MaterialResources& materialData = GetMaterialResources(material);
		if (materialData.shaderProgram == 0)
			return;

		if (material->_depthTestEnabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
		glDepthFunc(ToOpenGLDepthFunction(material->_depthFunction));
		glDepthMask(material->_depthWriteEnabled ? GL_TRUE : GL_FALSE);

		glUseProgram(materialData.shaderProgram);
		glUniformMatrix4fv(materialData.transformLocation, 1, GL_TRUE, &transform.m00);

		MeshResources& meshData = GetMeshResources(mesh);
		glBindVertexArray(meshData.vertexArray);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh->GetVertices().size() / 3));
	}

	void Graphics::ReleaseMesh(const Pointer<Mesh> mesh)
	{
		auto iterator = _meshResources.find(mesh.Get());
		if (iterator == _meshResources.end())
			return;

		if (_window != nullptr)
		{
			glDeleteVertexArrays(1, &iterator->second.vertexArray);
			glDeleteBuffers(1, &iterator->second.vertexBuffer);
		}
		_meshResources.erase(iterator);
	}

	void Graphics::ReleaseMaterial(const Pointer<Material> material)
	{
		auto iterator = _materialResources.find(material.Get());
		if (iterator == _materialResources.end())
			return;

		if (_window != nullptr && iterator->second.shaderProgram != 0)
			glDeleteProgram(iterator->second.shaderProgram);
		_materialResources.erase(iterator);
	}

	void Graphics::Shutdown()
	{
		if (_window != nullptr)
		{
			for (const auto& [mesh, resources] : _meshResources)
			{
				glDeleteVertexArrays(1, &resources.vertexArray);
				glDeleteBuffers(1, &resources.vertexBuffer);
			}
			for (const auto& [material, resources] : _materialResources)
			{
				if (resources.shaderProgram != 0)
					glDeleteProgram(resources.shaderProgram);
			}
			_meshResources.clear();
			_materialResources.clear();
			glfwDestroyWindow(_window);
			_window = nullptr;
		}

		if (_glfwInitialized)
		{
			glfwTerminate();
			_glfwInitialized = false;
		}
	}
}
