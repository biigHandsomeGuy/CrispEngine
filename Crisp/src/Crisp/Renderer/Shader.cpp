#include "pch.h"
#include "Shader.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Crisp
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::Nono:
			CR_CORE_ASSERT(false, "Unchoose RendererAPI");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		return nullptr;
	}
}