#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Components/TestComponents.hpp"

int main(int argc, char* argv[])
{
    Entity o;
    auto pos = o.addComponent<MovementComponent>();
    pos->position.x = 12;
    pos->velocity.x = 4;

    sf::RenderWindow window(sf::VideoMode(850, 500), "SFML works!");
    window.setFramerateLimit(120);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        o.getComponent<MovementComponent>()->update(1 / 60.f);

        shape.setPosition(pos->position.x, pos->position.y);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
