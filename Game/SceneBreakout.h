#pragma once

#include "IncludeSFML.h"

#include "Scene/Scene.h"


class SceneBreakout : public Scene
{
public:

	SceneBreakout();

	virtual void load() override;

	virtual void spawn() override;

	virtual void update() override;

private:

	static bool onBrickCollide(GameObject& objA, PhysicsComponent& collA, GameObject& objB, PhysicsComponent& collB);


private:

	GameObject* m_paddle;
	GameObject* m_score;

	sf::Texture brickTex;
	sf::Font font;
};
