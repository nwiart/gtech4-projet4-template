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
    // Nothing TODO
}

RectComponent& RectSystem::get(GameObject& obj)
{
    if (auto it = m_component.find(obj); it != m_component.end())
    {
        return it->second;
    }
}
