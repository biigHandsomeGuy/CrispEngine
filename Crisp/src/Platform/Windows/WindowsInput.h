#pragma once

#include "Crisp/Input.h"

namespace Crisp
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keyCode) override;

		bool IsMouseBottonPressedImpl(int botton) override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		std::pair<float, float> GetMousePositionImpl() override;
	};
}