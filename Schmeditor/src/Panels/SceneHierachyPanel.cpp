#include "SceneHierachyPanel.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>

#include "UiHelper.h"

namespace Schmog {

	void SceneHierachyPanel::SetContext(const std::shared_ptr<Scene> context)
	{
		m_SelectionContext = {};
		m_Context = context;
	}

	void SceneHierachyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene");

		for (uint32_t entityId : m_Context->GetEntities())
		{
			DrawEntityNode(Entity(m_Context.get(), entityId));
		}

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
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
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
			m_Context->DeleteEntity(entity);
		}	
	}

	void SceneHierachyPanel::DrawComponents(Entity entity)
	{
		
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag.c_str());
		if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
		{
			tag = std::string(buffer);
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				if (!m_SelectionContext.HasComponent<CameraComponent>())
					m_SelectionContext.AddComponent<CameraComponent>();
				else
					SG_CORE_WARN("This entity already has the Camera Component!");
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				if (!m_SelectionContext.HasComponent<SpriteRendererComponent>())
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
				else
					SG_CORE_WARN("This entity already has the Sprite Renderer Component!");
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();
		ImGui::Text("");

		UiHelper::DrawComponent<TransformComponent>("Transform", entity, [&](TransformComponent& component)
			{
				auto& trans = component;
				UiHelper::DrawVec3Control("Translation", trans.Position);
				UiHelper::DrawVec2Control("Scale", trans.Scale, 1);
				UiHelper::DrawIntControl("Rotation", trans.RotationDeg, 0, 50);
			}
		);

		UiHelper::DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [&](SpriteRendererComponent& component)
			{
				auto& sprite = component;
				float color[4];
				color[0] = (float)sprite.Color.rgba[0] / 255.f;
				color[1] = (float)sprite.Color.rgba[1] / 255.f;
				color[2] = (float)sprite.Color.rgba[2] / 255.f;
				color[3] = (float)sprite.Color.rgba[3] / 255.f;

				UiHelper::DrawColor4Control("Color", &color[0]);
				sprite.Color = RGBa(color);
			}
		);

		UiHelper::DrawComponent<CameraComponent>("Camera", entity, [&](CameraComponent& component)
			{
				auto& cam = component;

				const char* typeStrings[] = { "Orthographic", "Perspective" };
				const char* currentProjection = typeStrings[(int)cam.Camera.GetProjectionType()];
				if (ImGui::BeginCombo("##Projection", currentProjection))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjection == typeStrings[i];
						if (ImGui::Selectable(typeStrings[i], isSelected))
						{
							currentProjection = typeStrings[i];
							cam.Camera.SetProjectionType((SceneCamera::CameraProjectionType) i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				UiHelper::DrawCheckBox("Main Camera", cam.IsMain(), [&](bool val) { if (val) cam.SetMain(); });

				if (cam.Camera.GetProjectionType() == SceneCamera::CameraProjectionType::Orthographic)
				{
					UiHelper::DrawDragFloat("Size", cam.Camera.GetOrthographicSize(), [&](float val) { cam.Camera.SetOrthographicSize(val); });
					UiHelper::DrawDragFloat("Near Clip", cam.Camera.GetNearClip(), [&](float val) { cam.Camera.SetNearClip(val); });
					UiHelper::DrawDragFloat("Far Clip", cam.Camera.GetFarClip(), [&](float val) { cam.Camera.SetFarClip(val); });
				}

				if (cam.Camera.GetProjectionType() == SceneCamera::CameraProjectionType::Perspective)
				{
					UiHelper::DrawDragFloat("FOV", cam.Camera.GetPerspectiveVerticalFOV(), [&](float val) { cam.Camera.SetPerspectiveVerticalFOV(val); });
					UiHelper::DrawDragFloat("Near Clip", cam.Camera.GetPerspectiveNearClip(), [&](float val) { cam.Camera.SetPerspectiveNearClip(val); });
					UiHelper::DrawDragFloat("Far Clip", cam.Camera.GetPerspectiveFarClip(), [&](float val) { cam.Camera.SetPerspectiveFarClip(val); });
				}
			}
		);
	}
}


