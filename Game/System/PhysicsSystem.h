#pragma once

#include "System.h"
#include "Component/PhysicsComponent.h"

#include <unordered_map>


class PhysicsSystem : public System<PhysicsComponent>
{
public:

	enum ColliderType : uint16_t
	{
		UNKNOWN,
		RECT,
		CIRCLE
	};

	enum class ScreenSide
	{
		UNKNOWN,
		LEFT,
		TOP,
		RIGHT,
		BOTTOM
	};

	struct ObjectInfo
	{
		PhysicsComponent m_component;
		GameObject* m_gameObject;
		ColliderType m_type;
	};

	struct CollisionPair
	{
		uint32_t m_indices;
		bool m_isFrame;
	};

	PhysicsSystem();

	PhysicsComponent* add(GameObject& obj);

	void remove(GameObject& obj);

	void update(float dt);

	PhysicsComponent& get(GameObject& obj);

	bool isRegistered(GameObject& obj) const;


private:

	inline uint32_t makeColliderTypePair(ColliderType typeA, ColliderType typeB) const { return ((uint32_t) typeA) | (((uint32_t) typeB) << 16); }

	sf::Shape* getObjectShape(GameObject* obj) const;

	bool intersect(sf::Shape* shapeA, sf::Shape* shapeB, ColliderType typeA, ColliderType typeB) const;
	bool intersect(sf::RectangleShape* shapeA, sf::RectangleShape* shapeB) const;
	bool intersect(sf::RectangleShape* shapeA, sf::CircleShape* shapeB) const;


private:

	std::unordered_map<uint32_t, ObjectInfo> m_colliders;
	std::unordered_map<uint32_t, CollisionPair> m_collisionPairs;
};
