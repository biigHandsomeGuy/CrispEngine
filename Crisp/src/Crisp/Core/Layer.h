#pragma once

#include "Crisp/Core/Core.h"
#include "Crisp/Core/TimeStep.h"
#include "Crisp/Events/Event.h"

namespace Crisp
{
	class CRISP_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(TimeStep ts){}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event&){}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};


}