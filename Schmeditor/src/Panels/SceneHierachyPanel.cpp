#include "SceneHierachyPanel.h"

#include <imgui/imgui.h>

void Schmog::SceneHierachyPanel::SetContext(const std::shared_ptr<Scene> context)
{
	m_Context = context;
}

void Schmog::SceneHierachyPanel::OnImGuiRender()
{
	ImGui::Begin("Scene Hierachy Panel");

	for (uint32_t entityId : m_Context->GetEntities())
	{
		DrawEntityNode(Entity(m_Context.get(), entityId));
	}

	ImGui::End();
}

void Schmog::SceneHierachyPanel::DrawEntityNode(Entity entity)
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
