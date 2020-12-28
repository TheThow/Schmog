#pragma once

#include <stdint.h>
#include <vector>


namespace Schmog {

	template<typename T>
	class ComponentDataContainer
	{
	public:
		ComponentDataContainer(uint32_t size)
		{
			m_Data.resize(size);
			m_EntityToIndex.resize(size, INVALID_VALUE);
			m_IndexToEntity.resize(size, INVALID_VALUE);
		}

		bool ContainsEntity(uint32_t id)
		{
			return m_EntityToIndex[id] != INVALID_VALUE;
		}

		T& Get(uint32_t id)
		{
			SG_ASSERT(m_EntityToIndex[id] != INVALID_VALUE, "Index invalid")
			return m_Data[m_EntityToIndex[id]];
		}

		T& GetByIndex(uint32_t index)
		{
			return m_Data[index];
		}

		uint32_t GetIdByIndex(uint32_t index)
		{
			SG_ASSERT(m_IndexToEntity[index] != INVALID_VALUE, "Index invalid")
			return m_IndexToEntity[index];
		}

		std::vector<T>& GetData()
		{
			return m_Data;
		}

		T& Add(uint32_t id, T& component)
		{
			SG_ASSERT(id < m_Data.size(), "Index out of bounds")

			m_Data[m_Index] = component;
			m_EntityToIndex[id] = m_Index;
			m_IndexToEntity[m_Index] = id;

			m_Index++;

			return m_Data[m_Index - 1];
		}

		void Remove(uint32_t id)
		{
			if (m_Index == 0)
				return;

			if (m_EntityToIndex[id] == INVALID_VALUE)
				return;

			uint32_t delIndex = m_EntityToIndex[id];

			m_Data[delIndex] = std::move(m_Data[m_Index - 1]);
			m_IndexToEntity[delIndex] = m_IndexToEntity[m_Index - 1];
			m_EntityToIndex[m_IndexToEntity[delIndex]] = delIndex;

			m_IndexToEntity[m_Index - 1] = INVALID_VALUE;
			m_EntityToIndex[id] = INVALID_VALUE;

			m_Index--;
		}

		uint32_t GetSize() { return m_Index; }

		typename std::vector<T>::iterator begin() {
			return m_Data.begin();
		}

		typename std::vector<T>::iterator end() {
			return m_Data.begin() + m_Index;
		}

		typename std::vector<T>::const_iterator begin() const {
			return m_Data.begin();
		}

		typename std::vector<T>::const_iterator end() const {
			return m_Data.begin() + m_Index;
		}


	private:
		static const uint32_t INVALID_VALUE = UINT32_MAX;

		std::vector<T> m_Data;
		std::vector<uint32_t> m_EntityToIndex;
		std::vector<uint32_t> m_IndexToEntity;

		uint32_t m_Index = 0;
	};

}