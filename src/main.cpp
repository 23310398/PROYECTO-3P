#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Peleador {
public:
    // Modificar la clase Peleador para aceptar texturas pre-cargadas
    Peleador(sf::Texture& sharedTexture, sf::Vector2f startPos, sf::Color boxColor)
        : vida(100), currentFrame(0), animationTime(0.1f), elapsedTime(0.0f) {
        texture = &sharedTexture; // Usar la textura compartida
        sprite.setTexture(*texture);
        sprite.setPosition(startPos);
        sprite.setScale(1.0f, 1.0f);

        // Configurar el rectángulo inicial del sprite
        frameWidth = 64; // Ancho de cada frame
        frameHeight = 64; // Alto de cada frame
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));

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

    void animate(float deltaTime) {
        // Actualizar el temporizador
        elapsedTime += deltaTime;
        if (elapsedTime >= animationTime) {
            elapsedTime = 0.0f;
            // Cambiar al siguiente frame del sprite sheet
            currentFrame = (currentFrame + 1) % (texture->getSize().x / frameWidth);
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite); // Dibujar solo el sprite del jugador
        //window.draw(hitbox); // Descomenta para ver hitbox si es necesario
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
    sf::Texture* texture; // Apuntar a la textura compartida
    sf::Sprite sprite;
    sf::RectangleShape hitbox;
    int vida;

    // Variables para manejar el sprite sheet
    int frameWidth;
    int frameHeight;
    int currentFrame;

    // Variables para animaciones fluidas
    float animationTime; // Tiempo entre frames
    float elapsedTime;   // Tiempo transcurrido
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
    // Verificar si la fuente se carga correctamente
    if (!font.loadFromFile("./assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente desde ./assets/fonts/Minecraft.ttf\n";
        return -1; // Salir del programa si la fuente no se carga
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

    // Cargar imágenes de ninja y samurai para el menú
    sf::Texture ninjaTexture, samuraiTexture;
    if (!ninjaTexture.loadFromFile("./assets/images/ninja.png") ||
        !samuraiTexture.loadFromFile("./assets/images/samurai.png")) {
        std::cerr << "Error cargando texturas de ninja o samurai para el menú\n";
        return -1;
    }

    sf::Sprite ninjaSprite(ninjaTexture), samuraiSprite(samuraiTexture);
    ninjaSprite.setPosition(200, 200);
    samuraiSprite.setPosition(400, 200);
    ninjaSprite.setScale(0.5f, 0.5f);
    samuraiSprite.setScale(0.5f, 0.5f);

    // Ajustar tamaño y posición de las imágenes del menú
    ninjaSprite.setScale(0.7f, 0.7f); // Hacer la imagen de Ninja más grande
    samuraiSprite.setScale(0.7f, 0.7f); // Hacer la imagen de Samurai más grande

    ninjaSprite.setPosition((800 / 4) - (ninjaSprite.getGlobalBounds().width / 2), 250); // Bajar Ninja
    samuraiSprite.setPosition((800 * 3 / 4) - (samuraiSprite.getGlobalBounds().width / 2), 250); // Bajar Samurai

    // Ajustar el menú para mostrar ninja y samurai
    while (true) {
        window.clear();

        // Mostrar el título "Ninja vs Samurai" centrado en la pantalla
        sf::Text titleText("Ninja vs Samurai", font, 30); // Título con tamaño de fuente 30
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition((800 - titleText.getGlobalBounds().width) / 2, 50); // Centrar horizontalmente
        window.draw(titleText);

        sf::Text menuText("Jugador 1: Presiona E para Ninja\nJugador 2: Presiona B para Samurai\nPresiona Enter para continuar", font, 18);
        menuText.setPosition(20, 150); // Bajar el texto del menú
        menuText.setFillColor(sf::Color::White);
        window.draw(menuText);

        if (seleccionJugador1 == 0) {
            window.draw(ninjaSprite); // Mostrar ninja si no se ha seleccionado
        } else {
            sf::Text label1("Jugador 1 listo", font, 18);
            label1.setPosition(200, 350);
            label1.setFillColor(sf::Color::Green);
            window.draw(label1);
        }

        if (seleccionJugador2 == 0) {
            window.draw(samuraiSprite); // Mostrar samurai si no se ha seleccionado
        } else {
            sf::Text label2("Jugador 2 listo", font, 18);
            label2.setPosition(400, 350);
            label2.setFillColor(sf::Color::Green);
            window.draw(label2);
        }

        window.display();

        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::E && seleccionJugador1 == 0) {
                    seleccionJugador1 = 1;
                    seleccionJugador2 = 2; // El otro jugador recibe el personaje restante
                } else if (ev.key.code == sf::Keyboard::B && seleccionJugador2 == 0) {
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
    // Configurar peleadores con las imágenes originales para el combate
    Peleador p1(
        texture1,
        {100, 400}, sf::Color::Red);
    Peleador p2(
        texture2,
        {600, 400}, sf::Color::Blue);

    // Mover las texturas a variables globales o de mayor alcance
    sf::Texture textureP1, textureP2;
    if (!textureP1.loadFromFile("./assets/images/peleador1.png") ||
        !textureP2.loadFromFile("./assets/images/peleador2.png")) {
        std::cerr << "Error cargando texturas de los peleadores\n";
        return -1;
    }

    // Actualizar teclas de ataque y defensa
    const float speed = 3.0f;

    // Variables para el sistema de turnos
    bool turnoJugador1 = true; // Comienza el jugador 1
    bool accionRealizada = false; // Controla si ya se realizó una acción en el turno

    // Variables para marcador y rondas
    int victoriasJugador1 = 0;
    int victoriasJugador2 = 0;

    // Variable para rastrear la ronda actual
    int rondaActual = 1;

    // Mostrar la ronda actual
    sf::Text rondaText;
    rondaText.setFont(font);
    rondaText.setCharacterSize(20);
    rondaText.setFillColor(sf::Color::White);
    rondaText.setPosition((800 - rondaText.getGlobalBounds().width) / 2, (600 - rondaText.getGlobalBounds().height) / 4 + 50); // Alinear con el marcador y otros textos

    // Modificar la función de reinicio para reutilizar las texturas
    auto reiniciarRonda = [&]() {
        p1 = Peleador(textureP1, {100, 400}, sf::Color::Red);
        p2 = Peleador(textureP2, {600, 400}, sf::Color::Blue);
        rondaActual++;
    };

    // Mostrar marcador
    sf::Text marcadorText;
    marcadorText.setFont(font);
    marcadorText.setCharacterSize(20);
    marcadorText.setFillColor(sf::Color::White);
    marcadorText.setPosition(300, 50); // Posición centrada en la parte superior

    sf::Clock clock; // Reloj para calcular deltaTime
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); // Reiniciar el reloj y obtener el tiempo transcurrido

        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        // Control de turnos con movimiento al atacar o defender
        if (!accionRealizada) {
            // Ajustar el daño infligido por ataque para que sea menor
            const int danioPorAtaque = 5; // Reducir el daño a 5

            // Hacer las animaciones más lentas
            const float tiempoAnimacion = 0.2f; // Aumentar el tiempo entre frames

            // Cambiar turno automáticamente incluso si el jugador elige defender
            if (!accionRealizada) {
                if (turnoJugador1) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { // Ataque del jugador 1
                        p2.recibirDanio(danioPorAtaque);
                        p1.animate(tiempoAnimacion);
                        accionRealizada = true;
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { // Defensa del jugador 1
                        p1.animate(tiempoAnimacion);
                        accionRealizada = true;
                    }
                } else {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { // Ataque del jugador 2
                        p1.recibirDanio(danioPorAtaque);
                        p2.animate(tiempoAnimacion);
                        accionRealizada = true;
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { // Defensa del jugador 2
                        p2.animate(tiempoAnimacion);
                        accionRealizada = true;
                    }
                }

                // Cambiar turno automáticamente después de cualquier acción
                if (accionRealizada) {
                    turnoJugador1 = !turnoJugador1;
                    accionRealizada = false;
                }
            }
        }

        // Verificar si algún jugador se quedó sin vida
        if (p1.getVida() <= 0 || p2.getVida() <= 0) {
            if (p1.getVida() > p2.getVida()) {
                victoriasJugador1++;
                std::cout << "¡Jugador 1 gana la ronda!\n";
            } else if (p2.getVida() > p1.getVida()) {
                victoriasJugador2++;
                std::cout << "¡Jugador 2 gana la ronda!\n";
            } else {
                std::cout << "¡Es un empate!\n";
            }
            reiniciarRonda();
        }

        // Verificar si algún jugador ha ganado 3 rondas
        if (victoriasJugador1 == 3 || victoriasJugador2 == 3) {
            if (victoriasJugador1 == 3) {
                std::cout << "¡Jugador 1 es el ganador final!\n";
            } else {
                std::cout << "¡Jugador 2 es el ganador final!\n";
            }
            window.close();
        }

        // Finalizar el juego al presionar Shift
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            std::cout << "El juego ha sido finalizado manualmente.\n";
            window.close();
        }

        // Finalizar el juego después de 3 rondas
        if (rondaActual > 3) {
            if (victoriasJugador1 > victoriasJugador2) {
                std::cout << "¡Jugador 1 es el ganador final con " << victoriasJugador1 << " victorias!\n";
            } else if (victoriasJugador2 > victoriasJugador1) {
                std::cout << "¡Jugador 2 es el ganador final con " << victoriasJugador2 << " victorias!\n";
            } else {
                std::cout << "¡Es un empate! Ambos jugadores tienen " << victoriasJugador1 << " victorias.\n";
            }
            window.close();
        }

        // Actualizar marcador
        marcadorText.setString("Jugador 1: " + std::to_string(victoriasJugador1) + " | Jugador 2: " + std::to_string(victoriasJugador2));

        // Centrar el texto del marcador
        marcadorText.setPosition((800 - marcadorText.getGlobalBounds().width) / 2, 50);

        // Actualizar el texto de la ronda
        rondaText.setString("Ronda: " + std::to_string(rondaActual));

        // Centrar el texto de las rondas correctamente
        rondaText.setPosition((800 - rondaText.getGlobalBounds().width) / 2, 120); // Centrar horizontalmente y ajustar verticalmente

        // Dibujo
        window.clear();

        // Dibujar el texto del título y el menú
        window.draw(text);

        // Dibujar los sprites de los jugadores
        p1.draw(window); // Dibujar solo el sprite del jugador 1
        p2.draw(window); // Dibujar solo el sprite del jugador 2

        // Dibujar barras de vida
        dibujarBarra(window, p1.getVida(), {50, 550}, sf::Color::Red);
        dibujarBarra(window, p2.getVida(), {550, 550}, sf::Color::Blue);

        // Indicador de turno
        sf::Text turnoText;
        turnoText.setFont(font);
        turnoText.setCharacterSize(20);
        turnoText.setFillColor(sf::Color::Yellow);
        turnoText.setPosition(300, 20); // Posición centrada en la parte superior

        if (turnoJugador1) {
            turnoText.setString("Turno de Jugador 1");
        } else {
            turnoText.setString("Turno de Jugador 2");
        }

        window.draw(turnoText);

        // Dibujar marcador
        window.draw(marcadorText);

        // Dibujar texto de la ronda
        window.draw(rondaText);

        window.display();
    }

    return 0;
}

