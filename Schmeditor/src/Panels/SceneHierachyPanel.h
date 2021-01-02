#pragma once

#include <memory>

#include "Schmog.h"

namespace Schmog {

	class SceneHierachyPanel
	{
	public:
		SceneHierachyPanel() = default;

		void SetContext(const std::shared_ptr<Scene> context);
		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		std::shared_ptr<Scene> m_Context;
		Entity m_SelectionContext;
	};
}



