#pragma once

#include "Schmog/Layer.h"
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

		void OnUpdate() override;
		void OnEvent(Event& e) override;

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);


		void HandleSpecial(ImGuiIO& io);


	private:
		float m_Time = 0;
	};

}