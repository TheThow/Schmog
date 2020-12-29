#include "sgpch.h"
#include "Entity.h"
#include "Scene.h"
#include "Schmog/Renderer/Renderer2D.h"

namespace Schmog {


	Entity Scene::CreateEntity()
	{
		return CreateEntity(std::string("Entity"));
	}

	Entity Scene::CreateEntity(std::string& name)
	{
		return Entity(this, m_Registry.CreateEntity(name));
	}

	void Scene::DeleteEntity(Entity& entity)
	{
		m_Registry.DeleteEntity(entity.GetId());
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		for (auto& entity : m_Registry.GetComponents<CameraComponent>())
		{
			entity.Camera.SetViewportSize(width, height);
		}
	}

	void Scene::OnUpdate()
	{
		auto cameras = m_Registry.GetComponents<CameraComponent>();
		CameraComponent camera = cameras.GetByIndex(0);

		Renderer2D::BeginScene(camera.Camera.GetProjection());

		auto group = m_Registry.Group<SpriteRendererComponent, TransformComponent>();
		for (auto& [sprite, transform] : group)
		{
			Renderer2D::DrawQuad(transform, sprite);
		}

		Renderer2D::EndScene();
	}

}