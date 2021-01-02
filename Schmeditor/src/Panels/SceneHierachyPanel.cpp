#include "SceneHierachyPanel.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>

namespace Schmog {

	void SceneHierachyPanel::SetContext(const std::shared_ptr<Scene> context)
	{
		m_Context = context;
	}

	void SceneHierachyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierachy Panel");

		for (uint32_t entityId : m_Context->GetEntities())
		{
			DrawEntityNode(Entity(m_Context.get(), entityId));
		}

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}
		ImGui::End();
	}

	void SceneHierachyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Name;
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

	void SceneHierachyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Name;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			ImGui::Text("Tag");
			ImGui::SameLine();
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::Text("");

		if (entity.HasComponent<TransformComponent>())
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), flags, "Transform"))
			{
				auto& trans = entity.GetComponent<TransformComponent>();
				ImGui::Text("Translation");
				ImGui::InputFloat3("##Translation", &(trans.Position.x), 2);
				ImGui::Text("Rotation");
				ImGui::InputFloat("##Rotation", &(trans.Rotation), 0.1, 0.2, 2);
				ImGui::Text("Scale");
				ImGui::InputFloat2("##Scale", &(trans.Scale.x), 2);
				ImGui::TreePop();
			}
		}

		ImGui::Text("");

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
			if (ImGui::TreeNodeEx((void*)(uint64_t)typeid(SpriteRendererComponent).hash_code(), flags, "Render"))
			{
				auto& sprite = entity.GetComponent<SpriteRendererComponent>();
				ImGui::Text("Color");
				int color[4];
				color[0] = sprite.Color.rgba[0];
				color[1] = sprite.Color.rgba[1];
				color[2] = sprite.Color.rgba[2];
				color[3] = sprite.Color.rgba[3];

				ImGui::InputInt4("##Color", &color[0]);
				sprite.Color = RGBa(color);

				ImGui::TreePop();
			}
		}
	}

	uint8_t ColorConvert(int val)
	{
		return (uint8_t)std::max(std::min(255, val), 0);
	}
}


