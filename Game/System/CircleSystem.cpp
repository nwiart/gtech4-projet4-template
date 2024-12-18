#include "GameManager.h"
#include "CircleSystem.h"

#include "Scene/GameObject.h"

CircleSystem::CircleSystem()
{
}

CircleComponent* CircleSystem::add(GameObject& obj)
{
    auto p = m_component.emplace(obj, CircleComponent{});
    CircleComponent& c = p.first->second;
    return &c;
}

void CircleSystem::remove(GameObject& obj)
{
    m_component.erase(obj);
}

void CircleSystem::update(float dt)
{
    for (auto& [id, comp] : m_component) {
        GameObject* obj = GameManager::getInstance().getObjectByID(id);
        sf::CircleShape* shape = reinterpret_cast<sf::CircleShape*>(comp.getShape());

        shape->setPosition(obj->getPosition());
        shape->setRadius(25.0F);
        shape->setFillColor(sf::Color::Cyan);
    }
}

CircleComponent& CircleSystem::get(GameObject& obj)
{
    if (auto it = m_component.find(obj); it != m_component.end())
    {
        return it->second;
    }
}

bool CircleSystem::isRegistered(GameObject& obj) const
{
    return m_component.find(obj) != m_component.end();
}
