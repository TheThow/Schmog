#pragma once

#include "IComponent.h"

namespace Schmog {

	class Entity;

	class NativeScript
	{
	public:
		virtual ~NativeScript() {};

		virtual void OnCreate() {};
		virtual void OnUpdate() {};
		virtual void OnDelete() {};

		template<typename T>
		T& GetComponent()
		{
			return m_Entity->GetComponent<T>();
		}

	protected:
		std::shared_ptr<Entity> m_Entity = nullptr;

		friend class Scene;
	};

	class NativeScriptingComponent : public IComponent
	{
	public:
		NativeScriptingComponent() = default;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { Instance.reset(new T()); };
		}

		void Serialize(YAML::Emitter& out) override
		{
		}

		void Deserialize(const YAML::Node& data) override
		{
		}

		static std::string GetSerializationName()
		{
			return "NativeScriptingComponent";
		}

	protected:
		std::function<void()> InstantiateFunction;
		std::unique_ptr<NativeScript> Instance = nullptr;

		friend class Scene;
	};
}