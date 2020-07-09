#include "EditorLayer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

#include <iostream>


namespace Schmog {

	void ScheditorLayer::OnAttach()
	{
		FrameBufferSpec fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbSpec);
	}

	void ScheditorLayer::OnDetach()
	{
	}

	void ScheditorLayer::OnUpdate()
	{

	}

	void ScheditorLayer::OnImGuiRender()
	{

	}

	void ScheditorLayer::OnEvent(Event& e)
	{

	}
}