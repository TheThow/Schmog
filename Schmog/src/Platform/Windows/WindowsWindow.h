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

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }

		void SetWidth(unsigned int width) override {  m_Data.Width = width; }
		void SetHeight(unsigned int height) override { m_Data.Height = height; }

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
			std::string Title = "Default";
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallbackFn eventCallback;
		};

		WindowData m_Data;

	};

}