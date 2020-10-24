#include "sgpch.h"
#include "Entity.h"

namespace Schmog {

	Entity::Entity(Scene* scene, uint32_t id)
	{
		m_Id = id;
		m_Scene = scene;
	}

	uint32_t Entity::GetId() const
	{
		return m_Id;
	}
}