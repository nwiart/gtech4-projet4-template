#include "Scene.h"

#include "GameObject.h"


Scene::Scene()
{

}

GameObject* Scene::instantiateObject()
{
	return new GameObject();
}

void Scene::destroyObject(GameObject* obj)
{
	delete obj;
}
