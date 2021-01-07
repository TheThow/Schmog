#pragma once

#include <typeindex>
#include <vector>
#include <tuple>
#include <unordered_map>

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

		GroupIterator(const GroupIterator& other) = default;

		GroupIterator& operator++()
		{
			uint32_t entity;
			do
			{
				m_Index++;
				if (m_First->GetSize() == m_Index)
					break;
				entity = m_First->GetIdByIndex(m_Index);
			} while (!m_Second->ContainsEntity(entity) && m_Index < m_First->GetSize()-1);
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
				if (-1 == m_Index)
					break;
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

		std::pair<FirstType&, SecondType&> operator*()
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

		~ComponentRegistry();

		uint32_t CreateEntity();
		uint32_t CreateEntity(const std::string& name);
		void DeleteEntity(uint32_t entity);
		std::vector<uint32_t> GetEntityIds();


		template<class T, typename... Args>
		T& AddComponent(const uint32_t entity, Args&&... args)
		{
			if (m_Data.find(typeid(T)) == m_Data.end())
			{
				ComponentDataContainer<T>* container = new ComponentDataContainer<T>{ MAX_ENTITY_COUNT };
				m_Data.emplace(typeid(T), (IDataContainer*)container);
			}
			return static_cast<ComponentDataContainer<T>*>(m_Data[typeid(T)])->Add(entity, std::forward<Args>(args)...);
		}

		template<class T>
		T& GetComponent(const uint32_t entity)
		{
			return static_cast<ComponentDataContainer<T>*>(m_Data[typeid(T)])->Get(entity);
		}

		template<class T>
		uint32_t GetEntityByIndex(uint32_t index)
		{
			return static_cast<ComponentDataContainer<T>*>(m_Data[typeid(T)])->GetIdByIndex(index);
		}

		template<class T>
		bool HasComponent(const uint32_t entity)
		{
			if (m_Data.find(typeid(T)) == m_Data.end())
				return false;

			return static_cast<ComponentDataContainer<T>*>(m_Data[typeid(T)])->ContainsEntity(entity);
		}

		template<class T>
		void RemoveComponent(const uint32_t entity)
		{
			static_cast<ComponentDataContainer<T>*>(m_Data[typeid(T)])->Remove(entity);
		}

		template<class T>
		ComponentDataContainer<T>& GetComponents()
		{
			return *static_cast<ComponentDataContainer<T>*>(m_Data[typeid(T)]);
		}

		template<class T, class U>
		ContainerGroup<T, U> Group()
		{
			ComponentDataContainer<T>* first = static_cast<ComponentDataContainer<T>*>(m_Data[typeid(T)]);
			ComponentDataContainer<U>* second = static_cast<ComponentDataContainer<U>*>(m_Data[typeid(U)]);
			return ContainerGroup<T, U>(first, second);
		}

		bool EntityExists(uint32_t id)
		{
			return m_EntityIds[id];
		}

	private:
		static const uint32_t MAX_ENTITY_COUNT = 5000;

		std::vector<bool> m_EntityIds;
		std::vector<uint32_t> m_ExistingEntities;

		std::unordered_map<std::type_index, IDataContainer*> m_Data;
	};
}