#include <Schmog.h>
// ------ ENTRY POINT ------
#include "Schmog/EntryPoint.h"
#include <memory>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.inl>

#include "EditorLayer.h"


namespace Schmog {

	class Schmeditor : public Schmog::Application
	{
	public:
		Schmeditor()
			: Application("Schmeditor")
		{
			PushLayer(std::make_shared<SchmeditorLayer>());
		}

		~Schmeditor()
		{

		}


	};

	std::shared_ptr<Schmog::Application> Schmog::CreateApplication()
	{
		return std::make_shared<Schmeditor>();
	}

}
