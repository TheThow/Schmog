#pragma once
#include <cstdint>

class RGBa
{
public:

	RGBa(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
		: r(r), g(g), b(b), a(alpha)
	{

	}

	uint32_t GetHex() const
	{
		return (r << 24) | (g << 16) | (b << 8) | a;
	}

	RGBa Interpolate(RGBa other, float ratio)
	{
		return RGBa(ratio * r + (1-ratio) * other.r, 
					ratio * g + (1-ratio) * other.g, 
					ratio * b + (1-ratio) * other.b, 
					ratio * a + (1-ratio) * other.a);
	}

public:
	uint32_t r, g, b, a;
};
