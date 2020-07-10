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

		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseButtonCode button);

		static MousePosition GetMousePosition();

	};


}