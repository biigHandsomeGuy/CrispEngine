#include "Sandbox2D.h"
#include "imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& fn)
		:m_Name(name), m_Func(fn), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
		{
			Stop();
		}
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};
template<typename Fn>
Timer(const char*, Fn&&) -> Timer<Fn>;


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
	Timer timer("", [&](ProfileResult result) { m_ProfileResults.push_back(result); });


	{
		//Timer timer("m_CameraController::OnUpdate", [&](ProfileResult result) { m_ProfileResults.push_back(result); });
		m_CameraController.OnUpdate(ts);
	}

	// Rendering
	Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Crisp::RenderCommand::Clear();

	Crisp::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	Crisp::Renderer2D::DrawQuad({ -0.7f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.7f, 0.3f, 1.0f });
	Crisp::Renderer2D::DrawQuad({ 0.7f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.7f, 0.3f, 1.0f });
	Crisp::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 0.3f, 0.3f }, m_Texture);

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

