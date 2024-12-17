#pragma once

#include "GameManager.h"
#include "IncludeSFML.h"

#include <stdint.h>


class GameObject
{
public:

	GameObject() : m_id(-1) { }

	template<typename T>
	T* addComponent()
	{
		return GameManager::getInstance().addComponentToObject<T>(*this);
	}

	inline uint32_t getID() const { return m_id; }

	inline operator uint32_t() const { return m_id; }

	void setPosition(const sf::Vector2f& newPosition);
	const sf::Vector2f& getPosition() const { return position; }

private:

	uint32_t m_id;
	sf::Vector2f position;

};
