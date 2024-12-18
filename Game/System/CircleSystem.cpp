#include "CircleSystem.h"

CircleSystem::CircleSystem()
{
}

CircleComponent* CircleSystem::add(GameObject& obj)
{
    auto p = m_component.emplace(obj, CircleComponent{});
    CircleComponent& c = p.first->second;
    return &c;
}
