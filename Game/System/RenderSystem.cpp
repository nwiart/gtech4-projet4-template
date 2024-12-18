#include "GameManager.h"
#include "RenderSystem.h"

#include "Scene/GameObject.h"


RenderSystem::RenderSystem()
{
	m_window.create(sf::VideoMode(1280, 720), "Casse-Briques");
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
		component.draw(m_window);
		//m_window.draw(component)
	}

	m_window.display();
}

RenderComponent& RenderSystem::get(GameObject& obj)
{
	if (auto it = m_components.find(obj); it != m_components.end()) {
		return it->second;
	}
}
