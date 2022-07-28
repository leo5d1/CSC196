#pragma once
#include <cstdint>

namespace c14
{
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);

		std::string r = line.substr(line.find("{") + 1, line.find(",") - line.find(",") - 1);
		color.r = (uint8_t)(std::stof(r) * 255);
		std::string g = line.substr(line.find(",") + 1, line.find(",") - line.find(",") - 1);
		color.g = (uint8_t)(std::stof(g) * 255);
		std::string b = line.substr(line.find(",") + 1, line.find(",") - line.find("{") - 1);
		color.b = (uint8_t)(std::stof(b) * 255);
		color.a = 255;

		return stream;
	}


}