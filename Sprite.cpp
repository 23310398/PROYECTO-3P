#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Example");

    // Cargar una textura desde el archivo SPRITE.jpg
    sf::Texture texture;
    if (!texture.loadFromFile("SPRITE.jpg")) {
        // Manejar error si no se encuentra la imagen
        return -1;
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Centrar el sprite en la ventana
    sprite.setPosition(
        (window.getSize().x - sprite.getGlobalBounds().width) / 2,
        (window.getSize().y - sprite.getGlobalBounds().height) / 2
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento del sprite con las teclas de flecha
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                sprite.move(0, -5);
            }
            if (event.key.code == sf::Keyboard::Down) {
                sprite.move(0, 5);
            }
            if (event.key.code == sf::Keyboard::Left) {
                sprite.move(-5, 0);
            }
            if (event.key.code == sf::Keyboard::Right) {
                sprite.move(5, 0);
            }
        }

        window.clear();
        window.draw(sprite); // Dibujar el sprite en la ventana
        window.display();
    }

    return 0;
}