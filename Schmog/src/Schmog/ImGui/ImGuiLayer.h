#pragma once

#include "Schmog/Core/Layer.h"
#include "Schmog/Events/MouseEvent.h"
#include "Schmog/Events/KeyEvent.h"
#include "Schmog/Events/ApplicationEvent.h"


// Forward declaration to avoid imgui.h
struct ImGuiIO;

namespace Schmog {

	class SCHMOG_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnImGuiRender() override;

		void Begin();
		void End();

	};

}