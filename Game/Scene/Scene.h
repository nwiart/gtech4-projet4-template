#pragma once

class GameObject;


class Scene
{
public:

	Scene();

	GameObject* instantiateObject();

	void destroyObject(GameObject* obj);


private:

};
