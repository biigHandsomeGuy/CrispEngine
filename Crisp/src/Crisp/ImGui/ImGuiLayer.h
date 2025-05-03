#pragma once

#include "Crisp/Layer.h"

namespace Crisp
{
	class CRISP_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event&) override;
	private:
		float m_Time = 0.0f;
	};


}