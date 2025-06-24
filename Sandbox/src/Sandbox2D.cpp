#include "Sandbox2D.h"
#include "imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),
	m_CameraController(1080.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
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



	m_FlatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColorShader.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Crisp::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	// Rendering
	Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Crisp::RenderCommand::Clear();

	Crisp::Renderer::BeginScene(m_CameraController.GetCamera());


	std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);


	// Quad
	// std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_Shader)->Bind();
	Crisp::Renderer::Submit(m_FlatColorShader, m_SquareVA);

	Crisp::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Crisp::Event& e)
{
	m_CameraController.OnEvent(e);
}
