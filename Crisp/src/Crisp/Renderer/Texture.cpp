#include "pch.h"
#include "Texture.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Crisp
{



	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::Nono:
			CR_CORE_ASSERT(false, "Unchoose RendererAPI");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		
		return nullptr;
	}

}