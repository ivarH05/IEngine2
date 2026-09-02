#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GameObject.h"
#include "Transform.h"
#include "Pointer.h"
using namespace IEngine;

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
    Pointer<GameObject> object = new GameObject();
    object->instantiate();
    Pointer<GameObject> object2 = new GameObject();
    object2->instantiate("Engine/Rendering/Shaders/ExampleFragmentShader.glsl");

    Vector3 rot = Vector3::Zero();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClearDepth(0.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        glDepthMask(GL_TRUE);

        object->OnRender();
        object2->OnRender();
        glfwSwapBuffers(window);

        float moveSpeed = 0.01f;
        float scaleSpeed = 0.01f;
        float rotSpeed = 1.0f;

		Vector3 pos = object->transform->GetPosition(); 
		Vector3 scale = object->transform->GetLossyScale();

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos.y += moveSpeed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos.y -= moveSpeed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos.x -= moveSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos.x += moveSpeed;

        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) pos.z -= moveSpeed;
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) pos.z += moveSpeed;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) scale.x += scaleSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) scale.x -= scaleSpeed;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) scale.y += scaleSpeed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) scale.y -= scaleSpeed;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rot.z += rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) rot.z -= rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) rot.x += rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) rot.x -= rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) rot.y += rotSpeed;
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) rot.y -= rotSpeed;

		object->transform->SetPosition(pos);
		object->transform->SetLocalEulerAngles(rot);
		object->transform->SetLossyScale(scale);
    }

    glfwTerminate();
    return 0;
}