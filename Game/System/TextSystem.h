#pragma once

#include "System/System.h"
#include "Component/TextComponent.h"

#include <unordered_map>

class TextSystem : public System<TextComponent>
{
public:
    TextSystem();

    TextComponent* add(GameObject& obj);

    void remove(GameObject& obj);

    void update(float dt);

    TextComponent& get(GameObject& obj);

    bool isRegistered(GameObject& obj) const;

private:
    std::unordered_map<uint32_t, TextComponent> m_component;
};