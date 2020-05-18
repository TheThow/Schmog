#include "sgpch.h"
#include "LayerStack.h"

namespace Schmog {

	LayerStack::LayerStack()
		: m_LayerInsert(0)
	{
	}

	LayerStack::~LayerStack()
	{

	}

	void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsert, layer);
		m_LayerInsert++;
	}

	void LayerStack::PushOverlay(std::shared_ptr<Layer> layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(std::shared_ptr<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(std::shared_ptr<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

	inline std::vector<std::shared_ptr<Layer>>::iterator LayerStack::Begin()
	{
		return m_Layers.begin();
	}

	inline std::vector<std::shared_ptr<Layer>>::iterator LayerStack::End()
	{
		return m_Layers.end();
	}

}