#include "sgpch.h"

#include "ComponentRegistry.h"

namespace Schmog {

	ComponentRegistry::ComponentRegistry()
	{
		m_EntityIds.resize(MAX_ENTITY_COUNT);
	}

	uint32_t ComponentRegistry::CreateEntity()
	{
		return CreateEntity(TransformComponent());
	}

	uint32_t ComponentRegistry::CreateEntity(std::string& name)
	{
		return CreateEntity(TransformComponent(), name);
	}

	uint32_t ComponentRegistry::CreateEntity(TransformComponent& component)
	{
		return CreateEntity(component, std::string("Entity"));
	}

	uint32_t ComponentRegistry::CreateEntity(TransformComponent& component, std::string& name)
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

		AddComponent(index, component);
		AddComponent(index, TagComponent(name));
		m_EntityIds[index] = true;
		return index;
	}

	void ComponentRegistry::DeleteEntity(uint32_t entity)
	{
		m_EntityIds[entity] = false;
		RemoveComponent<TransformComponent>(entity);
		RemoveComponent<SpriteRendererComponent>(entity);
	}
}