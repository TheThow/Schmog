#include <Schmog.h>
// ------ ENTRY POINT ------
#include "Schmog/EntryPoint.h"
#include <memory>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.inl>

#include "EditorLayer.h"


namespace Schmog {

	class Scheditor : public Schmog::Application
	{
	public:
		Scheditor()
			: Application("Scheditor")
		{
			PushLayer(std::make_shared<ScheditorLayer>());
		}

		~Scheditor()
		{

		}


	};

	std::shared_ptr<Schmog::Application> Schmog::CreateApplication()
	{
		return std::make_shared<Scheditor>();
	}

}
