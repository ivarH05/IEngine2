#pragma once
#include "Object.h"
#include <string>

namespace IEngine
{
    enum class DepthFunction
    {
        Never,
        Less,
        Equal,
        LessOrEqual,
        Greater,
        NotEqual,
        GreaterOrEqual,
        Always
    };

    class Graphics;

    class Material : public Object
    {
    private:
        std::string _vertexScript = "Engine/Rendering/Shaders/DefaultVertexShader.glsl";
        std::string _fragmentScript = "Engine/Rendering/Shaders/DefaultFragmentShader.glsl";
        bool _depthTestEnabled = true;
        DepthFunction _depthFunction = DepthFunction::Greater;
        bool _depthWriteEnabled = true;

        friend class Graphics;

    public:
        void SetShaderFiles(std::string vertexPath, std::string fragmentPath);
        const std::string& GetVertexShaderPath() const { return _vertexScript; }
        const std::string& GetFragmentShaderPath() const { return _fragmentScript; }
        void SetDepthTestEnabled(bool enabled);
        void SetDepthFunction(DepthFunction function);
        void SetDepthWriteEnabled(bool enabled);
        virtual void OnDestroy() override;
    };
}