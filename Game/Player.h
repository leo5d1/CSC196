#pragma once
#include "Framework/Actor.h"
#include "Engine.h"

class Player : public c14::Actor
{
public:
	Player() = default;
	Player(const c14::Model& model, const c14::Transform& transform) : Actor{ model, transform } {}

	void Update() override;

	void OnCollision(Actor* other) override;

private:
	float m_health{ 100000000 };

	float m_speed{ 0 };
	float m_maxSpeed{ 100 };
};