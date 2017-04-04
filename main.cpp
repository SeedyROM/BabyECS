#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Components/TestComponents.hpp"

int main(int argc, char* argv[])
{
    Entity o;
    auto transform = o.addComponent<Test::Transform>();
    auto velocity = o.addComponent<Test::Velocity>();
    velocity->x = 12;

    sf::RenderWindow window(sf::VideoMode(850, 500), "BabyECS");
    window.setFramerateLimit(120);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        o.getComponent<Test::Velocity>()->update(1 / 60.f);
        shape.setPosition(transform->position.x, transform->position.y);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
