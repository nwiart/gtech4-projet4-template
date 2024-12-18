#include "GameManager.h"
#include "RenderSystem.h"

#include "Scene/GameObject.h"


RenderSystem::RenderSystem()
{
	m_window.create(sf::VideoMode(1280, 720), "Casse-Briques");
	m_window.setVerticalSyncEnabled(true);
}

RenderComponent* RenderSystem::add(GameObject& obj)
{
	auto p = m_components.emplace(obj, RenderComponent{ });
	RenderComponent& c = p.first->second;
	return &c;
}

void RenderSystem::remove(GameObject& obj)
{
	m_components.erase(obj);
}

void RenderSystem::update()
{
	m_window.clear();

	for (auto& [id, component] : m_components) {
		GameObject* obj = GameManager::getInstance().getObjectByID(id);

		if (obj->hasComponent<RectComponent>()) {
			m_window.draw(*reinterpret_cast<sf::RectangleShape*>(obj->getComponent<RectComponent>().getShape()));
		}
		else if (obj->hasComponent<CircleComponent>()) {
			m_window.draw(*reinterpret_cast<sf::CircleShape*>(obj->getComponent<CircleComponent>().getShape()));
		}
	}

	m_window.display();
}

RenderComponent& RenderSystem::get(GameObject& obj)
{
	if (auto it = m_components.find(obj); it != m_components.end()) {
		return it->second;
	}
}

bool RenderSystem::isRegistered(GameObject& obj) const
{
	auto it = m_components.find(obj);
	return it != m_components.end();
}
