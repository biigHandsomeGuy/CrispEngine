#include "pch.h"
#include "OrthographicCameraController.h"

#include "Crisp/Core/Input.h"
#include "Crisp/Core/KeyCodes.h"

namespace Crisp
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_Rotation(rotation)
	{


	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{

		if (Input::IsKeyPressed(CR_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(CR_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(CR_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(CR_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(CR_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(CR_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		// TODO:
		dispatcher.Dispatch<MouseScrolledEvent>(
			std::bind(&OrthographicCameraController::OnMouseScrolled, this, std::placeholders::_1));;

		dispatcher.Dispatch<WindowResizeEvent>(CR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = std::max(0.25f, m_ZoomLevel);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;

	}

}

