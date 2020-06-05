#pragma once

#include <string>

#include "Schmog/Core/Core.h"


namespace Schmog {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;
		static std::shared_ptr<Texture2D> Create(const std::string& path);
	};

}



