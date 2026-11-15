#pragma once
#include "Object.h"
#include <vector>

namespace IEngine
{
    class Graphics;

    class Mesh : public Object
    {
    private:
        std::vector<float> _vertices;

        friend class Graphics;

    public:
        const std::vector<float>& GetVertices() const { return _vertices; }
        void SetVertices(const std::vector<float>& vertices) { _vertices = vertices; }
        virtual void OnDestroy() override;

        static Pointer<Mesh> Quad();
        static Pointer<Mesh> Cube();
    };
}