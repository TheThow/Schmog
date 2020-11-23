#pragma once
#include <Schmog\Game\Camera.h>


namespace Schmog {

	struct CameraComponent
	{
		Camera Camera;

		CameraComponent() = default;
		CameraComponent(const glm::mat4& projection)
			: Camera(projection) {}
	};

}