#include "../include/Peleador.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Peleador::Peleador(sf::Texture& sharedTexture, sf::Vector2f startPos, sf::Color boxColor, bool voltear)
    : vida(100), energia(0), currentFrame(0), animationTime(0.1f), elapsedTime(0.0f) {
    texture = &sharedTexture;
    frameWidth = 40;
    frameHeight = 29;
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setColor(sf::Color::White);
    if (voltear) {
        sprite.setScale(-4.0f, 4.0f);
        sprite.setOrigin(frameWidth, 0);
        sprite.setPosition(startPos.x + frameWidth, startPos.y);
    } else {
        sprite.setScale(4.0f, 4.0f);
        sprite.setOrigin(0, 0);
        sprite.setPosition(startPos);
    }
    hitbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(boxColor);
    hitbox.setOutlineThickness(1);
    hitbox.setPosition(sprite.getPosition());
}

void Peleador::move(float dx, float dy) {
    sprite.move(dx, dy);
    hitbox.move(dx, dy);
}

void Peleador::animate(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= animationTime) {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % (texture->getSize().x / frameWidth);
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
}

void Peleador::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Peleador::getBounds() const {
    return hitbox.getGlobalBounds();
}

void Peleador::recibirDanio(int cantidad) {
    vida -= cantidad;
    if (vida < 0) vida = 0;
    sprite.setColor(sf::Color::Red);
    // La generación de partículas ahora la maneja la clase Juego
}

void Peleador::cargarEnergia() {
    if (energia < 100) {
        energia += 1;
    }
}

bool Peleador::puedeUsarEspecial() const {
    return energia >= 100;
}

void Peleador::usarEspecial(Peleador& oponente, int jugador) {
    if (puedeUsarEspecial()) {
        if (jugador == 1) {
            oponente.recibirDanio(30);
            oponente.move(-50, 0);
        } else if (jugador == 2) {
            oponente.recibirDanio(20);
            vida += 10;
            if (vida > 100) vida = 100;
        }
        energia = 0;
    }
}

void Peleador::update(float deltaTime) {
    if (sprite.getColor() == sf::Color::Red) {
        sprite.setColor(sf::Color::White);
    }
    animate(deltaTime);
}

int Peleador::getVida() const {
    return vida;
}

int Peleador::getEnergia() const {
    return energia;
}

//fin de codigo