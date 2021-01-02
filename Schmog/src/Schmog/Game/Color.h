#pragma once
#include <cstdint>

struct RGBa
{
	uint8_t rgba[4];

	RGBa()
	{
		rgba[0] = 255;
		rgba[1] = 255;
		rgba[2] = 255;
		rgba[3] = 255;
	}

	RGBa(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		rgba[0] = r;
		rgba[1] = g;
		rgba[2] = b;
		rgba[3] = a;
	}

	RGBa(int color[4])
	{
		rgba[0] = ColorConvert(color[0]);
		rgba[1] = ColorConvert(color[1]);
		rgba[2] = ColorConvert(color[2]);
		rgba[3] = ColorConvert(color[3]);
	}


	RGBa Interpolate(RGBa other, float ratio)
	{
		return RGBa(static_cast<uint8_t>(ratio * rgba[0] + (1 - ratio) * other.rgba[0]), 
					static_cast<uint8_t>(ratio * rgba[1] + (1 - ratio) * other.rgba[1]),
					static_cast<uint8_t>(ratio * rgba[2] + (1 - ratio) * other.rgba[2]),
					static_cast<uint8_t>(ratio * rgba[3] + (1 - ratio) * other.rgba[3]));
	}

	RGBa(const RGBa& other) 
	{ 
		rgba[0] = other.rgba[0];
		rgba[1] = other.rgba[1];
		rgba[2] = other.rgba[2];
		rgba[3] = other.rgba[3];
	} 
	
	uint8_t ColorConvert(int val)
	{
		return (uint8_t)std::max(std::min(255, val), 0);
	}
};
