#pragma once
#include "MonoBehaviour.h"
#include "Mesh.h"
#include "Material.h"
#include "Graphics.h"

namespace IEngine
{
    class MeshRenderer : public MonoBehaviour<MeshRenderer>
    {
    private:
        Pointer<Mesh> _mesh = nullptr;
        Pointer<Material> _material = nullptr;

    public:
        void SetMesh(Pointer<Mesh> value)
        { 
            _mesh = value;
        }

        void SetMaterial(Pointer<Material> value)
        { 
            _material = value;
        }

        void OnRender()
        {
            if (!_mesh || !_material)
                return;

            Graphics::RenderMesh(_mesh, _material, transform->GetMatrix());
        }
    };
}