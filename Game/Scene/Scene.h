#pragma once

#include "GameObject.h"

#include <unordered_map>


class Scene
{
public:

	Scene();

	virtual void load() { }
	virtual void spawn() { }
	virtual void update() { }
	
	void clear();

	GameObject* instantiateObject();

	void destroyObject(uint32_t id);
	void destroyObject(GameObject* obj);

	GameObject* getObjectByID(uint32_t id);


private:

	std::unordered_map<uint32_t, GameObject> m_gameObjects;

	uint32_t m_currentID;
};
