#pragma once

#include <typeindex>
#include <vector>
#include <tuple>

#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/TagComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "ComponentDataContainer.h"

namespace Schmog {

	template<typename ContainerGroup>
	class GroupIterator
	{
	public:
		using FirstType = typename ContainerGroup::FirstType;
		using SecondType = typename ContainerGroup::SecondType;

	public:
		GroupIterator(ComponentDataContainer<FirstType>* first, ComponentDataContainer<SecondType>* second, uint32_t index)
		{
			m_First = first;
			m_Second = second;
			m_Index = index;
		}

		GroupIterator& operator++()
		{
			uint32_t entity;
			do
			{
				m_Index++;
				entity = m_First->GetIdByIndex(m_Index);
			} while (!m_Second->ContainsEntity(entity));
			return *this;
		}

		GroupIterator& operator++(int)
		{
			GroupIterator it = *this;
			++(*this);
			return it;
		}

		GroupIterator& operator--()
		{
			uint32_t entity;
			do
			{
				m_Index--;
				entity = m_First->GetIdByIndex(m_Index);
			} while (!m_Second->ContainsEntity(entity) && m_Index >= 0);
			return *this;
		}

		GroupIterator& operator--(int)
		{
			GroupIterator it = *this;
			--(*this);
			return it;
		}

		std::pair<FirstType&, SecondType&>& operator*()
		{
			FirstType& first = (*m_First).GetByIndex(m_Index);
			uint32_t entity = (*m_First).GetIdByIndex(m_Index);
			SecondType& second = (*m_Second).Get(entity);
			return std::make_pair(std::ref(first), std::ref(second));
		}

		bool operator==(const GroupIterator& other) const
		{
			return equals(other);
		}

		bool operator!=(const GroupIterator& other) const
		{
			return !equals(other);
		}

	private:
		bool equals(const GroupIterator& other) const
		{
			return m_First->GetData().begin() + m_Index == other.m_First->GetData().begin() + other.m_Index;
		}

	private:
		ComponentDataContainer<FirstType>* m_First;
		ComponentDataContainer<SecondType>* m_Second;
		uint32_t m_Index;
	};

	template <class T, class U>
	class ContainerGroup
	{
	public:
		using FirstType = T;
		using SecondType = U;
		using Iterator = GroupIterator<ContainerGroup<T, U>>;

	public:
		ContainerGroup(ComponentDataContainer<T>* first, ComponentDataContainer<U>* second)
		{
			m_First = first;
			m_Second = second;
		}

		Iterator begin() 
		{
			return Iterator(m_First, m_Second, 0);
		}

		Iterator end() 
		{
			return Iterator(m_First, m_Second, m_First->GetSize());
		}

		const Iterator begin() const
		{
			return Iterator(m_First, m_Second, 0);
		}

		const Iterator end() const
		{
			return Iterator(m_First, m_Second, m_First->GetSize());
		}


	private:
		ComponentDataContainer<T>* m_First;
		ComponentDataContainer<U>* m_Second;
	};

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
		ComponentDataContainer<T>& GetComponents()
		{
			return *static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)]);
		}

		template<class T, class U>
		ContainerGroup<T, U> Group()
		{
			ComponentDataContainer<T>* first = static_cast<ComponentDataContainer<T>*>(m_TypeStorage[typeid(T)]);
			ComponentDataContainer<U>* second = static_cast<ComponentDataContainer<U>*>(m_TypeStorage[typeid(U)]);
			return ContainerGroup<T, U>(first, second);
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