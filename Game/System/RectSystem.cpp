#include "GameManager.h"
#include "RectSystem.h"

#include "Scene/GameObject.h"

RectSystem::RectSystem()
{
}

RectComponent* RectSystem::add(GameObject& obj)
{
    auto p = m_component.emplace(obj, RectComponent{});
    RectComponent& c = p.first->second;
    return &c;
}

void RectSystem::remove(GameObject& obj)
{
    m_component.erase(obj);
}

void RectSystem::update(float dt)
{
    for (auto& [id, comp] : m_component) {
        GameObject* obj = GameManager::getInstance().getObjectByID(id);
        sf::RectangleShape* shape = reinterpret_cast<sf::RectangleShape*>(comp.getShape());

        shape->setPosition(obj->getPosition());
    }
}

RectComponent& RectSystem::get(GameObject& obj)
{
    if (auto it = m_component.find(obj); it != m_component.end())
    {
        return it->second;
    }
}

bool RectSystem::isRegistered(GameObject& obj) const
{
    return m_component.find(obj) != m_component.end();
}
