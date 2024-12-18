#pragma once

#include "IncludeSFML.h"

#include <stdint.h>


class GameObject
{
public:

	GameObject(uint32_t id) : m_id(id) { }

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

	void setPosition(const sf::Vector2f& newPosition);
	const sf::Vector2f& getPosition() const { return position; }

private:

	uint32_t m_id;
	sf::Vector2f position;
};
