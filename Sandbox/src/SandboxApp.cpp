#include <Crisp.h>
#include <Crisp/Core/EntryPoint.h>
#include "imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"


class ExampleLayer : public Crisp::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),
		m_CameraController(1080.0f / 720.0f, true)
	{
		m_VertexArray = Crisp::VertexArray::Create();

		float vertices[] =
		{
			0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			-0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};
		std::shared_ptr<Crisp::VertexBuffer> triangleVB;
		triangleVB.reset(Crisp::VertexBuffer::Create(vertices, sizeof(vertices)));

		Crisp::BufferLayout layout = {
			{Crisp::ShaderDataType::Float3, "a_Position"},
			{Crisp::ShaderDataType::Float4, "a_Color"},
		};
		triangleVB->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(triangleVB);

		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<Crisp::IndexBuffer> triangleIB;
		triangleIB.reset(Crisp::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIB);

		m_SquareVA = Crisp::VertexArray::Create();

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

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 1, 2, 3 };
		std::shared_ptr<Crisp::IndexBuffer> squareIB;
		squareIB.reset(Crisp::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);



		std::string flatColorVS = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string flatColorPS = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;
			
			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader = Crisp::Shader::Create("flatShader", flatColorVS, flatColorPS);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Crisp::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Crisp::Texture2D::Create("assets/textures/logo.png");

		std::dynamic_pointer_cast<Crisp::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Crisp::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}
	void OnUpdate(Crisp::TimeStep ts) override 
	{
		m_CameraController.OnUpdate(ts);

		// Rendering
		Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Crisp::RenderCommand::Clear();

		Crisp::Renderer::BeginScene(m_CameraController.GetCamera());


		std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		m_Texture->Bind();
		Crisp::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA);
		
		m_LogoTexture->Bind();
		Crisp::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA);


		// Triangle
		// std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_Shader)->Bind();
		Crisp::Renderer::Submit(m_FlatColorShader, m_VertexArray);

		Crisp::Renderer::EndScene();
	}
	void OnEvent(Crisp::Event& event) override 
	{
		m_CameraController.OnEvent(event);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}
private:
	Crisp::ShaderLibrary m_ShaderLibrary;

	std::shared_ptr<Crisp::VertexArray> m_VertexArray;

	std::shared_ptr<Crisp::Shader> m_FlatColorShader;
	std::shared_ptr<Crisp::VertexArray> m_SquareVA;

	std::shared_ptr<Crisp::Texture2D> m_Texture, m_LogoTexture;

	Crisp::OrthographicCameraController m_CameraController;

	glm::mat4 m_SqureTransform;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.7f, 1.0f };
};

class Sandbox : public Crisp::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Crisp::Application* Crisp::CreateApplication()
{
	return new Sandbox();
}
