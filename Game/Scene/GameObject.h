#pragma once

#include "GameManager.h"

#include <stdint.h>


class GameObject
{
public:

	GameObject();

	template<typename T>
	T* addComponent()
	{
		return GameManager::getInstance().addComponentToObject<T>(this);
	}

	inline uint32_t getID() const { return m_id; }

	inline operator uint32_t() const { return m_id; }

private:

	uint32_t m_id;
};
