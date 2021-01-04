#pragma once

#include <memory>
#include <stdint.h>

#include "Scene.h"

namespace Schmog {

	class Entity 
	{
		friend class Scene;

	public:
		Entity() {};
		Entity(Scene* scene, uint32_t id);

		void Destroy();

		template<class T, typename... Args>
		T& AddComponent(Args&&... args) const
		{
			SG_CORE_ASSERT(m_Scene, "Scene is null");
			return m_Scene->AddComponent<T>(*this, std::forward<Args>(args)...);
		}

		template<class T>
		T& GetComponent() const
		{
			SG_CORE_ASSERT(m_Scene, "Scene is null");
			return m_Scene->GetComponent<T>(*this);
		}

		template<class T>
		void RemoveComponent() const
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

		operator uint32_t() const
		{
			return m_Id;
		}

		operator bool() const
		{
			return m_Scene && m_Scene->EntityExists(*this);
		}

		bool operator==(const Entity& other) const
		{
			return m_Id == other.m_Id && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		uint32_t m_Id = 0;
		Scene* m_Scene = nullptr;
	};
}



