#include "pch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>
namespace Crisp
{
	struct Renderer2DStroage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> FlatShaderColor;
		std::shared_ptr<Shader> TextureShader;
	};

	static Renderer2DStroage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStroage();

		s_Data->QuadVertexArray = Crisp::VertexArray::Create();

		float squareVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Crisp::VertexBuffer> squareVB;
		squareVB.reset(Crisp::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Crisp::BufferLayout squareLayout = {
			{Crisp::ShaderDataType::Float3, "a_Position"},
			{Crisp::ShaderDataType::Float2, "a_TexCoord"},
		};
		squareVB->SetLayout(squareLayout);
		 
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 1, 2, 3 };
		std::shared_ptr<Crisp::IndexBuffer> squareIB;
		squareIB.reset(Crisp::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);



		s_Data->FlatShaderColor = Shader::Create("assets/shaders/FlatColorShader.glsl");
		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->FlatShaderColor->Bind();
		s_Data->FlatShaderColor->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->FlatShaderColor->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->FlatShaderColor->SetMat4("u_Transform", transform);
		s_Data->FlatShaderColor->SetFloat4("u_Color", color);
		
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture2D>& texture)
	{
		s_Data->TextureShader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		 
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		texture->Bind(0);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}