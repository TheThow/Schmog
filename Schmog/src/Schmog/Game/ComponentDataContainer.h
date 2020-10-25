#pragma once


namespace Schmog {

	template<typename T>
	class ComponentDataContainer
	{
	public:
		ComponentDataContainer(uint32_t size)
		{
			m_Data.resize(size);
		}

		T& Get(uint32_t id)
		{
			return m_Data[m_EntityToIndex[id]];
		}

		T& GetByIndex(uint32_t index)
		{
			return m_Data[index];
		}

		uint32_t GetIdByIndex(uint32_t index)
		{
			SG_ASSERT(m_IndexToEntity.find(index) != m_IndexToEntity.end(), "Invalid index")
			return m_IndexToEntity[index];
		}

		std::vector<T>& GetData()
		{
			return m_Data;
		}


		T& Add(uint32_t id, T& component)
		{
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

			if (m_EntityToIndex.find(id) == m_EntityToIndex.end())
				return;

			uint32_t delIndex = m_EntityToIndex[id];
			m_Data[delIndex] = std::move(m_Data[m_Index - 1]);
			m_IndexToEntity[delIndex] = m_IndexToEntity[m_Index - 1];
			m_EntityToIndex[m_IndexToEntity[delIndex]] = delIndex;

			m_IndexToEntity.erase(m_Index - 1);
			m_EntityToIndex.erase(id);

			m_Index--;
		}

	private:
		std::vector<T> m_Data;
		std::unordered_map<uint32_t, uint32_t> m_EntityToIndex;
		std::unordered_map<uint32_t, uint32_t> m_IndexToEntity;

		uint32_t m_Index = 0;
	};

}