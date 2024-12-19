#pragma once

#include "IncludeSFML.h"

#include <stdint.h>


enum class GameObjectFlags : uint32_t
{
	NONE = 0,
	DESTROY = (1 << 0)
};


class GameObject
{
public:

	GameObject(uint32_t id) : m_id(id), m_flags(0), m_userData(0) { }

	template<typename T>
	T* addComponent()
	{
		return GameManager::getInstance().addComponentToObject<T>(*this);
	}

	template<typename T>
	T& getComponent()
	{
		return GameManager::getInstance().getObjectComponent<T>(*this);
	}

	template<typename T>
	bool hasComponent()
	{
		return GameManager::getInstance().hasComponent<T>(*this);
	}

	inline uint32_t getID() const { return m_id; }

	inline operator uint32_t() const { return m_id; }

	inline bool isMarkedForDeletion() const { return (m_flags & (uint32_t)GameObjectFlags::DESTROY) != 0; }
	inline void markForDeletion() { m_flags = m_flags | (uint32_t)GameObjectFlags::DESTROY; }

	inline uintptr_t getUserData() const { return m_userData; }
	inline void setUserData(uintptr_t p) { m_userData = p; }

	void setPosition(const sf::Vector2f& newPosition);
	const sf::Vector2f& getPosition() const { return position; }

private:

	uint32_t m_id;
	uint32_t m_flags;
	uintptr_t m_userData;

	sf::Vector2f position;
};
