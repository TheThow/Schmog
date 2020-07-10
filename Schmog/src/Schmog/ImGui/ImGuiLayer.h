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
		void OnEvent(Event& e) override;

		void OnImGuiRender() override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		bool EventsBlocked() { return m_BlockEvents;  }

	private:
		bool m_BlockEvents = false;
	};

}