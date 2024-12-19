#include "GameManager.h"
#include "TextSystem.h"

#include "Scene/GameObject.h"

TextSystem::TextSystem()
{
}

TextComponent* TextSystem::add(GameObject& obj)
{
    auto p = m_component.emplace(obj, TextComponent{});
    TextComponent& c = p.first->second;
    return &c;
}

void TextSystem::remove(GameObject& obj)
{
    m_component.erase(obj);
}

void TextSystem::update(float dt)
{

}

TextComponent& TextSystem::get(GameObject& obj)
{
    if (auto it = m_component.find(obj); it != m_component.end())
    {
        return it->second;
    }
}

bool TextSystem::isRegistered(GameObject& obj) const
{
    return m_component.find(obj) != m_component.end();
}
