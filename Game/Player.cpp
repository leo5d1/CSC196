#include "Player.h"
#include "Bullet.h"

void Player::Update()
{
	//keyboard controls
	// rotate
	if (c14::g_inputSystem.GetKeyDown(c14::key_left))
	{
		m_transform.rotation -= math::Pi * c14::g_time.deltaTime;
	}
	if (c14::g_inputSystem.GetKeyDown(c14::key_right))
	{
		m_transform.rotation += math::Pi * c14::g_time.deltaTime;
	}
	// set thrust speed
	m_speed = 0;
	if (c14::g_inputSystem.GetKeyDown(c14::key_up))
	{
		m_speed = m_maxSpeed;
	}
	// turbo speed
	if (c14::g_inputSystem.GetKeyDown(c14::key_up) && c14::g_inputSystem.GetKeyDown(c14::key_space))
	{
		m_speed = m_maxSpeed * 2;
	}

	// calculate velocity
	c14::Vector2 direction{ 1, 0 };
	direction = c14::Vector2::Rotate(direction, m_transform.rotation);
	c14::Vector2 velocity = direction * m_speed * c14::g_time.deltaTime;
	//move
	m_transform.position += velocity;

	// edge of screen
	if (m_transform.position.x > c14::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = c14::g_renderer.GetWidth();
	if (m_transform.position.y > c14::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = c14::g_renderer.GetHeight();

	// fire bullets

	if (c14::g_inputSystem.GetKeyState(c14::key_q) == c14::InputSystem::State::Pressed)
	{
		// fire
		c14::Transform transform = m_transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(c14::Model{ "Bullet.txt" }, transform, 2.0f);
		bullet->GetTag() = "player";
		m_scene->Add(std::move(bullet));
		c14::g_audio.PlayAudio("laser");
		
	}
	
	if (c14::g_inputSystem.GetKeyState(c14::key_e) == c14::InputSystem::State::Pressed)
	{
		// fire
		c14::Transform transform = m_transform;
		std::unique_ptr<Bullet> bomb = std::make_unique<Bullet>(c14::Model{ "Bomb.txt" }, transform, 10.0f);
		bomb->GetTag() = "bomb";
		m_scene->Add(std::move(bomb));
		c14::g_audio.PlayAudio("laser");
	}
}

void Player::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "enemy")
	{
		m_health -= dynamic_cast<Bullet*>(other)->GetDamage();

		if (m_health <= 0) m_destroy = true;
	}
}
