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
	m_Texture = Crisp::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}
void Sandbox2D::OnUpdate(Crisp::TimeStep ts)
{
	CR_PROFILE_FUNCTION();

	{
		CR_PROFILE_SCOPE("CameraController.OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Rendering
	{
		CR_PROFILE_SCOPE("DrawCall");
		Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Crisp::RenderCommand::Clear();

		Crisp::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Crisp::Renderer2D::DrawQuad({ -0.7f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.7f, 0.3f, 1.0f });
		Crisp::Renderer2D::DrawQuad({ 0.7f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.7f, 0.3f, 1.0f });
		Crisp::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 0.3f, 0.3f }, m_Texture);

		Crisp::Renderer2D::EndScene();
	}
	
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
 	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults)
	{
		char label[64];
		strcpy(label, result.Name);
		strcat(label, " %.3fms");
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();
	ImGui::End();
}

void Sandbox2D::OnEvent(Crisp::Event& e)
{
	m_CameraController.OnEvent(e);
}

