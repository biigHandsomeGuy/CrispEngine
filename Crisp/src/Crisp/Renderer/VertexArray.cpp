#include "pch.h"
#include "VertexArray.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Crisp
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::Nono:
			CR_CORE_ASSERT(false, "Unchoose RendererAPI");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		return nullptr;
	}
}