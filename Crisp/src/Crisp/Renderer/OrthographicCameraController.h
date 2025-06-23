#pragma once

#include "Crisp/Renderer/OrthographicCamera.h"
#include "Crisp/Core/TimeStep.h"

#include "Crisp/Events/ApplicationEvent.h"
#include "Crisp/Events/MouseEvent.h"



namespace Crisp
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		
		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; // rotation angle?
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 90.0f;
	};


}