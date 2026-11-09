#pragma once
#include "MonoBehaviour.h"
#include "Mesh.h"
#include "Material.h"

namespace IEngine
{
    class MeshRenderer : public MonoBehaviour<MeshRenderer>
    {
    private:
        Mesh* mesh = nullptr;
        Material* material = nullptr;

        int transformLoc = -1;

    public:
        void SetMesh(Mesh* value) 
        { 
            mesh = value;
            mesh->Upload();
        }

        void SetMaterial(Material* value) 
        { 
            material = value;
            material->Compile();
        }

        void OnRender()
        {
            if (!mesh || !material)
                return;

            material->Bind();

            Matrix4x4 transformMatrix = transform->GetMatrix();

            glUniformMatrix4fv(
                material->GetUniformLocation("transform"),
                1,
                GL_TRUE,
                &transformMatrix.m00
            );

            mesh->Bind();
            mesh->Draw();
        }

        virtual void OnDestroy() override {}
    };
}