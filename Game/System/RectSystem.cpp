#include "RectSystem.h"

RectSystem::RectSystem()
{
}

RectComponent* RectSystem::add(GameObject& obj)
{
    auto p = m_component.emplace(obj, RectComponent{});
    RectComponent& c = p.first->second;
    return &c;
}
