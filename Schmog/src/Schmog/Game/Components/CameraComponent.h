#pragma once
#include "Schmog\Game\SceneCamera.h"
#include "IComponent.h"


namespace Schmog {

	struct CameraComponent : public IComponent
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

		void Serialize(YAML::Emitter& out) override
		{
			out << YAML::Key << GetSerializationName();
			out << YAML::BeginMap;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)Camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << Camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << Camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << Camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << Camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << Camera.GetNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << Camera.GetFarClip();

			out << YAML::Key << "Main" << YAML::Value << IsMain();
			out << YAML::EndMap; // Camera

			out << YAML::EndMap;
		}

		void Deserialize(const YAML::Node& data) override
		{
			auto& cameraProps = data["Camera"];
			Camera.SetProjectionType((SceneCamera::CameraProjectionType)cameraProps["ProjectionType"].as<int>());

			Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
			Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
			Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

			Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
			Camera.SetNearClip(cameraProps["OrthographicNear"].as<float>());
			Camera.SetFarClip(cameraProps["OrthographicFar"].as<float>());

			if (cameraProps["Main"].as<bool>())
				MainCamera = &Camera;
		}

		static std::string GetSerializationName()
		{
			return "CameraComponent";
		}
	};

}