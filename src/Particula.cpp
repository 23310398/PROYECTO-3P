#include "../include/Particula.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>

Particula::Particula(sf::Vector2f pos, sf::Color color)
    : position(pos), velocity(rand() % 5 - 2, rand() % 5 - 2), lifetime(1.0f) {
    shape.setRadius(3);
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Particula::update(float deltaTime) {
    position += velocity;
    lifetime -= deltaTime;
    shape.setPosition(position);
}

void Particula::draw(sf::RenderWindow& window) const {
    if (lifetime > 0) {
        window.draw(shape);
    }
}

bool Particula::isAlive() const {
    return lifetime > 0;
}
