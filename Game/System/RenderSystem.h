#pragma once

#include "System.h"
#include "Component/RenderComponent.h"

#include <SFML/Graphics.hpp>

#include <unordered_map>


class RenderSystem : public System<RenderComponent>
{
public:

	RenderSystem();

	RenderComponent* add(GameObject& obj);

	void remove(GameObject& obj);

	void update();

	RenderComponent& get(GameObject& obj);

	bool isRegistered(GameObject& obj) const;

	inline sf::RenderWindow& getSfmlWindow() { return m_window; }


private:

	sf::RenderWindow m_window;

	std::unordered_map<uint32_t, RenderComponent> m_components;
};
