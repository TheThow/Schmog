#pragma once

namespace Schmog {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void SetViewPort(int width, int height) = 0;
	};

}