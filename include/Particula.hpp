#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Particula {
public:
    Particula(sf::Vector2f pos, sf::Color color);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isAlive() const;

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime;
    sf::CircleShape shape;
};
