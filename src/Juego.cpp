#include "../include/Juego.hpp"
#include <iostream>

Juego::Juego()
    : window(sf::VideoMode(800, 600), "Juego de Pelea"),
      seleccionJugador1(0), seleccionJugador2(0),
      victoriasJugador1(0), victoriasJugador2(0),
      rondaActual(1), turnoJugador1(true), accionRealizada(false),
      gameOver(false), ganador(0),
      p1(texture1, {200, 400}, sf::Color::Red, false),
      p2(texture2, {400, 400}, sf::Color::Blue, true) {
    window.setFramerateLimit(60);
    // Cargar fuente
    if (!font.loadFromFile("./assets/fonts/Minecraft.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente desde ./assets/fonts/Minecraft.ttf\n";
    }
    // Cargar música
    if (!music.openFromFile("./assets/music/musica.ogg")) {
        std::cerr << "Error cargando musica.ogg\n";
    } else {
        music.setLoop(true);
        music.play();
    }
    // Cargar texturas
    texture1.loadFromFile("./assets/images/peleador1,2.png");
    texture2.loadFromFile("./assets/images/peleador2,2.png");
    ninjaTexture.loadFromFile("./assets/images/ninja.png");
    samuraiTexture.loadFromFile("./assets/images/samurai.png");
    fondoPresentacion.loadFromFile("./assets/images/FONDO.jpg");
    fondoPelea.loadFromFile("./assets/images/FONDO 1.jpg");
    fondoGameOver.loadFromFile("./assets/images/FONDO3.jpg");
    // Configurar sprites
    sprite1.setTexture(texture1);
    sprite2.setTexture(texture2);
    ninjaSprite.setTexture(ninjaTexture);
    samuraiSprite.setTexture(samuraiTexture);
    fondoSpritePresentacion.setTexture(fondoPresentacion);
    fondoSpritePelea.setTexture(fondoPelea);
    spriteFondoGameOver.setTexture(fondoGameOver);
    // Escalados y posiciones iniciales pueden ajustarse aquí
}

void Juego::run() {
    mostrarPantallaPresentacion();
    iniciarRonda();
    while (window.isOpen()) {
        manejarEventos();
        actualizar();
        dibujar();
    }
}

// Métodos auxiliares (declaraciones vacías, implementarás la lógica después)
void Juego::mostrarPantallaPresentacion() {
    // Menú para seleccionar personajes con imágenes y letras debajo
    sprite1.setPosition(200, 200);
    sprite2.setPosition(600, 200);
    sprite1.setScale(3.0f, 3.0f);
    sprite2.setScale(3.0f, 3.0f);
    ninjaSprite.setScale(1.0f, 1.0f);
    samuraiSprite.setScale(1.0f, 1.0f);
    ninjaSprite.setPosition((800 / 4) - (ninjaSprite.getGlobalBounds().width / 2), 250);
    samuraiSprite.setPosition((800 * 3 / 4) - (samuraiSprite.getGlobalBounds().width / 2), 250);
    fondoSpritePresentacion.setScale(
        800.0f / fondoPresentacion.getSize().x,
        600.0f / fondoPresentacion.getSize().y
    );
    seleccionJugador1 = 0;
    seleccionJugador2 = 0;
    sf::Text titleText("Ninja vs Samurai", font, 30);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition((800 - titleText.getGlobalBounds().width) / 2, 50);
    sf::Text menuText("Jugador 1: Presiona E para Ninja\nJugador 2: Presiona B para Samurai\nPresiona Enter para continuar", font, 18);
    menuText.setPosition(20, 150);
    menuText.setFillColor(sf::Color::White);
    while (true) {
        window.clear();
        window.draw(fondoSpritePresentacion);
        window.draw(titleText);
        window.draw(menuText);
        if (seleccionJugador1 == 0) {
            window.draw(ninjaSprite);
        } else {
            sf::Text label1("Jugador 1 listo", font, 18);
            label1.setPosition(200, 350);
            label1.setFillColor(sf::Color::Green);
            window.draw(label1);
        }
        if (seleccionJugador2 == 0) {
            window.draw(samuraiSprite);
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
                return;
            }
            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::E && seleccionJugador1 == 0) {
                    seleccionJugador1 = 1;
                    seleccionJugador2 = 2;
                } else if (ev.key.code == sf::Keyboard::B && seleccionJugador2 == 0) {
                    seleccionJugador1 = 2;
                    seleccionJugador2 = 1;
                } else if (ev.key.code == sf::Keyboard::Enter) {
                    if (seleccionJugador1 != 0 && seleccionJugador2 != 0) {
                        return;
                    }
                }
            }
        }
    }
}

