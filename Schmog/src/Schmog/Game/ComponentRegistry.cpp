#include "sgpch.h"

#include "ComponentRegistry.h"
#include <algorithm>

namespace Schmog {

	ComponentRegistry::ComponentRegistry()
	{
		m_EntityIds.resize(MAX_ENTITY_COUNT);
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

		AddComponent<TransformComponent>(index);
		AddComponent<TagComponent>(index, name);
		m_EntityIds[index] = true;
		m_ExistingEntities.push_back(index);
		return index;
	}

	void ComponentRegistry::DeleteEntity(uint32_t entity)
	{
		m_EntityIds[entity] = false;
		RemoveComponent<TransformComponent>(entity);
		RemoveComponent<TagComponent>(entity);
		RemoveComponent<CameraComponent>(entity);
		RemoveComponent<NativeScriptingComponent>(entity);
		RemoveComponent<SpriteRendererComponent>(entity);
		m_ExistingEntities.erase(std::remove(m_ExistingEntities.begin(), m_ExistingEntities.end(), entity), m_ExistingEntities.end());
	}

	std::vector<uint32_t> ComponentRegistry::GetEntityIds()
	{
		return m_ExistingEntities;
	}
}