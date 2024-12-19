#include "GameManager.h"
#include "SceneBreakout.h"


SceneBreakout::SceneBreakout()
{

}

void SceneBreakout::load()
{
	brickTex.loadFromFile("brick.png");
}

void SceneBreakout::spawn()
{
	GameManager& man = GameManager::getInstance();
	sf::Window& window = man.getSystem<RenderSystem>().getSfmlWindow();

	// User-controlled paddle.
	m_paddle = this->instantiateObject();
	man.addComponents<RectSystem, RenderSystem, PhysicsSystem>(*m_paddle);
	m_paddle->setPosition(sf::Vector2f((window.getSize().x / 2), (window.getSize().y - 100)));
	m_paddle->getComponent<RectComponent>().setColor(sf::Color::Green);
	m_paddle->getComponent<RectComponent>().setSize(sf::Vector2f(150, 20));

	// The ball.
	GameObject* ball = this->instantiateObject();
	man.addComponents<CircleSystem, RenderSystem, PhysicsSystem>(*ball);
	ball->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	ball->getComponent<CircleComponent>().setColor(sf::Color::Red);
	ball->getComponent<CircleComponent>().setRadius(10);
	ball->getComponent<PhysicsComponent>().setVelocity(sf::Vector2f(300.0F, 300.0F));
	ball->getComponent<PhysicsComponent>().setCollideObjectCallback([](GameObject& objA, PhysicsComponent& collA, GameObject& objB, PhysicsComponent& collB) -> bool {
		bool isBrick = objB.getUserData() == 1;
		sf::Vector2f v = collA.getVelocity();
		if (!isBrick) {
			v.x = 10.0F * (((objA.getPosition().x + 6.0F) - (objB.getPosition().x + 75.0F)));
		}
		v.y = -v.y;
		collA.setVelocity(v);
		return true;
	});
	ball->getComponent<PhysicsComponent>().setCollideScreenCallback([](GameObject& objA, PhysicsComponent& collA, int side) -> bool {
		sf::Vector2f v = collA.getVelocity();
		switch ((PhysicsSystem::ScreenSide)side)
		{
		case PhysicsSystem::ScreenSide::LEFT:   break;
		case PhysicsSystem::ScreenSide::TOP:    break;
		case PhysicsSystem::ScreenSide::RIGHT:  break;
		case PhysicsSystem::ScreenSide::BOTTOM:
			GameManager::getInstance().getScene()->clear();
			GameManager::getInstance().getScene()->spawn();
			break;
		}
		collA.setVelocity(v);
		return true;
	});

	// Bricks.
	const sf::Vector2f brickSize(100.0f, 40.0f);
	const float spacing = 10.0f;
	const float startX = (window.getSize().x - (brickSize.x * 4 + spacing * 3)) / 2;
	const float startY = 50.0f;

	constexpr uint32_t color[] =
	{
		0xFF2020ff, 0xFF8020ff, 0xFFFF00ff, 0x20FF20ff, 0x22AAFFff, 0x1050FFff, 0x6020FFff
	};
	int n = 0;

	for (int row = 0; row < 2; ++row) {
		for (int col = 0; col < 4; ++col) {

			float posX = startX + col * (brickSize.x + spacing);
			float posY = startY + row * (brickSize.y + spacing);

			GameObject* brick = this->instantiateObject();
			man.addComponents<RectSystem, PhysicsSystem, RenderSystem>(*brick);
			brick->setUserData(1);
			brick->setPosition(sf::Vector2f(posX, posY));
			brick->getComponent<RectComponent>().setColor(sf::Color(color[n % 7]));
			brick->getComponent<RectComponent>().setSize(brickSize);
			brick->getComponent<RectComponent>().setTexture(brickTex);
			brick->getComponent<PhysicsComponent>().setCollideObjectCallback([](GameObject& objA, PhysicsComponent& collA, GameObject& objB, PhysicsComponent& collB) -> bool {
				GameManager::getInstance().destroyObject(objA);
				return true;
			});

			n++;
		}
	}
}

void SceneBreakout::update()
{
	GameManager& man = GameManager::getInstance();
	sf::Window& window = man.getSystem<RenderSystem>().getSfmlWindow();

	constexpr float PADDLE_SPEED = 10.0F;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_paddle->getPosition().x > 0)
		{
			m_paddle->setPosition(m_paddle->getPosition() - sf::Vector2f(PADDLE_SPEED, 0));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_paddle->getPosition().x + 150 < window.getSize().x)
		{
			m_paddle->setPosition(m_paddle->getPosition() + sf::Vector2f(PADDLE_SPEED, 0));
		}
	}
}
