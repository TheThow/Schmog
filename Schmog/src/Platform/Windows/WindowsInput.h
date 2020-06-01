#pragma once
#include "Schmog/Core/Input.h"

namespace Schmog {

	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;

		virtual MousePosition GetMousePositionImpl() override;
	};

}