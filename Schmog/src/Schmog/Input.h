#pragma once

#include "Schmog/Core.h"
#include <memory>

namespace Schmog {


	class SCHMOG_API Input
	{
	public:
		struct SCHMOG_API MousePosition {
			float x, y;
		};

	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static MousePosition GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual MousePosition GetMousePositionImpl() = 0;


	private:
		static std::shared_ptr<Input> s_Instance;
	};


}