void Juego::iniciarRonda() {
    // Inicializa los peleadores y variables de ronda
    p1 = Peleador(texture1, {200, 400}, sf::Color::Red, false);
    p2 = Peleador(texture2, {400, 400}, sf::Color::Blue, true);
    rondaActual = 1;
    victoriasJugador1 = 0;
    victoriasJugador2 = 0;
    turnoJugador1 = true;
    accionRealizada = false;
    gameOver = false;
    ganador = 0;
    particulas.clear();
}

void Juego::mostrarGameOver() {
    window.clear();
    // Escalar el fondo de Game Over a la ventana
    spriteFondoGameOver.setScale(
        800.0f / fondoGameOver.getSize().x,
        600.0f / fondoGameOver.getSize().y
    );
    window.draw(spriteFondoGameOver);
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
        victoriasJugador1 = 0;
        victoriasJugador2 = 0;
        rondaActual = 1;
        reiniciarRonda(false);
        gameOver = false;
        ganador = 0;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
}

void Juego::actualizar() {
    float deltaTime = clock.restart().asSeconds();
    // Control de turnos y acciones
    static bool teclasSoltadas = true;
    if (teclasSoltadas) {
        const int danioPorAtaque = 5;
        const float tiempoAnimacion = 0.2f;
        bool accion = false;
        if (turnoJugador1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                p2.recibirDanio(danioPorAtaque);
                generarParticulas(p2.getBounds().getPosition(), sf::Color::Yellow); // Generar partículas al recibir daño
                p1.animate(tiempoAnimacion);
                turnoJugador1 = false;
                accion = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                p1.animate(tiempoAnimacion);
                turnoJugador1 = false;
                accion = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                p1.usarEspecial(p2, 1);
                generarParticulas(p2.getBounds().getPosition(), sf::Color::Yellow); // Partículas para especial
                turnoJugador1 = false;
                accion = true;
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                p1.recibirDanio(danioPorAtaque);
                generarParticulas(p1.getBounds().getPosition(), sf::Color::Yellow); // Generar partículas al recibir daño
                p2.animate(tiempoAnimacion);
                turnoJugador1 = true;
                accion = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                p2.animate(tiempoAnimacion);
                turnoJugador1 = true;
                accion = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                p2.usarEspecial(p1, 2);
                generarParticulas(p1.getBounds().getPosition(), sf::Color::Yellow); // Partículas para especial
                turnoJugador1 = true;
                accion = true;
            }
        }
        if (accion) teclasSoltadas = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        teclasSoltadas = true;
    }
    // Actualizar energía
    p1.cargarEnergia();
    p2.cargarEnergia();
    // Actualizar partículas
    for (auto it = particulas.begin(); it != particulas.end();) {
        it->update(deltaTime);
        if (!it->IsAlive()) {
            it = particulas.erase(it);
        } else {
            ++it;
        }
    }
    // Verificar fin de ronda o juego
    if (p1.getVida() <= 0 || p2.getVida() <= 0) {
        if (p1.getVida() > p2.getVida()) {
            victoriasJugador1++;
            ganador = 1;
        } else if (p2.getVida() > p1.getVida()) {
            victoriasJugador2++;
            ganador = 2;
        } else {
            ganador = 0;
        }
        gameOver = (victoriasJugador1 == 3 || victoriasJugador2 == 3);
        reiniciarRonda();
    }
    if (victoriasJugador1 == 3 || victoriasJugador2 == 3 || rondaActual > 3) {
        if (victoriasJugador1 > victoriasJugador2) {
            ganador = 1;
        } else if (victoriasJugador2 > victoriasJugador1) {
            ganador = 2;
        } else {
            ganador = 0;
        }
        gameOver = true;
    }
}
void Juego::dibujar() {
    window.clear();
    // Escalar el fondo de pelea a la ventana
    fondoSpritePelea.setScale(
        800.0f / fondoPelea.getSize().x,
        600.0f / fondoPelea.getSize().y
    );
    window.draw(fondoSpritePelea);
    // Peleadores
    p1.draw(window);
    p2.draw(window);
    // Barras de vida y energía
    dibujarBarra(window, p1.getVida(), {50, 550}, sf::Color::Red);
    dibujarBarra(window, p2.getVida(), {550, 550}, sf::Color::Blue);
    dibujarBarraEnergia(window, p1.getEnergia(), {50, 530}, sf::Color::Yellow);
    dibujarBarraEnergia(window, p2.getEnergia(), {550, 530}, sf::Color::Yellow);
    // Partículas
    for (const auto& particula : particulas) {
        particula.Draw(window);
    }
    // Marcador y ronda
    marcadorText.setFont(font);
    marcadorText.setCharacterSize(20);
    marcadorText.setFillColor(sf::Color::White);
    marcadorText.setString("Jugador 1: " + std::to_string(victoriasJugador1) + " | Jugador 2: " + std::to_string(victoriasJugador2));
    marcadorText.setPosition((800 - marcadorText.getGlobalBounds().width) / 2, 50);
    window.draw(marcadorText);
    rondaText.setFont(font);
    rondaText.setCharacterSize(20);
    rondaText.setFillColor(sf::Color::White);
    rondaText.setString("Ronda: " + std::to_string(rondaActual));
    rondaText.setPosition((800 - rondaText.getGlobalBounds().width) / 2, 120);
    window.draw(rondaText);
    // Turno
    turnoText.setFont(font);
    turnoText.setCharacterSize(20);
    turnoText.setFillColor(sf::Color::Yellow);
    turnoText.setPosition(300, 20);
    turnoText.setString(turnoJugador1 ? "Turno de Jugador 1" : "Turno de Jugador 2");
    window.draw(turnoText);
    // Game Over
    if (gameOver) {
        mostrarGameOver();
        return;
    }
    window.display();
}

