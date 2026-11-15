#include "Material.h"
#include "Graphics.h"
#include <utility>

namespace IEngine
{
	void Material::SetShaderFiles(std::string vertexPath, std::string fragmentPath)
	{
		if (_vertexScript == vertexPath && _fragmentScript == fragmentPath)
			return;

		Graphics::ReleaseMaterial(this);
		_vertexScript = std::move(vertexPath);
		_fragmentScript = std::move(fragmentPath);
	}

	void Material::SetDepthTestEnabled(bool enabled)
	{
		_depthTestEnabled = enabled;
	}

	void Material::SetDepthFunction(DepthFunction function)
	{
		_depthFunction = function;
	}

	void Material::SetDepthWriteEnabled(bool enabled)
	{
		_depthWriteEnabled = enabled;
	}

	void Material::OnDestroy()
	{
		Graphics::ReleaseMaterial(this);
	}
}
