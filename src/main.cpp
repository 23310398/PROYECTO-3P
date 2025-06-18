#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "../include/Peleador.hpp"
#include "../include/Particula.hpp"

using namespace std;
using namespace sf;

// Declarar generarParticulas antes de la clase Peleador
void generarParticulas(sf::Vector2f pos, sf::Color color);

// Declaración global de partículas
std::vector<Particula> particulas;

// Función para generar partículas
void generarParticulas(sf::Vector2f pos, sf::Color color) {
    for (int i = 0; i < 10; ++i) {
        particulas.emplace_back(pos, color);
    }
}

// Función para dibujar barra de vida
void dibujarBarra(sf::RenderWindow& window, int vida, sf::Vector2f pos, sf::Color color) {
    sf::RectangleShape fondo(sf::Vector2f(200, 20));
    fondo.setFillColor(sf::Color(50, 50, 50));
    fondo.setPosition(pos);
    sf::RectangleShape barra(sf::Vector2f(2 * vida, 20));
    barra.setFillColor(color);
    barra.setPosition(pos);
    window.draw(fondo);
    window.draw(barra);
}

// Función para dibujar barra de energía
void dibujarBarraEnergia(sf::RenderWindow& window, int energia, sf::Vector2f pos, sf::Color color) {
    sf::RectangleShape fondo(sf::Vector2f(200, 10));
    fondo.setFillColor(sf::Color(50, 50, 50));
    fondo.setPosition(pos);
    sf::RectangleShape barra(sf::Vector2f(2 * energia, 10));
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
    if (!texture1.loadFromFile("./assets/images/peleador1,2.png") ||
        !texture2.loadFromFile("./assets/images/peleador2,2.png")) {
        std::cerr << "Error cargando texturas para el menú\n";
        return -1;
    }

    sf::Sprite sprite1(texture1), sprite2(texture2);
    sprite1.setPosition(200, 200);
    sprite2.setPosition(600, 200);
    sprite1.setScale(3.0f, 3.0f); // Escalar el personaje 1
    sprite2.setScale(3.0f, 3.0f); // Escalar el personaje 2

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
    samuraiSprite.setPosition(600, 200);
    ninjaSprite.setScale(3.0, 3.0f); // Escalar el ninja
    samuraiSprite.setScale(3.0f, 3.0f); // Escalar el samurai

    // Ajustar tamaño y posición de las imágenes del menú
    ninjaSprite.setScale(1.0f, 1.0f); // Hacer la imagen de Ninja más grande
    samuraiSprite.setScale(1.0f, 1.0f); // Hacer la imagen de Samurai más grande

    ninjaSprite.setPosition((800 / 4) - (ninjaSprite.getGlobalBounds().width / 2), 250); // Bajar Ninja
    samuraiSprite.setPosition((800 * 3 / 4) - (samuraiSprite.getGlobalBounds().width / 2), 250); // Bajar Samurai

    // Cargar la imagen de fondo para la presentación
    sf::Texture fondoPresentacion;
    if (!fondoPresentacion.loadFromFile("./assets/images/FONDO.jpg")) {
        std::cerr << "Error cargando la textura de fondo de presentación\n";
        return -1;
    }

    sf::Sprite fondoSpritePresentacion(fondoPresentacion);
    // Ajustar fondo de presentación
    fondoSpritePresentacion.setScale(
        800.0f / fondoPresentacion.getSize().x,
        600.0f / fondoPresentacion.getSize().y
    );

    // Mostrar la pantalla de presentación con los personajes
    while (true) {
        window.clear();

        // Dibujar el fondo de presentación
        window.draw(fondoSpritePresentacion);

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
            label2.setPosition(600, 350);
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
        {200, 400}, sf::Color::Red, false); // Jugador 1 no volteado
    Peleador p2(
        texture2,
        {400, 400}, sf::Color::Blue, true); // Jugador 2 volteado

    // Mover las texturas a variables globales o de mayor alcance
    sf::Texture textureP1, textureP2;
    if (!textureP1.loadFromFile("./assets/images/peleador1,2.png") ||
        !textureP2.loadFromFile("./assets/images/peleador2,2.png")) {
        std::cerr << "Error cargando texturas de los peleadores\n";
        return -1;
    }

    // Cargar la imagen de fondo para las peleas
    sf::Texture fondoPelea;
    if (!fondoPelea.loadFromFile("./assets/images/FONDO 1.jpg")) {
        std::cerr << "Error cargando la textura de fondo de pelea\n";
        return -1;
    }

    sf::Sprite fondoSpritePelea(fondoPelea);
    // Ajustar fondo de pelea
    fondoSpritePelea.setScale(
        800.0f / fondoPelea.getSize().x,
        600.0f / fondoPelea.getSize().y
    );

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
    auto reiniciarRonda = [&](bool soloRonda = true) {
        p1 = Peleador(textureP1, {200, 400}, sf::Color::Red, false);
        p2 = Peleador(textureP2, {400, 400}, sf::Color::Blue, true);
        if (soloRonda) rondaActual++;
    };

    // Mostrar marcador
    sf::Text marcadorText;
    marcadorText.setFont(font);
    marcadorText.setCharacterSize(20);
    marcadorText.setFillColor(sf::Color::White);
    marcadorText.setPosition(300, 50); // Posición centrada en la parte superior

    sf::Clock clock; // Reloj para calcular deltaTime
    bool gameOver = false;
    int ganador = 0; // 1 para jugador 1, 2 para jugador 2, 0 para empate

    // Cargar la imagen de fondo para la pantalla de Game Over
    sf::Texture fondoGameOver;
    if (!fondoGameOver.loadFromFile("./assets/images/FONDO3.jpg")) {
        std::cerr << "No se pudo cargar la imagen de fondo de Game Over\n";
    }
    sf::Sprite spriteFondoGameOver(fondoGameOver);
    spriteFondoGameOver.setScale(
        800.0f / fondoGameOver.getSize().x,
        600.0f / fondoGameOver.getSize().y
    );

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
        }
        // --- Pantalla de Game Over ---
        if (gameOver) {
            window.clear();
            window.draw(spriteFondoGameOver); // Dibuja el fondo ajustado
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(40);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("GAME OVER");
            gameOverText.setPosition((800 - gameOverText.getGlobalBounds().width) / 2, 100);
            window.draw(gameOverText);
            sf::Text winnerText;
            winnerText.setFont(font);
            winnerText.setCharacterSize(30);
            winnerText.setFillColor(sf::Color::White);
            if (ganador == 1) {
                winnerText.setString("¡Jugador 1 gana!");
            } else if (ganador == 2) {
                winnerText.setString("¡Jugador 2 gana!");
            } else {
                winnerText.setString("¡Empate!");
            }
            winnerText.setPosition((800 - winnerText.getGlobalBounds().width) / 2, 200);
            window.draw(winnerText);
            // Mostrar sprite del ganador
            if (ganador == 1) {
                p1.draw(window);
            } else if (ganador == 2) {
                p2.draw(window);
            }
            // Mensaje para volver a jugar
            sf::Text restartText;
            restartText.setFont(font);
            restartText.setCharacterSize(24);
            restartText.setFillColor(sf::Color::Yellow);
            restartText.setString("Presiona R para volver a jugar o ESC para salir");
            restartText.setPosition((800 - restartText.getGlobalBounds().width) / 2, 350);
            window.draw(restartText);
            window.display();
            // Esperar acción del usuario
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                // Reiniciar variables
                victoriasJugador1 = 0;
                victoriasJugador2 = 0;
                rondaActual = 1;
                reiniciarRonda(false); // Reinicio total, NO suma ronda
                gameOver = false;
                ganador = 0;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            continue;
        }

        // Control de turnos con movimiento al atacar o defender
        // --- Control de turnos robusto: SOLO este bloque debe cambiar turnoJugador1 ---
        static bool teclasSoltadas = true;
        if (teclasSoltadas) {
            const int danioPorAtaque = 5;
            const float tiempoAnimacion = 0.2f;
            bool accion = false;
            if (turnoJugador1) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                    p2.recibirDanio(danioPorAtaque);
                    p1.animate(tiempoAnimacion);
                    turnoJugador1 = false;
                    accion = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                    p1.animate(tiempoAnimacion);
                    turnoJugador1 = false;
                    accion = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                    p1.usarEspecial(p2, 1);
                    turnoJugador1 = false;
                    accion = true;
                }
            } else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                    p1.recibirDanio(danioPorAtaque);
                    p2.animate(tiempoAnimacion);
                    turnoJugador1 = true;
                    accion = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                    p2.animate(tiempoAnimacion);
                    turnoJugador1 = true;
                    accion = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                    p2.usarEspecial(p1, 2);
                    turnoJugador1 = true;
                    accion = true;
                }
            }
            if (accion) teclasSoltadas = false;
        }
        // Solo permitir nueva acción cuando todas las teclas estén soltadas
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            teclasSoltadas = true;
        }
        // --- Fin control de turnos robusto ---

        // Verificar si algún jugador se quedó sin vida
        if (p1.getVida() <= 0 || p2.getVida() <= 0) {
            if (p1.getVida() > p2.getVida()) {
                victoriasJugador1++;
                std::cout << "¡Jugador 1 gana la ronda!\n";
                ganador = 1;
            } else if (p2.getVida() > p1.getVida()) {
                victoriasJugador2++;
                std::cout << "¡Jugador 2 gana la ronda!\n";
                ganador = 2;
            } else {
                std::cout << "¡Es un empate!\n";
                ganador = 0;
            }
            gameOver = (victoriasJugador1 == 3 || victoriasJugador2 == 3); // Verificar si hay un ganador final
            reiniciarRonda(); // Solo cambio de ronda, suma 1
        }

        // Verificar si algún jugador ha ganado 3 rondas
        if (victoriasJugador1 == 3 || victoriasJugador2 == 3) {
            if (victoriasJugador1 == 3) {
                ganador = 1;
            } else if (victoriasJugador2 == 3) {
                ganador = 2;
            } else {
                ganador = 0;
            }
            gameOver = true;
        }

        // Finalizar el juego después de 3 rondas
        if (rondaActual > 3) {
            if (victoriasJugador1 > victoriasJugador2) {
                ganador = 1;
            } else if (victoriasJugador2 > victoriasJugador1) {
                ganador = 2;
            } else {
                ganador = 0;
            }
            gameOver = true;
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

        // Dibujar el fondo de pelea
        window.draw(fondoSpritePelea);

        // Dibujar el texto del título y el menú
        window.draw(text);

        // Dibujar los sprites de los jugadores
        p1.draw(window);
        p2.draw(window);

        // Dibujar barras de vida
        dibujarBarra(window, p1.getVida(), {50, 550}, sf::Color::Red);
        dibujarBarra(window, p2.getVida(), {550, 550}, sf::Color::Blue);

        // Asegurarse de que la energía del jugador 2 también se actualice correctamente
        auto actualizarEnergia = [&]() {
            p1.cargarEnergia();
            p2.cargarEnergia();
        };

        // En el bucle principal, llamar a la función para actualizar la energía
        actualizarEnergia();

        // Dibujar barras de energía para ambos jugadores
        dibujarBarraEnergia(window, p1.getEnergia(), {50, 530}, sf::Color::Yellow);
        dibujarBarraEnergia(window, p2.getEnergia(), {550, 530}, sf::Color::Yellow);

        // Revisar y ajustar la lógica de los ataques especiales para evitar bloqueos
        if (turnoJugador1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && p1.puedeUsarEspecial()) { // Ataque especial del jugador 1
                p1.usarEspecial(p2, 1);
                turnoJugador1 = false; // Cambiar turno inmediatamente
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { // Ataque normal del jugador 1
                p2.recibirDanio(5);
                turnoJugador1 = false;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { // Defensa del jugador 1
                turnoJugador1 = false;
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && p2.puedeUsarEspecial()) { // Ataque especial del jugador 2
                p2.usarEspecial(p1, 2);
                turnoJugador1 = true; // Cambiar turno inmediatamente
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { // Ataque normal del jugador 2
                p1.recibirDanio(5);
                turnoJugador1 = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { // Defensa del jugador 2
                turnoJugador1 = true;
            }
        }

        // Asegurar que la energía se actualice correctamente en cada frame
        actualizarEnergia();

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

        // Actualizar y dibujar partículas
        for (auto it = particulas.begin(); it != particulas.end();) {
            it->update(deltaTime);
            if (!it->isAlive()) {
                it = particulas.erase(it);
            } else {
                ++it;
            }
        }

        for (const auto& particula : particulas) {
            particula.draw(window);
        }

        window.display();
    }

    return 0;
}

