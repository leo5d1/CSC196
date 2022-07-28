#pragma once
#include "Renderer.h"
#include <vector>
#include <string>

namespace c14
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<c14::Vector2>& points, const c14::Color& color) :
			m_points{points},
			m_color{color}
		{}
		Model(const std::string& filename);

		void Draw(Renderer& renderer, const Vector2& position, float angle, float scale = 1);

		void Load(const std::string& filename);
		float CalculateRadius();

		float GetRadius() { return m_radius; }

	private:
		c14::Color m_color;
		std::vector<c14::Vector2> m_points;

		float m_radius = 0;
	};
}