#include "SpaceShooter.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Engine.h"

void SpaceShooter::Initialize()
{
	m_scene = std::make_unique<c14::Scene>(this);

	//create assets
	m_font = std::make_unique<c14::Font>("Fonts/00TT.TTF", 36);

	m_titleText = std::make_unique<c14::Text>(m_font.get());
	m_titleText->Create(c14::g_renderer, "Asteroidz", { 0, 240, 200, 255 });

	m_scoreText = std::make_unique<c14::Text>(m_font.get());
	m_scoreText->Create(c14::g_renderer, "0000", { 255, 255, 255, 255 });

	// CREATE ACTOR
	// transform
	c14::Transform transform;
	transform.position = c14::Vector2{ 400, 300 };
	transform.rotation = 0;
	transform.scale = 2;

	// model
	std::unique_ptr<Player> player = std::make_unique<Player>(c14::Model{ "Player.txt" }, transform);
	m_scene->Add(std::move(player));
}

void SpaceShooter::Shutdown()
{

}

void SpaceShooter::Update()
{
	// spawn enemies (type 1)
	m_spawnTimer -= c14::g_time.deltaTime;
	if (m_spawnTimer <= 0)
	{
		c14::Transform transform;
		transform.position.x = c14::Randomf(800);
		transform.position.y = c14::Randomf(600);
		transform.rotation = c14::Randomf(math::TwoPi);
		transform.scale = 2;
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(c14::Model{ "Enemy.txt" }, transform,4.0f);
		m_scene->Add(std::move(enemy));
	}
	// spawn enemies (type 2)
	if (m_spawnTimer <= 0 && m_score >= 1000)
	{
		c14::Transform transform;
		transform.position.x = c14::Randomf(800);
		transform.position.y = c14::Randomf(600);
		transform.rotation = c14::Randomf(math::TwoPi);
		transform.scale = 2;
		std::unique_ptr<Enemy2> enemy = std::make_unique<Enemy2>(c14::Model{ "Enemy2.txt" }, transform, 10.0f);
		m_scene->Add(std::move(enemy));
	}

	// boss
	if (m_bossSpawned == false && m_score >= 3000)
	{
		c14::Transform transform;
		transform.position.x = 300;
		transform.position.y = 20;
		transform.rotation = c14::Randomf(math::TwoPi);
		transform.scale = 10;
		std::unique_ptr<Boss> enemy = std::make_unique<Boss>(c14::Model{ "Boss.txt" }, transform, 1000.0f);
		m_scene->Add(std::move(enemy));
		m_bossSpawned = true;
	}

	// reset timer
	if (m_spawnTimer <= 0)
	{
		m_spawnTimer = 4;
	}

	//update game objects
	m_scene->Update();

	// update score Text
	m_scoreText->Create(c14::g_renderer, std::to_string(m_score), { 255, 255, 255, 255 });
}

void SpaceShooter::Draw(c14::Renderer& renderer)
{
	// render game objects
	m_scene->Draw(c14::g_renderer);
	m_titleText->Draw(renderer, { 300, 10 });
	m_scoreText->Draw(renderer, { 40, 30 });
}