#pragma once
#include "IncludeSFML.h"

class GameObject;

class PhysicsComponent
{
	friend class PhysicsSystem;

	typedef bool (*OnCollideScreen)(GameObject& objA, PhysicsComponent& collA);
	typedef bool (*OnCollideObject)(GameObject& objA, PhysicsComponent& collA, GameObject& objB, PhysicsComponent& collB);

public:

	typedef class PhysicsSystem SystemType;


	PhysicsComponent();

	void update(float dt);

	void setVelocity(const sf::Vector2f& newVelocity);

	inline void setCollideScreenCallback(OnCollideScreen func) { m_onCollideScreenCallback = func; }
	inline void setCollideObjectCallback(OnCollideObject func) { m_onCollideObjectCallback = func; }


	inline const sf::Vector2f& getVelocity() const { return velocity; }

private:
	sf::Vector2f velocity;

	OnCollideScreen m_onCollideScreenCallback;
	OnCollideObject m_onCollideObjectCallback;
};
