#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/Peleador.hpp"
#include "../include/Particula.hpp"
#include <vector>

class Juego {
public:
    Juego();
    void run();

private:
    void mostrarPantallaPresentacion();
    void iniciarRonda();
    void mostrarGameOver();
    void actualizar();
    void dibujar();
    void manejarEventos();
    void generarParticulas(sf::Vector2f pos, sf::Color color);
    void dibujarBarra(sf::RenderWindow& window, int vida, sf::Vector2f pos, sf::Color color);
    void dibujarBarraEnergia(sf::RenderWindow& window, int energia, sf::Vector2f pos, sf::Color color);
    void reiniciarRonda(bool soloRonda = true);

    sf::RenderWindow window;
    sf::Font font;
    sf::Music music;
    sf::Texture texture1, texture2, ninjaTexture, samuraiTexture, fondoPresentacion, fondoPelea, fondoGameOver;
    sf::Sprite sprite1, sprite2, ninjaSprite, samuraiSprite, fondoSpritePresentacion, fondoSpritePelea, spriteFondoGameOver;
    Peleador p1, p2;
    std::vector<Particula> particulas;
    int seleccionJugador1;
    int seleccionJugador2;
    int victoriasJugador1;
    int victoriasJugador2;
    int rondaActual;
    bool turnoJugador1;
    bool accionRealizada;
    bool gameOver;
    int ganador;
    sf::Text text, rondaText, marcadorText, turnoText;
    sf::Clock clock;
};
