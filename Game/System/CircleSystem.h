#pragma once

#include "System.h"
#include "Component/CircleComponent.h"

#include <unordered_map>

class CircleSystem : public System<CircleComponent>
{
public:
    CircleSystem();
    
    CircleComponent* add(GameObject& obj);

    void remove(GameObject& obj);
    void update(float dt);

    CircleComponent& get(GameObject& obj);

    bool isRegistered(GameObject& obj) const;

private:
    std::unordered_map<uint32_t, CircleComponent> m_component;
};