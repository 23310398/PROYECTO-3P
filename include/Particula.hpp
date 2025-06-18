#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Particula {
public:
    Particula(sf::Vector2f pos, sf::Color color);
    void update(float deltaTime);
    void Draw(sf::RenderWindow& window) const;
    bool IsAlive() const;

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime;
    sf::CircleShape shape;
};
