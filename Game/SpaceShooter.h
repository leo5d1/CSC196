#pragma once
#include "Framework/Game.h"

namespace c14
{
	class Font;
	class Text;
}

class SpaceShooter : public c14::Game
{
public:
	SpaceShooter() = default;
	~SpaceShooter() = default;

	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(c14::Renderer& renderer) override;

private:
	float m_spawnTimer = 0;

	bool m_bossSpawned = false;

	std::unique_ptr<c14::Font> m_font;
	std::unique_ptr<c14::Text> m_titleText;
	std::unique_ptr<c14::Text> m_scoreText;
};