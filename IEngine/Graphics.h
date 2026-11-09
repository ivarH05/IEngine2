#pragma once
#include "Pointer.h"

namespace IEngine
{
	class Material;
	struct Matrix4x4;
	class Mesh;

	class Graphics
	{
	public:
		static bool Initialize(int width, int height, const char* title);
		static bool IsWindowOpen();
		static bool IsKeyPressed(int key);
		static void PollEvents();
		static void BeginFrame(float red, float green, float blue, float alpha, double depth = 0.0);
		static void EndFrame();
		static void RenderMesh(const Pointer<Mesh> mesh, const Pointer<Material> material, const Matrix4x4& transform);
		static void Shutdown();

	private:
		friend class Material;
		friend class Mesh;

		static void ReleaseMaterial(const Pointer<Material> material);
		static void ReleaseMesh(const Pointer<Mesh> mesh);
	};
}

