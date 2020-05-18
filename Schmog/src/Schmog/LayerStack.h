#pragma once

#include "Layer.h"
#include <vector>

namespace Schmog
{
	class SCHMOG_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> layer);

		void PopLayer(std::shared_ptr<Layer> layer);
		void PopOverlay(std::shared_ptr<Layer> layer);

		inline std::vector<std::shared_ptr<Layer>>::iterator Begin();
		inline std::vector<std::shared_ptr<Layer>>::iterator End();

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		int m_LayerInsert;
	};

}


