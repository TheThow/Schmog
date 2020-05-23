#pragma once

#include "Schmog/Core.h"
#include <memory>

namespace Schmog {


	class SCHMOG_API Input
	{
	public:
		struct SCHMOG_API MousePosition {
			float x{ 0.0f }, y{ 0.0f };
		};
		

	public:
		virtual ~Input() = default;

		static bool IsKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		static MousePosition GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual MousePosition GetMousePositionImpl() = 0;


	private:
		static Input* s_Instance;
	};


}