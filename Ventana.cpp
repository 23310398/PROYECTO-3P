#include <SFML/Graphics.hpp>

int main()
{
    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    // Cargar una textura desde el archivo PORTADA.jpg
    sf::Texture texture;
    if (!texture.loadFromFile("PORTADA.jpg")) {
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

        window.clear();
        window.draw(sprite); // Dibujar el sprite en lugar del círculo
        window.display();
    }

    return 0;
}