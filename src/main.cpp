#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Peleador {
public:
    Peleador(const std::string& texturePath, sf::Vector2f startPos, sf::Color boxColor) {
        if (!texture.loadFromFile(texturePath)) std::cerr<<"Error cargando "<<texturePath<<"\n";
        sprite.setTexture(texture);
        sprite.setPosition(startPos);
        hitbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(boxColor);
        hitbox.setOutlineThickness(1);
        hitbox.setPosition(startPos);
    }
    void move(float dx, float dy){
        sprite.move(dx,dy);
        hitbox.move(dx,dy);
    }
    void draw(sf::RenderWindow &w){
        w.draw(sprite);
        w.draw(hitbox);  // Puedes comentar esta línea para ocultar hitbox
    }
    sf::FloatRect getBounds() const {
        return hitbox.getGlobalBounds();
    }
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape hitbox;
};

int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "Juego de Pelea");
    window.setFramerateLimit(60);

    sf::Music music;
    if(!music.openFromFile("./assets/music/musica.ogg"))
        std::cerr<<"Error cargando musica.ogg\n";
    else {
        music.setLoop(true);
        music.play();
    }

    sf::Font font;
    if(!font.loadFromFile("./assets/fonts/Minecraft.ttf"))
        std::cerr<<"Error cargando fuente\n";
    sf::Text text("¡Combate!", font, 30);
    text.setPosition(300,10);
    text.setFillColor(sf::Color::White);

    Peleador p1("./assets/images/peleador1.png", {100,400}, sf::Color::Red);
    Peleador p2("./assets/images/peleador2.png", {600,400}, sf::Color::Blue);
    const float speed = 3.0f;
    
    while(window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev))
            if(ev.type == sf::Event::Closed)
                window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) p1.move(-speed,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) p1.move(speed,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) p1.move(0,-speed);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) p1.move(0,speed);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p2.move(-speed,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p2.move(speed,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) p2.move(0,-speed);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) p2.move(0,speed);

        if(p1.getBounds().intersects(p2.getBounds())){
            text.setString("¡Golpe!");
            text.setFillColor(sf::Color::Yellow);
        } else {
            text.setString("¡Combate!");
            text.setFillColor(sf::Color::White);
        }

        window.clear();
        window.draw(text);
        p1.draw(window);
        p2.draw(window);
        window.display();
    }
    return 0;
}
