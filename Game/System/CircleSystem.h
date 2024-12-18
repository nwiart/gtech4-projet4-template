#pragma once

#include "System/System.h"
#include "Component/CircleComponent.h"

#include <unordered_map>

class CircleSystem : public System<CircleComponent>
{
public:
    CircleSystem();
    
    CircleComponent* add(GameObject& obj);

private:
    std::unordered_map<uint32_t, CircleComponent> m_component;
};