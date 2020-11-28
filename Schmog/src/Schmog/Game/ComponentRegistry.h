#pragma once

#include <typeindex>
#include <vector>

#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/TagComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "ComponentDataContainer.h"

namespace Schmog {

	class ComponentRegistry
	{
	public:

		ComponentRegistry();

		uint32_t CreateEntity();
		uint32_t CreateEntity(std::string& name);
		uint32_t CreateEntity(TransformComponent& component);
		uint32_t CreateEntity(TransformComponent& component, std::string& name);
		void DeleteEntity(uint32_t entity);


		template<class T>
		T& AddComponent(const uint32_t entity, T& component)
		{
			AddComponentIndex<T>(entity);
			return static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->Add(entity, component);
		}

		template<class T>
		T& GetComponent(const uint32_t entity)
		{
			return static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->Get(entity);
		}

		template<class T>
		uint32_t GetEntityByIndex(uint32_t index)
		{
			return Entity(this, static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->GetIdByIndex(index));
		}

		template<class T>
		bool HasComponent(const uint32_t entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			return m_ComponentMap[entity] & (1 << idx);
		}

		template<class T>
		void RemoveComponent(const uint32_t entity)
		{
			static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->Remove(entity);
			RemoveComponentIndex<T>(entity);
		}

		template<class T>
		std::vector<T>& GetComponents()
		{
			return static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->GetData();
		}

		template<class T>
		ComponentDataContainer<T>& GetComponentContainer()
		{
			return static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)]);
		}


	private:
		template<class T>
		void AddComponentIndex(const uint32_t entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			m_ComponentMap[entity] = m_ComponentMap[entity] | (1 << idx);
		}

		template<class T>
		void RemoveComponentIndex(const uint32_t entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			m_ComponentMap[entity] = m_ComponentMap[entity] & ~(1 << idx);
		}


	private:
		static const uint32_t MAX_ENTITY_COUNT = 5000;

		std::vector<bool> m_EntityIds;
		std::unordered_map<uint32_t, uint32_t> m_ComponentMap;

		ComponentDataContainer<TransformComponent> m_TransformComponentData{ MAX_ENTITY_COUNT };
		ComponentDataContainer<TagComponent> m_TagComponentData{ MAX_ENTITY_COUNT };
		ComponentDataContainer<SpriteRendererComponent> m_SpriteRendererComponentData{ MAX_ENTITY_COUNT };
		ComponentDataContainer<CameraComponent> m_CameraComponentData{ MAX_ENTITY_COUNT };

		std::unordered_map<std::type_index, uint32_t> m_TypeIndex =
		{
			{ typeid(TransformComponent), 0 },
			{ typeid(TagComponent), 1 },
			{ typeid(SpriteRendererComponent), 2 },
			{ typeid(CameraComponent), 3 }
		};

		std::unordered_map<std::type_index, void*> m_TypeStorage =
		{
			{ typeid(TransformComponent), &m_TransformComponentData },
			{ typeid(TagComponent), &m_TagComponentData },
			{ typeid(SpriteRendererComponent), &m_SpriteRendererComponentData },
			{ typeid(CameraComponent), &m_CameraComponentData }
		};

	};

}