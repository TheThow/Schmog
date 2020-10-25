#include "sgpch.h"
#include "Entity.h"
#include "Scene.h"

namespace Schmog {

	Scene::Scene()
	{
		m_EntityIds.resize(MAX_ENTITY_COUNT);
	}

	Entity Scene::CreateEntity()
	{
		return CreateEntity(TransformComponent());
	}

	Entity Scene::CreateEntity(TransformComponent& component)
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

		Entity entity = Entity(this, index);
		AddComponent(entity, component);
		m_EntityIds[index] = true;
		return entity;
	}

	void Scene::DeleteEntity(Entity& entity)
	{
		m_EntityIds[entity.GetId()] = false;
		RemoveComponent<TransformComponent>(entity);
	}

}