#include "GameManager.h"

#include "Scene.h"

#include "GameObject.h"


Scene::Scene()
	: m_currentID(0)
{
	
}

GameObject* Scene::instantiateObject()
{
	auto it = m_gameObjects.emplace(m_currentID, GameObject{ m_currentID });
	GameObject* obj = &it.first->second;

	m_currentID++;

	return obj;
}

void Scene::destroyObject(GameObject* obj)
{
	m_gameObjects.erase(obj->getID());
}

GameObject* Scene::getObjectByID(uint32_t id)
{
	if (auto it = m_gameObjects.find(id); it != m_gameObjects.end()) {
		return &it->second;
	}
	return 0;
}
