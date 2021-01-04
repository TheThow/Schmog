#pragma once

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui\imgui_internal.h>

#include "Schmog.h"

namespace Schmog {

	namespace UiHelper {
		template<typename T>
		static void DrawComponent(const std::string name, Entity entity, std::function<void(T&)> uiFunction)
		{
			if (entity.HasComponent<T>())
			{
				ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });

				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen 
					| ImGuiTreeNodeFlags_AllowItemOverlap 
					| ImGuiTreeNodeFlags_Framed 
					| ImGuiTreeNodeFlags_SpanAvailWidth
					| ImGuiTreeNodeFlags_FramePadding;
				auto open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str());
				ImGui::PopStyleVar();

				bool removeComponent = false;
				if (typeid(T) != typeid(TagComponent) && typeid(T) != typeid(TransformComponent))
				{
					ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
					if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
					{
						ImGui::OpenPopup("ComponentSettings");
					}

					if (ImGui::BeginPopup("ComponentSettings"))
					{
						if (ImGui::MenuItem("Remove component"))
							removeComponent = true;

						ImGui::EndPopup();
					}
				}

				if (open)
				{
					T& component = entity.GetComponent<T>();
					uiFunction(component);
					ImGui::TreePop();
				}

				if (removeComponent)
					entity.RemoveComponent<T>();

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

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
				values.x = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::InputInt("##X", &values.x, 0);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
				values.y = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::InputInt("##Y", &values.y, 0);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
			if (ImGui::Button("Z", buttonSize))
				values.z = resetValue;
			ImGui::PopStyleColor(3);

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

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
				values.x = resetValue;
			ImGui::PopStyleColor(3);

			ImGui::SameLine();
			ImGui::InputInt("##X", &values.x, 0);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
				values.y = resetValue;
			ImGui::PopStyleColor(3);

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

		static void DrawColor4Control(const std::string& label, float* value, float columnWidth = 100.0f)
		{
			ImGui::PushID(label.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, columnWidth);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			ImGui::ColorEdit4("##Color", value);
			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
		}

		static void DrawDragFloat(const std::string& label, float value, std::function<void(float)> callback, float columnWidth = 100.0f)
		{
			ImGui::PushID(label.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, columnWidth);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			float changeval = value;
			if (ImGui::DragFloat("##val", &changeval))
				callback(changeval);
			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
		}

		static void DrawCheckBox(const std::string& label, bool value, std::function<void(bool)> callback, float columnWidth = 100.0f)
		{
			ImGui::PushID(label.c_str());

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, columnWidth);
			ImGui::Text(label.c_str());
			ImGui::NextColumn();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			bool checked = value;
			if (ImGui::Checkbox("##val", &checked))
				callback(checked);
			ImGui::PopStyleVar();

			ImGui::Columns(1);

			ImGui::PopID();
		}
	}

}