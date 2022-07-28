#pragma once
#include "Framework/Actor.h"
#include "Engine.h"

class Enemy : public c14::Actor
{
public:
	Enemy() = default;
	Enemy(const c14::Model& model, const c14::Transform& transform, float health = 1) : 
		Actor{ model, transform },
		m_health{ health } {}

	void Update() override;

	void OnCollision(Actor* other) override;

private:
	float m_health = 1;

	float m_speed = 50;
	float m_fireTimer = 0;
};
