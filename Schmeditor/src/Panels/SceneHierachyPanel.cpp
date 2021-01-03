#include "SceneHierachyPanel.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui\imgui_internal.h>

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

	template<typename T>
	static void DrawComponent(const std::string name, Entity entity, std::function<void(T&)> uiFunction)
	{
		if (entity.HasComponent<T>())
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
			if (ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str()))
			{
				T& component = entity.GetComponent<T>();
				uiFunction(component);
				ImGui::TreePop();
			}

			ImGui::Text("");
		}
	}

	static void DrawVec3Control(const std::string& label, glm::ivec3& values, int resetValue = 0, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;

		ImGui::SameLine();
		ImGui::InputInt("##X", &values.x, 0);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;

		ImGui::SameLine();
		ImGui::InputInt("##Y", &values.y, 0);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;

		ImGui::SameLine();
		ImGui::InputInt("##Z", &values.z, 0);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	static void DrawVec2Control(const std::string& label, glm::ivec2& values, int resetValue = 0, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;

		ImGui::SameLine();
		ImGui::InputInt("##X", &values.x, 0);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;

		ImGui::SameLine();
		ImGui::InputInt("##Y", &values.y, 0);
		ImGui::PopItemWidth();
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	static void DrawIntControl(const std::string& label, int& value, int resetValue = 0, int step = 0, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		ImGui::InputInt("##X", &value, step);
		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void SceneHierachyPanel::DrawComponents(Entity entity)
	{
		DrawComponent<TagComponent>("Tag", entity, [&](TagComponent& component)
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

		DrawComponent<TransformComponent>("Transform", entity, [&](TransformComponent& component)
			{
				auto& trans = component;
				DrawVec3Control("Translation", trans.Position);
				DrawVec2Control("Scale", trans.Scale, 1);
				DrawIntControl("Rotation", trans.RotationDeg, 0, 500);
			}
		);

		DrawComponent<SpriteRendererComponent>("Drawing", entity, [&](SpriteRendererComponent& component)
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

		DrawComponent<CameraComponent>("Drawing", entity, [&](CameraComponent& component)
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


