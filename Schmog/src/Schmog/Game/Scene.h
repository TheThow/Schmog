#pragma once
#include <typeindex>

#include "Components/TransformComponent.h"
#include "ComponentDataContainer.h"

namespace Schmog {

	class Entity;

	class Scene
	{
	public:
		Scene();

		Entity CreateEntity();
		Entity CreateEntity(TransformComponent& component);

		void DeleteEntity(Entity& entity);

		template<class T>
		T& AddComponent(const Entity& entity, T& component)
		{
			AddComponentIndex<T>(entity);
			return static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->Add(entity.GetId(), component);
		}

		template<class T>
		T& GetComponent(const Entity& entity)
		{
			return static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->Get(entity.GetId());
		}

		template<class T>
		bool HasComponent(const Entity& entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			return m_ComponentMap[entity.GetId()] & (1 << idx);
		}

		template<class T>
		void RemoveComponent(const Entity& entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->Remove(entity.GetId());
			m_ComponentMap[entity.GetId()] = m_ComponentMap[entity.GetId()] & ~(1 << idx);
		}

	private:
		template<class T>
		void AddComponentIndex(const Entity& entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			m_ComponentMap[entity.GetId()] = m_ComponentMap[entity.GetId()] | (1 << idx);
		}

	private:
		static const uint32_t s_MaxEntityCount = 5000;
		uint32_t m_EntityCount = 0;

		ComponentDataContainer<TransformComponent> m_TransformComponentData{ s_MaxEntityCount };

		std::unordered_map<uint32_t, uint32_t> m_ComponentMap;

		std::unordered_map<std::type_index, uint32_t> m_TypeIndex =
		{
			{ typeid(TransformComponent), 0 }
		};

		std::unordered_map<std::type_index, void*> m_TypeStorage = 
		{
			{ typeid(TransformComponent), &m_TransformComponentData }
		};
	};



}



