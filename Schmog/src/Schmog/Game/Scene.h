#pragma once
#include <typeindex>

#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/TagComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "ComponentDataContainer.h"
#include "ComponentRegistry.h"

namespace Schmog {

	class Entity;

	class Scene
	{
	public:
		Entity CreateEntity();
		Entity CreateEntity(std::string& name);
		Entity CreateEntity(TransformComponent& component);
		Entity CreateEntity(TransformComponent& component, std::string& name);

		void DeleteEntity(Entity& entity);

		template<class T>
		T& AddComponent(const Entity& entity, T& component)
		{
			return m_Registry.AddComponent<T>(entity.GetId(), component);
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
		std::vector<T>& GetComponents()
		{
			return m_Registry.GetComponents<T>();
		}

		template<class T>
		ComponentDataContainer<T>& GetComponentContainer()
		{
			return m_Registry.GetComponentContainer<T>();
		}

		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		ComponentRegistry m_Registry;

		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	};
}



