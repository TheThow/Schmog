#pragma once

namespace Schmog {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual ~GraphicsContext() = default;
		virtual void SwapBuffers() = 0;
	};

}