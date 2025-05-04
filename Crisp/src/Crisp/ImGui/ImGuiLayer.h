#pragma once

#include "Crisp/Layer.h"
#include "Crisp/Events/MouseEvent.h"
#include "Crisp/Events/ApplicationEvent.h"
#include "Crisp/Events/KeyEvent.h"

namespace Crisp
{
	class CRISP_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};


}