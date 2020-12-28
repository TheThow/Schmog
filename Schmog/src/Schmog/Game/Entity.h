#pragma once

#include <memory>
#include <stdint.h>

#include "Scene.h"

namespace Schmog {

	class Entity 
	{
		friend class Scene;

	public:

		template<class T>
		T& AddComponent(T& component) const
		{
			SG_CORE_ASSERT(m_Scene, "Scene is null");
			return m_Scene->AddComponent<T>(*this, component);
		}

		template<class T>
		T& GetComponent() const
		{
			SG_CORE_ASSERT(m_Scene, "Scene is null");
			return m_Scene->GetComponent<T>(*this);
		}

		template<class T>
		T& RemoveComponent() const
		{
			SG_CORE_ASSERT(m_Scene, "Scene is null");
			return m_Scene->RemoveComponent<T>(*this);
		}

		template<class T>
		bool HasComponent() const
		{
			SG_CORE_ASSERT(m_Scene, "Scene is null");
			return m_Scene->HasComponent<T>(*this);
		}

		uint32_t GetId() const;

	private:
		Entity(Scene* scene, uint32_t id);

		uint32_t m_Id = 0;
		Scene* m_Scene;
	};
}



