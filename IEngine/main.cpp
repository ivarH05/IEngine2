#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GameObject.h"
using namespace IEngine;

const char* defaultVertexShader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* defaultFragmentShader = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
)";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);
	GameObject object = GameObject();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		object.OnRender();
        glfwSwapBuffers(window);

        float moveSpeed = 0.01f;
        float scaleSpeed = 0.01f;
        float rotSpeed = 0.02f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) object.position.y += moveSpeed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) object.position.y -= moveSpeed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) object.position.x -= moveSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) object.position.x += moveSpeed;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) object.scale.x += scaleSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) object.scale.x -= scaleSpeed;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) object.scale.y += scaleSpeed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) object.scale.y -= scaleSpeed;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) object.rotation.z += rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) object.rotation.z -= rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) object.rotation.x += rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) object.rotation.x -= rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) object.rotation.y += rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) object.rotation.y -= rotSpeed;

    }

    glfwTerminate();
    return 0;
}