#pragma once
#include <Schmog\Game\SceneCamera.h>


namespace Schmog {

	struct CameraComponent
	{
		SceneCamera Camera;
		static SceneCamera* MainCamera;

		CameraComponent() {
			if (MainCamera == nullptr)
			{
				MainCamera = &Camera;
			}
		}

		~CameraComponent() {
			if (MainCamera == &Camera) 
			{
				MainCamera = nullptr;
			}
		}

		bool IsMain()
		{
			return MainCamera != nullptr && MainCamera == &Camera;
		}

		void SetMain()
		{
			MainCamera = &Camera;
		}
	};

}