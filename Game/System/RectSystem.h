#pragma once

#include "System/System.h"
#include "Component/RectComponent.h"

#include <unordered_map>

class RectSystem : public System<RectComponent>
{
public:
    RectSystem();

    RectComponent* add(GameObject& obj);

    void remove(GameObject& obj);

    void update(float dt);

    RectComponent& get(GameObject& obj);

private:
    std::unordered_map<uint32_t, RectComponent> m_component;
};