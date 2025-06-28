#pragma once

#include <Crisp.h>
struct ProfileResult
{
	const char* Name;
	float Time;
};
class Sandbox2D : public Crisp::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Crisp::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Crisp::Event&) override;

private:
	Crisp::ShaderLibrary m_ShaderLibrary;

	std::shared_ptr<Crisp::Shader> m_FlatColorShader;
	std::shared_ptr<Crisp::VertexArray> m_SquareVA;

	Crisp::OrthographicCameraController m_CameraController;

	std::shared_ptr<Crisp::Texture2D> m_Texture;

	

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.7f, 1.0f };
};