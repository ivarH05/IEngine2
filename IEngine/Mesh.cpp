#include "Mesh.h"
#include "Graphics.h"

namespace IEngine
{
	void Mesh::OnDestroy()
	{
		Graphics::ReleaseMesh(this);
	}

	Pointer<Mesh> Mesh::Quad()
	{
		Pointer<Mesh> result = new Mesh();
		result->SetVertices(std::vector<float>
		{
			-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,

				-0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
		});
		return result;
	}

	Pointer<Mesh> Mesh::Cube()
	{
		Pointer<Mesh> result = new Mesh();
		result->SetVertices(std::vector<float>
		{
			// Top
				/*1*/ -0.5f, 0.5f, -0.5f, /*2*/ -0.5f, 0.5f, 0.5f, /*3*/ 0.5f, 0.5f, -0.5f,
				/*1*/ -0.5f, 0.5f, 0.5f, /*2*/ 0.5f, 0.5f, 0.5f, /*3*/ 0.5f, 0.5f, -0.5f,

			// Bottom
				/*1*/ -0.5f, -0.5f, -0.5f, /*2*/ 0.5f, -0.5f, -0.5f, /*3*/ -0.5f, -0.5f, 0.5f,
				/*1*/ 0.5f, -0.5f, -0.5f, /*2*/ 0.5f, -0.5f, 0.5f, /*3*/ -0.5f, -0.5f, 0.5f,

			// Front
				/*1*/ -0.5f, -0.5f, -0.5f, /*2*/ 0.5f, -0.5f, -0.5f, /*3*/ -0.5f, 0.5f, -0.5f,
				/*1*/ 0.5f, -0.5f, -0.5f, /*2*/ 0.5f, 0.5f, -0.5f, /*3*/ -0.5f, 0.5f, -0.5f,

			// Back
				/*1*/ -0.5f, -0.5f, 0.5f, /*2*/ -0.5f, 0.5f, 0.5f, /*3*/ 0.5f, -0.5f, 0.5f,
				/*1*/ -0.5f, 0.5f, 0.5f, /*2*/ 0.5f, 0.5f, 0.5f, /*3*/ 0.5f, -0.5f, 0.5f,

			// Left
				/*1*/ -0.5f, -0.5f, -0.5f, /*2*/ -0.5f, -0.5f, 0.5f, /*3*/ -0.5f, 0.5f, -0.5f,
				/*1*/ -0.5f, -0.5f, 0.5f, /*2*/ -0.5f, 0.5f, 0.5f, /*3*/ -0.5f, 0.5f, -0.5f,

			// Right
				/*1*/ 0.5f, -0.5f, -0.5f, /*2*/ 0.5f, 0.5f, -0.5f, /*3*/ 0.5f, -0.5f, 0.5f,
				/*1*/ 0.5f, 0.5f, -0.5f, /*2*/ 0.5f, 0.5f, 0.5f, /*3*/ 0.5f, -0.5f, 0.5f,
		});
		return result;
	}
}