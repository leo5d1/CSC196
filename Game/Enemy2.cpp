#include "Enemy2.h"
#include "Bullet.h"
#include "Player.h"

void Enemy2::Update()
{

	// Set Direction towards Player
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		c14::Vector2 direction = player->GetTransform().position - m_transform.position;
		m_transform.rotation = direction.GetAngle();
	}

	// calculate velocity
	c14::Vector2 direction{ 1, 0 };
	direction = c14::Vector2::Rotate(direction, m_transform.rotation);
	c14::Vector2 velocity = direction * m_speed * c14::g_time.deltaTime;
	// move
	m_transform.position += velocity;

	// Fire Weapon
	m_fireTimer -= c14::g_time.deltaTime;
	if (m_fireTimer <= 0)
	{
		m_fireTimer = c14::Randomf(2, 6);
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(c14::Model{ "Bullet.txt" }, m_transform);
		bullet->GetTag() = "enemy";
		m_scene->Add(std::move(bullet));
	}

	// edge of screen
	if (m_transform.position.x > c14::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = c14::g_renderer.GetWidth();
	if (m_transform.position.y > c14::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = c14::g_renderer.GetHeight();
}

void Enemy2::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "player")
	{
		m_health -= dynamic_cast<Bullet*>(other)->GetDamage();

		if (m_health <= 0)
		{
			m_destroy = true;
			m_scene->GetGame()->AddPoints(1000);
		}
	}

	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "bomb")
	{
		m_health -= dynamic_cast<Bullet*>(other)->GetDamage();

		if (m_health <= 0)
		{
			m_destroy = true;
			m_scene->GetGame()->AddPoints(1000);
		}
	}
}
