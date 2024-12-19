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

	GameObject* m_paddle;

	sf::Texture brickTex;
};
