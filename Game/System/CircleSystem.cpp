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
    // Nothing TODO
}

CircleComponent& CircleSystem::get(GameObject& obj)
{
    if (auto it = m_component.find(obj); it != m_component.end())
    {
        return it->second;
    }
}
