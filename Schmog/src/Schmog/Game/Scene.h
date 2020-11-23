#pragma once
#include <typeindex>

#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/TagComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "ComponentDataContainer.h"

namespace Schmog {

	class Entity;

	class Scene
	{
	public:
		Scene();

		Entity CreateEntity();
		Entity CreateEntity(std::string& name);
		Entity CreateEntity(TransformComponent& component);
		Entity CreateEntity(TransformComponent& component, std::string& name);

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
		Entity GetEntityByIndex(uint32_t index)
		{
			return Entity(this, static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->GetIdByIndex(index));
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
			static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)])->Remove(entity.GetId());
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
		void AddComponentIndex(const Entity& entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			m_ComponentMap[entity.GetId()] = m_ComponentMap[entity.GetId()] | (1 << idx);
		}

		template<class T>
		void RemoveComponentIndex(const Entity& entity)
		{
			auto idx = m_TypeIndex[typeid(T)];
			m_ComponentMap[entity.GetId()] = m_ComponentMap[entity.GetId()] & ~(1 << idx);
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
			{ typeid(TagComponent), &m_CameraComponentData },
			{ typeid(SpriteRendererComponent), &m_SpriteRendererComponentData },
			{ typeid(CameraComponent), &m_CameraComponentData }
		};
	};



}



