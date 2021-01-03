#include "sgpch.h"
#include "Entity.h"
#include "Scene.h"
#include "Schmog/Renderer/Renderer2D.h"

namespace Schmog {

	Entity Scene::CreateEntity()
	{
		return CreateEntity("Entity");
	}

	Entity Scene::CreateEntity(const std::string& name)
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
		//Scripts
		uint32_t idx = 0;
		for (auto& script : m_Registry.GetComponents<NativeScriptingComponent>())
		{
			if (script.Instance == nullptr)
			{
				script.InstantiateFunction();
				script.Instance->m_Entity = std::shared_ptr<Entity>(new Entity(this, m_Registry.GetEntityByIndex<NativeScriptingComponent>(idx)));
				script.Instance->OnCreate();
			}
			script.Instance->OnUpdate();
			idx++;
		}

		// Rendering
		CameraComponent mainCamera;
		TransformComponent mainCameraTransform;
		for (auto& [cam, transform] : m_Registry.Group<CameraComponent, TransformComponent>())
		{
			if (cam.IsMain())
			{
				mainCamera = cam;
				mainCameraTransform = transform;
			}
		}

		Renderer2D::BeginScene(mainCamera.Camera.GetProjection(), mainCameraTransform);

		for (auto& [sprite, transform] : m_Registry.Group<SpriteRendererComponent, TransformComponent>())
		{
			Renderer2D::DrawQuad(transform, sprite);
		}

		Renderer2D::EndScene();
	}

	std::vector<uint32_t> Scene::GetEntities()
	{
		return m_Registry.GetEntityIds();
	}

	bool Scene::EntityExists(const Entity& entity)
	{
		return m_Registry.EntityExists(entity.GetId());
	}
}