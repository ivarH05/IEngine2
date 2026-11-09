#include <GLFW/glfw3.h>
#include "Graphics.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Pointer.h"
#include "MonoBehaviourManager.h"

using namespace IEngine;

int main()
{
	if (!Graphics::Initialize(800, 600, "Triangle"))
		return -1;

	Pointer<Mesh> mesh = Mesh::Cube();
	Pointer<Material> material = new Material();

	Pointer<GameObject> object = new GameObject();
	object->AddComponent<MeshRenderer>();
	object->transform->name = "Object 0";

	object->GetComponent<MeshRenderer>()->SetMaterial(material.Get());
	object->GetComponent<MeshRenderer>()->SetMesh(mesh);

	Pointer<GameObject> object1 = new GameObject();
	object1->AddComponent<MeshRenderer>();
	object1->GetComponent<MeshRenderer>()->SetMaterial(material.Get());
	object1->GetComponent<MeshRenderer>()->SetMesh(mesh);
	object1->transform->name = "Object 1";
	object1->transform->SetParent(object->transform);
	object1->transform->SetLocalEulerAngles(Vector3(0.0f, 90.0f, 0.0f));
	object1->transform->SetLocalPosition(Vector3(0.0f, 0.5f, 0.0f));
	object1->transform->SetLocalScale(Vector3(0.5f, 0.5f, 0.5f));

	Pointer<GameObject> object2 = new GameObject();
	object2->AddComponent<MeshRenderer>();
	object2->GetComponent<MeshRenderer>()->SetMaterial(material.Get());
	object2->GetComponent<MeshRenderer>()->SetMesh(mesh.Get());
	object2->transform->name = "Object 2";

	Vector3 rot = Vector3::Zero();

	while (Graphics::IsWindowOpen())
	{
		Graphics::PollEvents();
		Graphics::BeginFrame(0.1f, 0.1f, 0.15f, 1.0f, 0.0);

		MonoBehaviourManager::UpdateComponents();
		MonoBehaviourManager::LateUpdateComponents();
		/// TODO: Implemend a FixedUpdate cycle
		MonoBehaviourManager::FixedUpdateComponents();
		MonoBehaviourManager::RenderComponents();

		Graphics::EndFrame();

		float moveSpeed = 0.01f;
		float scaleSpeed = 0.01f;
		float rotSpeed = 1.0f;

		Vector3 pos = object->transform->GetPosition();
		Vector3 scale = object->transform->GetLossyScale();

		if (Graphics::IsKeyPressed(GLFW_KEY_W)) pos.y += moveSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_S)) pos.y -= moveSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_A)) pos.x -= moveSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_D)) pos.x += moveSpeed;

		if (Graphics::IsKeyPressed(GLFW_KEY_Z)) pos.z -= moveSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_X)) pos.z += moveSpeed;

		if (Graphics::IsKeyPressed(GLFW_KEY_RIGHT)) scale.x += scaleSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_LEFT)) scale.x -= scaleSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_UP)) scale.y += scaleSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_DOWN)) scale.y -= scaleSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_PERIOD)) scale.z += scaleSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_COMMA)) scale.z -= scaleSpeed;

		if (Graphics::IsKeyPressed(GLFW_KEY_Q)) rot.y += rotSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_E)) rot.y -= rotSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_I)) rot.x += rotSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_K)) rot.x -= rotSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_J)) rot.z += rotSpeed;
		if (Graphics::IsKeyPressed(GLFW_KEY_L)) rot.z -= rotSpeed;

		object->transform->SetPosition(pos);
		object->transform->SetLocalEulerAngles(rot);
		object->transform->SetLossyScale(scale);
	}

	Graphics::Shutdown();
	return 0;
}