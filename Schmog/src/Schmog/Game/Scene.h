#pragma once
#include <typeindex>

#include "ComponentDataContainer.h"
#include "ComponentRegistry.h"

namespace Schmog {

	class Entity;

	class Scene
	{
	public:
		Entity CreateEntity();
		Entity CreateEntity(std::string& name);

		void DeleteEntity(Entity& entity);

		template<class T, typename... Args>
		T& AddComponent(const Entity& entity, Args&&... args)
		{
			return m_Registry.AddComponent<T>(entity.GetId(), std::forward<Args>(args)...);
		}

		template<class T>
		T& GetComponent(const Entity& entity)
		{
			return m_Registry.GetComponent<T>(entity.GetId());
		}

		template<class T>
		Entity GetEntityByIndex(uint32_t index)
		{
			return m_Registry.GetEntityByIndex<T>(index);
		}

		template<class T>
		bool HasComponent(const Entity& entity)
		{
			return m_Registry.HasComponent<T>(entity.GetId());
		}

		template<class T>
		void RemoveComponent(const Entity& entity)
		{
			m_Registry.RemoveComponent<T>(entity.GetId());
		}

		template<class T>
		ComponentDataContainer<T>& GetComponents()
		{
			return m_Registry.GetComponents<T>();
		}

		void OnViewportResize(uint32_t width, uint32_t height);
		void OnUpdate();

	private:
		ComponentRegistry m_Registry;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	};
}



