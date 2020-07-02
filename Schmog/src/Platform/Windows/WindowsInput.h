#pragma once
#include "Schmog/Core/Input.h"

namespace Schmog {

	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(KeyCode keycode) override;
		virtual bool IsMouseButtonPressedImpl(MouseButtonCode button) override;

		virtual MousePosition GetMousePositionImpl() override;
	};

}