void Juego::manejarEventos() {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            window.close();
        // Aquí puedes agregar el manejo de teclas para el menú, reinicio, etc.
    }
}

void Juego::generarParticulas(sf::Vector2f pos, sf::Color color) {
    for (int i = 0; i < 10; ++i) {
        particulas.emplace_back(pos, color);
    }
}

void Juego::dibujarBarra(sf::RenderWindow& window, int vida, sf::Vector2f pos, sf::Color color) {
    sf::RectangleShape fondo(sf::Vector2f(200, 20));
    fondo.setFillColor(sf::Color(50, 50, 50));
    fondo.setPosition(pos);
    sf::RectangleShape barra(sf::Vector2f(2 * vida, 20));
    barra.setFillColor(color);
    barra.setPosition(pos);
    window.draw(fondo);
    window.draw(barra);
}

void Juego::dibujarBarraEnergia(sf::RenderWindow& window, int energia, sf::Vector2f pos, sf::Color color) {
    sf::RectangleShape fondo(sf::Vector2f(200, 10));
    fondo.setFillColor(sf::Color(50, 50, 50));
    fondo.setPosition(pos);
    sf::RectangleShape barra(sf::Vector2f(2 * energia, 10));
    barra.setFillColor(color);
    barra.setPosition(pos);
    window.draw(fondo);
    window.draw(barra);
}

void Juego::reiniciarRonda(bool soloRonda) {
    p1 = Peleador(texture1, {200, 400}, sf::Color::Red, false);
    p2 = Peleador(texture2, {400, 400}, sf::Color::Blue, true);
    if (soloRonda) rondaActual++;
    particulas.clear();
}
