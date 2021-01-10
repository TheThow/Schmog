#include "sgpch.h"

#include <fstream>

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
		auto& entity = Entity(this, m_Registry.CreateEntity(name));
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);
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

		for (auto& entity : m_Registry.GetComponents<CameraComponent>())
		{
			entity.Camera.SetViewportSize(width, height);
		}
	}

	void Scene::OnUpdateEditor(EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera.GetViewProjection());

		for (auto& [sprite, transform] : m_Registry.Group<SpriteRendererComponent, TransformComponent>())
		{
			Renderer2D::DrawQuad(transform, sprite);
		}

		Renderer2D::EndScene();
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

	void Scene::Serialize(const std::string& filename)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for (auto entity : m_Registry.GetEntityIds())
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Entity" << YAML::Value << entity;

			if (m_Registry.HasComponent<TagComponent>(entity))
				m_Registry.GetComponent<TagComponent>(entity).Serialize(out);

			if (m_Registry.HasComponent<TransformComponent>(entity))
				m_Registry.GetComponent<TransformComponent>(entity).Serialize(out);

			if (m_Registry.HasComponent<SpriteRendererComponent>(entity))
				m_Registry.GetComponent<SpriteRendererComponent>(entity).Serialize(out);

			if (m_Registry.HasComponent<NativeScriptingComponent>(entity))
				m_Registry.GetComponent<NativeScriptingComponent>(entity).Serialize(out);

			if (m_Registry.HasComponent<CameraComponent>(entity))
				m_Registry.GetComponent<CameraComponent>(entity).Serialize(out);

			out << YAML::EndMap;
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filename);
		fout << out.c_str();
	}

	void Scene::Deserialize(const std::string& filename)
	{
		YAML::Node data = YAML::LoadFile(filename);

		std::string sceneName = data["Scene"].as<std::string>();
		SG_CORE_INFO("Deserializing scene '{0}'", sceneName);

		YAML::Node entities = data["Entities"];

		for (auto& serializedEntity : entities)
		{
			Entity entity = CreateEntity();

			auto component = serializedEntity[TagComponent::GetSerializationName()];
			if (component)
				entity.GetComponent<TagComponent>().Deserialize(component);

			component = serializedEntity[TransformComponent::GetSerializationName()];
			if (component)
				entity.GetComponent<TransformComponent>().Deserialize(component);

			component = serializedEntity[SpriteRendererComponent::GetSerializationName()];
			if (component)
				entity.AddComponent<SpriteRendererComponent>().Deserialize(component);

			component = serializedEntity[CameraComponent::GetSerializationName()];
			if (component)
				entity.AddComponent<CameraComponent>().Deserialize(component);
		}
	}

	bool Scene::EntityExists(const Entity& entity)
	{
		return m_Registry.EntityExists(entity.GetId());
	}
}