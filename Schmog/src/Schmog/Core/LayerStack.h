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

		std::vector<std::shared_ptr<Layer>>::iterator begin() {	return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		unsigned int m_LayerInsert{ 0 };
	};

}


