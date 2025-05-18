#include "pch.h"
#include "VertexArray.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Crisp
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Nono:
			CR_CORE_ASSERT(false, "Unchoose RendererAPI");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}

		return nullptr;
	}
}