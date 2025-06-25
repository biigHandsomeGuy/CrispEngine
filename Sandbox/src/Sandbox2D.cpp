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
	Crisp::Renderer2D::Init();
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

	Crisp::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	Crisp::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.7f, 0.3f, 1.0f });
	Crisp::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 0.2f, 0.3f }, { 7.2f, 2.7f, 0.3f, 1.0f });

	Crisp::Renderer2D::EndScene();


	//std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);


	// Quad
	// std::dynamic_pointer_cast<Crisp::OpenGLShader>(m_Shader)->Bind();
	//Crisp::Renderer::Submit(m_FlatColorShader, m_SquareVA);

	
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
