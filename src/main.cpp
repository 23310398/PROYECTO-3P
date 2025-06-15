#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Peleador {
public:
    Peleador(const std::string& texturePath, sf::Vector2f startPos, sf::Color boxColor) 
        : vida(100) 
    {
        if (!texture.loadFromFile(texturePath)) {
            std::cerr << "Error cargando " << texturePath << "\n";
        }
        sprite.setTexture(texture);
        sprite.setPosition(startPos);
        // Cambiar escala a 1.0f para reducir el tamaño de las imágenes
        sprite.setScale(1.0f, 1.0f);  

        hitbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(boxColor);
        hitbox.setOutlineThickness(1);
        hitbox.setPosition(sprite.getPosition());
    }

    void move(float dx, float dy) {
        sprite.move(dx, dy);
        hitbox.move(dx, dy);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        //window.draw(hitbox); // Descomenta para ver hitbox
    }

    sf::FloatRect getBounds() const {
        return hitbox.getGlobalBounds();
    }

    void recibirDanio(int cantidad) {
        vida -= cantidad;
        if (vida < 0) vida = 0;
    }

    int getVida() const {
        return vida;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape hitbox;
    int vida;
};

// Función para dibujar barra de vida
void dibujarBarra(sf::RenderWindow& window, int vida, sf::Vector2f pos, sf::Color color) {
    sf::RectangleShape fondo(sf::Vector2f(200, 20));
    fondo.setFillColor(sf::Color(50, 50, 50));
    fondo.setPosition(pos);

    sf::RectangleShape barra(sf::Vector2f(2 * vida, 20));  // Vida de 0-100 -> barra de 0-200
    barra.setFillColor(color);
    barra.setPosition(pos);

    window.draw(fondo);
    window.draw(barra);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego de Pelea");
    window.setFramerateLimit(60);

    // Música
    sf::Music music;
    if (!music.openFromFile("./assets/music/musica.ogg")) {
        std::cerr << "Error cargando musica.ogg\n";
    } else {
        music.setLoop(true);
        music.play();
    }

    // Fuente
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error cargando fuente\n";
    }
    sf::Text text("¡Combate!", font, 20);
    // Recalcular posición para centrar el texto
    text.setPosition((800 - text.getGlobalBounds().width) / 2, (600 - text.getGlobalBounds().height) / 4);
    text.setFillColor(sf::Color::White);

    // Menú para seleccionar personajes con imágenes y letras debajo
    sf::Texture texture1, texture2;
    if (!texture1.loadFromFile("./assets/images/peleador1.png") ||
        !texture2.loadFromFile("./assets/images/peleador2.png")) {
        std::cerr << "Error cargando texturas para el menú\n";
        return -1;
    }

    sf::Sprite sprite1(texture1), sprite2(texture2);
    sprite1.setPosition(200, 200);
    sprite2.setPosition(400, 200);
    sprite1.setScale(0.5f, 0.5f);
    sprite2.setScale(0.5f, 0.5f);

    int seleccionJugador1 = 0;
    int seleccionJugador2 = 0;

    // Ajustar selección de personajes para que sean diferentes
    while (true) {
        window.clear();

        sf::Text menuText("Jugador 1: Presiona E\nJugador 2: Presiona B\nPresiona Enter para continuar", font, 20);
        menuText.setPosition(50, 50);
        menuText.setFillColor(sf::Color::White);
        window.draw(menuText);

        window.draw(sprite1);
        window.draw(sprite2);

        sf::Text label1("E", font, 20);
        label1.setPosition(230, 350); // Debajo de la primera imagen
        label1.setFillColor(sf::Color::White);
        window.draw(label1);

        sf::Text label2("B", font, 20);
        label2.setPosition(430, 350); // Debajo de la segunda imagen
        label2.setFillColor(sf::Color::White);
        window.draw(label2);

        window.display();

        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::E) {
                    seleccionJugador1 = 1;
                    seleccionJugador2 = 2; // El otro jugador recibe el personaje restante
                } else if (ev.key.code == sf::Keyboard::B) {
                    seleccionJugador1 = 2;
                    seleccionJugador2 = 1; // El otro jugador recibe el personaje restante
                } else if (ev.key.code == sf::Keyboard::Enter) {
                    if (seleccionJugador1 != 0 && seleccionJugador2 != 0) {
                        goto iniciarJuego;
                    }
                }
            }
        }
    }

iniciarJuego:
    // Configurar peleadores según selección
    Peleador p1(
        seleccionJugador1 == 1 ? "./assets/images/peleador1.png" : "./assets/images/peleador2.png",
        {100, 400}, sf::Color::Red);
    Peleador p2(
        seleccionJugador2 == 1 ? "./assets/images/peleador1.png" : "./assets/images/peleador2.png",
        {600, 400}, sf::Color::Blue);

    // Actualizar teclas de ataque y defensa
    const float speed = 3.0f;

    // Variables para el sistema de turnos
    bool turnoJugador1 = true; // Comienza el jugador 1
    bool accionRealizada = false; // Controla si ya se realizó una acción en el turno

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        // Control de turnos con movimiento al atacar o defender
        if (!accionRealizada) {
            if (turnoJugador1) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { // Ataque del jugador 1
                    p2.recibirDanio(10); // Solo el jugador 2 recibe daño
                    p1.move(10, 0); // Jugador 1 avanza al atacar
                    accionRealizada = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { // Defensa del jugador 1
                    std::cout << "Jugador 1 se defiende!\n";
                    p1.move(-5, 0); // Jugador 1 retrocede al defender
                    accionRealizada = true;
                }
            } else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { // Ataque del jugador 2
                    p1.recibirDanio(10); // Solo el jugador 1 recibe daño
                    p2.move(-10, 0); // Jugador 2 avanza al atacar
                    accionRealizada = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { // Defensa del jugador 2
                    std::cout << "Jugador 2 se defiende!\n";
                    p2.move(5, 0); // Jugador 2 retrocede al defender
                    accionRealizada = true;
                }
            }

            // Cambiar turno automáticamente después de una acción
            if (accionRealizada) {
                turnoJugador1 = !turnoJugador1;
                accionRealizada = false;
            }
        }

        // Dibujo
        window.clear();

        window.draw(text);
        p1.draw(window);
        p2.draw(window);

        // Dibujar barras de vida
        dibujarBarra(window, p1.getVida(), {50, 550}, sf::Color::Red);
        dibujarBarra(window, p2.getVida(), {550, 550}, sf::Color::Blue);

        window.display();
    }

    return 0;
}

