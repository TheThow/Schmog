#pragma once

#include "Schmog/Core/Window.h"
#include "Schmog/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Schmog {

	class WindowsWindow : public Window
	{

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.width; }
		unsigned int GetHeight() const override { return m_Data.height; }

		void SetWidth(unsigned int width) override {  m_Data.width = width; }
		void SetHeight(unsigned int height) override { m_Data.height = height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		std::shared_ptr<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string title = "Default";
			unsigned int width = 0, height = 0;
			bool vSync = false;

			EventCallbackFn eventCallback;
		};

		WindowData m_Data;

	};

}