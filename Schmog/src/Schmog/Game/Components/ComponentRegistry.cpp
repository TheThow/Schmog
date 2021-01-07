#include "sgpch.h"

#include "ComponentRegistry.h"


namespace Schmog {

	ComponentRegistry::ComponentRegistry()
	{
		m_EntityIds.resize(MAX_ENTITY_COUNT);
	}

	ComponentRegistry::~ComponentRegistry()
	{
		for (auto& container : m_Data)
		{
			delete container.second;
		}
	}

	uint32_t ComponentRegistry::CreateEntity()
	{
		return CreateEntity("Entity");
	}

	uint32_t ComponentRegistry::CreateEntity(const std::string& name)
	{
		uint32_t index = -1;
		for (auto it = std::begin(m_EntityIds); it != std::end(m_EntityIds); ++it)
		{
			if (!*it)
			{
				index = it - std::begin(m_EntityIds);
				break;
			}
		}

		SG_ASSERT(index != -1, "Max entities reached")

		m_EntityIds[index] = true;
		m_ExistingEntities.push_back(index);
		return index;
	}

	void ComponentRegistry::DeleteEntity(uint32_t entity)
	{
		m_EntityIds[entity] = false;

		for (auto& container : m_Data)
		{
			container.second->Remove(entity);
		}

		m_ExistingEntities.erase(std::remove(m_ExistingEntities.begin(), m_ExistingEntities.end(), entity), m_ExistingEntities.end());
	}

	std::vector<uint32_t> ComponentRegistry::GetEntityIds()
	{
		return m_ExistingEntities;
	}
}