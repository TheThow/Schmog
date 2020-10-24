#include "sgpch.h"
#include "Entity.h"
#include "Scene.h"

namespace Schmog {

	Scene::Scene()
	{

	}

	Entity Scene::CreateEntity()
	{
		return CreateEntity(TransformComponent());
	}

	Entity Scene::CreateEntity(TransformComponent& component)
	{
		Entity entity = Entity(this, m_EntityCount);
		AddComponent(entity, component);
		m_EntityCount++;
		return entity;
	}

	void Scene::DeleteEntity(Entity& entity)
	{
		RemoveComponent<TransformComponent>(entity);
	}

}