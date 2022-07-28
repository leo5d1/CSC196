#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Engine.h"

void Bullet::Update()
{
	// lifespan
	m_lifespan -= c14::g_time.deltaTime;
	if (m_lifespan <= 0) m_destroy = true;

	// calculate velocity
	c14::Vector2 direction{ 1, 0 };
	direction = c14::Vector2::Rotate(direction, m_transform.rotation);
	c14::Vector2 velocity = direction * m_speed * c14::g_time.deltaTime;

	
	// move
	m_transform.position += velocity;

	// edge of screen
	if (m_transform.position.x > c14::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = c14::g_renderer.GetWidth();
	if (m_transform.position.y > c14::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = c14::g_renderer.GetHeight();
}

void Bullet::OnCollision(Actor* other)
{
	if (dynamic_cast<Player*>(other) && m_tag != "player" && m_tag != "bomb")
	{
		if (dynamic_cast<Player*>(other) && m_tag == "bomb")
		{
			c14::g_audio.PlayAudio("explosion");
			m_destroy = true;
		}
		else 
		{
			m_destroy = true;
		}
	}

	if (dynamic_cast<Enemy*>(other) && m_tag != "enemy")
	{
		m_destroy = true;
	}

	if (dynamic_cast<Enemy2*>(other) && m_tag != "enemy")
	{
		m_destroy = true;
	}

	if (dynamic_cast<Boss*>(other) && m_tag != "enemy")
	{
		m_destroy = true;
	}
}
