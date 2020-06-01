#pragma once

#include "Schmog/Events/Event.h"


namespace Schmog {

	class SCHMOG_API Layer
	{
	public:
		Layer(const std::string& name);
		~Layer();

		virtual void OnEvent(Event& e) {}
		virtual void OnUpdate() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnImGuiRender() {}

	protected:
		std::string m_DebugName;
	};

}



