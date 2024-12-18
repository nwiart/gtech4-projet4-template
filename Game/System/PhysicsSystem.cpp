#include "GameManager.h"
#include "PhysicsSystem.h"
#include "Scene/GameObject.h"

#include "System/RectSystem.h"
#include "System/CircleSystem.h"
#include "Component/RectComponent.h"
#include "Component/CircleComponent.h"

#include <vector>

PhysicsSystem::PhysicsSystem()
{
}

PhysicsComponent *PhysicsSystem::add(GameObject &obj)
{
	auto p = m_colliders.emplace(obj, ObjectInfo{{}, &obj, UNKNOWN});
	ObjectInfo& coll = p.first->second;

	if (obj.hasComponent<RectComponent>()) {
		coll.m_type = RECT;
	}
	else if (obj.hasComponent<CircleComponent>()) {
		coll.m_type = CIRCLE;
	}
	else {
		coll.m_type = UNKNOWN;
	}

	return &coll.m_component;
}

void PhysicsSystem::remove(GameObject &obj)
{
	m_colliders.erase(obj);
}

void PhysicsSystem::update(float dt)
{
	std::vector<ObjectInfo*> allColliders;
	allColliders.reserve(m_colliders.size());

	// Integrate.
	for (auto &[id, collider] : m_colliders)
	{
		PhysicsComponent& component = collider.m_component;
		GameObject *obj = GameManager::getInstance().getObjectByID(id);
		obj->setPosition(obj->getPosition() + component.velocity * dt);

		allColliders.push_back(&collider);
	}

	// Collision test.
	for (int i = 0; i < allColliders.size(); i++)
	{
		ObjectInfo* objA = allColliders[i];
		sf::Shape* shapeA = getObjectShape(objA->m_gameObject);

		for (int j = i + 1; j < allColliders.size(); j++)
		{
			ObjectInfo* objB = allColliders[j];
			sf::Shape* shapeB = getObjectShape(objB->m_gameObject);

			uint32_t pairID = objA->m_gameObject->getID() | (objB->m_gameObject->getID() << 16);
			auto it = m_collisionPairs.find(pairID);
			if (it != m_collisionPairs.end()) {
				it->second.m_isFrame = false;
			}

			bool res = intersect(shapeA, shapeB, objA->m_type, objB->m_type);
			if (res) {
				bool newCollision = false;
				if (it == m_collisionPairs.end()) {
					newCollision = true;
					it = m_collisionPairs.emplace(pairID, CollisionPair{pairID, true}).first;
				}
				else {
					it->second.m_isFrame = true;
				}

				if (newCollision) {
					if (objA->m_component.m_onCollideObjectCallback) {
						objA->m_component.m_onCollideObjectCallback(*objA->m_gameObject, objA->m_component, *objB->m_gameObject, objB->m_component);
					}
					if (objB->m_component.m_onCollideObjectCallback) {
						objB->m_component.m_onCollideObjectCallback(*objB->m_gameObject, objB->m_component, *objA->m_gameObject, objA->m_component);
					}
				}
			}

			if (it != m_collisionPairs.end() && !it->second.m_isFrame) {
				m_collisionPairs.erase(pairID);
			}
		}

		// Border detection.
		sf::FloatRect bounds = shapeA->getGlobalBounds();
		PhysicsSystem::ScreenSide side = ScreenSide::UNKNOWN;

		if (bounds.left < 0 && objA->m_component.velocity.x < 0) {
			objA->m_component.velocity.x = -objA->m_component.velocity.x;
			side = ScreenSide::LEFT;
		}
		if (bounds.left + bounds.width > 1280 && objA->m_component.velocity.x > 0) {
			objA->m_component.velocity.x = -objA->m_component.velocity.x;
			side = ScreenSide::RIGHT;
		}
		if (bounds.top < 0 && objA->m_component.velocity.y < 0) {
			objA->m_component.velocity.y = -objA->m_component.velocity.y;
			side = ScreenSide::TOP;
		}
		if (bounds.top + bounds.height > 720 && objA->m_component.velocity.y > 0) {
			objA->m_component.velocity.y = -objA->m_component.velocity.y;
			side = ScreenSide::BOTTOM;
		}

		if (objA->m_component.m_onCollideScreenCallback) {
			objA->m_component.m_onCollideScreenCallback(*objA->m_gameObject, objA->m_component, (int) side);
		}
	}
}

PhysicsComponent &PhysicsSystem::get(GameObject &obj)
{
	if (auto it = m_colliders.find(obj); it != m_colliders.end())
	{
		return it->second.m_component;
	}
}

bool PhysicsSystem::isRegistered(GameObject& obj) const
{
	auto it = m_colliders.find(obj);
	return it != m_colliders.end();
}

sf::Shape* PhysicsSystem::getObjectShape(GameObject* obj) const
{
	auto it = m_colliders.find(obj->getID());
	if (it == m_colliders.end()) {
		return 0;
	}

	switch (it->second.m_type)
	{
	case RECT: return obj->getComponent<RectComponent>().getShape();
	case CIRCLE: return obj->getComponent<CircleComponent>().getShape();
	default: return 0;
	}
}

bool PhysicsSystem::intersect(sf::Shape* shapeA, sf::Shape* shapeB, ColliderType typeA, ColliderType typeB) const
{
	uint32_t collPair = makeColliderTypePair(typeA, typeB);

	// Dispatch collisions.
	switch (collPair)
	{
	// Rect-Rect collision.
	case ColliderType::RECT | (ColliderType::RECT << 16):
		return intersect(reinterpret_cast<sf::RectangleShape*>(shapeA), reinterpret_cast<sf::RectangleShape*>(shapeB));

	// Rect-Circle collision.
	case ColliderType::CIRCLE | (ColliderType::RECT << 16):
		std::swap(shapeA, shapeB);
	case ColliderType::RECT | (ColliderType::CIRCLE << 16):
		return intersect(reinterpret_cast<sf::RectangleShape*>(shapeA), reinterpret_cast<sf::CircleShape*>(shapeB));

	// Non-implemented pairs.
	default:
		break;
	}

	return false;
}

bool PhysicsSystem::intersect(sf::RectangleShape* shapeA, sf::RectangleShape* shapeB) const
{
	return shapeA->getGlobalBounds().intersects(shapeB->getGlobalBounds());
}

bool PhysicsSystem::intersect(sf::RectangleShape* shapeA, sf::CircleShape* shapeB) const
{
	return shapeA->getGlobalBounds().intersects(shapeB->getGlobalBounds());
}
