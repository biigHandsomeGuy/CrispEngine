#include <Crisp.h>

#include "imgui.h"

class ExampleLayer : public Crisp::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),
		m_Camera(-1.6f, 1.6f, -1.2f, 1.2f)
	{
		m_VertexArray.reset(Crisp::VertexArray::Create());

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

		m_SquareVA.reset(Crisp::VertexArray::Create());

		float squareVertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<Crisp::VertexBuffer> squareVB;
		squareVB.reset(Crisp::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Crisp::BufferLayout squareLayout = {
			{Crisp::ShaderDataType::Float3, "a_Position"},
		};
		squareVB->SetLayout(squareLayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 1, 2, 3 };
		std::shared_ptr<Crisp::IndexBuffer> squareIB;
		squareIB.reset(Crisp::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			layout(location = 1) in vec4 a_Color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
				color = v_Color;
			}
		)";
		m_Shader.reset(new Crisp::Shader(vertexSrc, fragmentSrc));

		std::string blueVS = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
			}
		)";

		std::string bluePS = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
			}
		)";

		m_BlueShader.reset(new Crisp::Shader(blueVS, bluePS));
	}
	void OnUpdate() override
	{
		if (Crisp::Input::IsKeyPressed(CR_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed;
		if (Crisp::Input::IsKeyPressed(CR_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed;
		if (Crisp::Input::IsKeyPressed(CR_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed;
		if (Crisp::Input::IsKeyPressed(CR_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed;

		Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Crisp::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(0.0f);

		Crisp::Renderer::BeginScene(m_Camera);

		Crisp::Renderer::Submit(m_BlueShader, m_SquareVA);
		Crisp::Renderer::Submit(m_Shader, m_VertexArray);

		Crisp::Renderer::EndScene();
	}
	void OnEvent(Crisp::Event& event) override 
	{
		
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("ss");
		ImGui::End();
	}
private:

	std::shared_ptr<Crisp::Shader> m_Shader;
	std::shared_ptr<Crisp::VertexArray> m_VertexArray;

	std::shared_ptr<Crisp::Shader> m_BlueShader;
	std::shared_ptr<Crisp::VertexArray> m_SquareVA;

	Crisp::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1;
};

class Sandbox : public Crisp::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Crisp::Application* Crisp::CreateApplication()
{
	return new Sandbox();
}
