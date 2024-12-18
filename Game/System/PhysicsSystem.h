#pragma once

#include "System.h"
#include "Component/PhysicsComponent.h"

#include <SFML/Graphics.hpp>

#include <unordered_map>


class PhysicsSystem : public System<PhysicsComponent>
{
public:

	PhysicsSystem();

	PhysicsComponent* add(GameObject& obj);

	void remove(GameObject& obj);

	void update(float dt);

	PhysicsComponent& get(GameObject& obj);


private:

	std::unordered_map<uint32_t, PhysicsComponent> m_components;
};
