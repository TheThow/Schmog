#pragma once

#include "Schmog/Core/Core.h"
#include <memory>

#include "Schmog/Core/KeyCodes.h"
#include "Schmog/Core/MouseButtonCodes.h"

namespace Schmog {


	class SCHMOG_API Input
	{
	public:
		struct SCHMOG_API MousePosition {
			float x{ 0.0f }, y{ 0.0f };
		};
		

	public:
		virtual ~Input() = default;

		static bool IsKeyPressed(KeyCode keycode) { return s_Instance->isKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		static MousePosition GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool isKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;

		virtual MousePosition GetMousePositionImpl() = 0;


	private:
		static Input* s_Instance;
	};


}