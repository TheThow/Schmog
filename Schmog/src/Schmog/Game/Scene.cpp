#include "sgpch.h"
#include "Entity.h"
#include "Scene.h"

namespace Schmog {


	Entity Scene::CreateEntity()
	{
		return CreateEntity(TransformComponent());
	}

	Entity Scene::CreateEntity(std::string& name)
	{
		return CreateEntity(TransformComponent(), name);
	}

	Entity Scene::CreateEntity(TransformComponent& component)
	{
		return CreateEntity(component, std::string("Entity"));
	}

	Entity Scene::CreateEntity(TransformComponent& component, std::string& name)
	{
		Entity entity = Entity(this, m_Registry.CreateEntity(component, name));
		return entity;
	}

	void Scene::DeleteEntity(Entity& entity)
	{
		m_Registry.DeleteEntity(entity.GetId());
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto cameras = m_Registry.GetComponents<CameraComponent>();
		for (auto entity : cameras)
		{
			entity.Camera.SetViewportSize(width, height);
		}

	}

}