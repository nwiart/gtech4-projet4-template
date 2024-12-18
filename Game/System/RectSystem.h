#pragma once

#include "System/System.h"
#include "Component/RectComponent.h"

#include <unordered_map>

class RectSystem : public System<RectComponent>
{
public:
    RectSystem();

    RectComponent* add(GameObject& obj);


private:
    std::unordered_map<uint32_t, RectComponent> m_component;
};