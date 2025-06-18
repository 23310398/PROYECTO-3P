
#include <SFML/Graphics.hpp>
#include <vector>
#include "Particula.hpp"

extern std::vector<Particula> particulas;

void generarParticulas(sf::Vector2f pos, sf::Color color);
void dibujarBarra(sf::RenderWindow& window, int vida, sf::Vector2f pos, sf::Color color);
void dibujarBarraEnergia(sf::RenderWindow& window, int energia, sf::Vector2f pos, sf::Color color);


