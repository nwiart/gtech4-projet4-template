#pragma once

#include <SFML/Graphics.hpp>
#include <concepts>

template <typename T>
concept Drawable = std::derived_from<T, sf::Drawable>;

template <Drawable T>
class Actor {
private:
    T drawable;
    sf::Vector2f position;
    sf::Vector2f velocity;

public:
    Actor(const T& drawableObject, const sf::Vector2f& initialPosition)
        : drawable(drawableObject), position(initialPosition), velocity(0.f, 0.f) {
        drawable.setPosition(position);
    }

    const sf::Vector2f& getPosition() const { return position; }
    const sf::Vector2f& getVelocity() const { return velocity; }

    void setPosition(const sf::Vector2f& newPosition) {
        position = newPosition;
        drawable.setPosition(position);
    }

    void setVelocity(const sf::Vector2f& newVelocity) {
        velocity = newVelocity;
    }

    void update(float deltaTime) {
        position += velocity * deltaTime;
        drawable.setPosition(position);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(drawable);
    }

    bool intersects(const Actor<sf::RectangleShape>& other) const {
        return drawable.getGlobalBounds().intersects(other.getDrawable().getGlobalBounds());
    }


    T& getDrawable() { return drawable; }
};
