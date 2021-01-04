#include "SceneHierachyPanel.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>

#include "UiHelper.h"

namespace Schmog {

	void SceneHierachyPanel::SetContext(const std::shared_ptr<Scene> context)
	{
		m_Context = context;
	}

	void SceneHierachyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene");

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
		UiHelper::DrawComponent<TagComponent>("Tag", entity, [&](TagComponent& component)
			{
				auto& tag = component.Name;
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), tag.c_str());
				if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
				{
					tag = std::string(buffer);
				}
			}
		);

		UiHelper::DrawComponent<TransformComponent>("Transform", entity, [&](TransformComponent& component)
			{
				auto& trans = component;
				UiHelper::DrawVec3Control("Translation", trans.Position);
				UiHelper::DrawVec2Control("Scale", trans.Scale, 1);
				UiHelper::DrawIntControl("Rotation", trans.RotationDeg, 0, 500);
			}
		);

		UiHelper::DrawComponent<SpriteRendererComponent>("Drawing", entity, [&](SpriteRendererComponent& component)
			{
				auto& sprite = component;
				float color[4];
				color[0] = (float)sprite.Color.rgba[0] / 255.f;
				color[1] = (float)sprite.Color.rgba[1] / 255.f;
				color[2] = (float)sprite.Color.rgba[2] / 255.f;
				color[3] = (float)sprite.Color.rgba[3] / 255.f;

				ImGui::ColorEdit4("Color", &color[0]);
				sprite.Color = RGBa(color);
			}
		);

		UiHelper::DrawComponent<CameraComponent>("Drawing", entity, [&](CameraComponent& component)
			{
				auto& cam = component;

				const char* typeStrings[] = { "Orthographic", "Perspective" };
				const char* currentProjection = typeStrings[(int)cam.Camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currentProjection))
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

				bool isMain = cam.IsMain();
				if (ImGui::Checkbox("Main Camera", &isMain))
				{
					if (isMain)
						cam.SetMain();
				}

				if (cam.Camera.GetProjectionType() == SceneCamera::CameraProjectionType::Orthographic)
				{
					float orthoSize = cam.Camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						cam.Camera.SetOrthographicSize(orthoSize);

					float nearClip = cam.Camera.GetNearClip();
					if (ImGui::DragFloat("Near Clip", &nearClip))
						cam.Camera.SetNearClip(nearClip);

					float farClip = cam.Camera.GetFarClip();
					if (ImGui::DragFloat("Far Clip", &farClip))
						cam.Camera.SetFarClip(farClip);
				}

				if (cam.Camera.GetProjectionType() == SceneCamera::CameraProjectionType::Perspective)
				{
					float perspectiveVerticalFov = glm::degrees(cam.Camera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
						cam.Camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

					float perspectiveNear = cam.Camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						cam.Camera.SetPerspectiveNearClip(perspectiveNear);

					float perspectiveFar = cam.Camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						cam.Camera.SetPerspectiveFarClip(perspectiveFar);
				}
			}
		);
	}
}


