
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Peleador {
public:
    Peleador(sf::Texture& sharedTexture, sf::Vector2f startPos, sf::Color boxColor);
    void move(float dx, float dy);
    void animate(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void recibirDanio(int cantidad);
    void cargarEnergia();
    bool puedeUsarEspecial() const;
    void usarEspecial(Peleador& oponente, int jugador);
    void update(float deltaTime);
    int getVida() const;
    int getEnergia() const;

private:
    sf::Texture* texture;
    sf::Sprite sprite;
    sf::RectangleShape hitbox;
    int vida;
    int energia;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    float animationTime;
    float elapsedTime;
};


