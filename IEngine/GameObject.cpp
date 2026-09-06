#include "GameObject.h"
#include "Transform.h"

namespace IEngine
{
	/* TEMP */
	void GameObject::OnRender()
	{
		glUseProgram(shaderProgram);
		Matrix4x4 transformMatrix = transform->GetMatrix();
		glUniformMatrix4fv(transformLoc, 1, GL_TRUE, &transformMatrix.m00);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	/* END OF TEMP */

	GameObject::GameObject() : transform(new Transform())
	{
		_components.push_back(Pointer<Component>(transform));
	}
}