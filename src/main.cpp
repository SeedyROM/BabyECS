#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Components/TestComponents.hpp"

int main(int argc, char* argv[])
{
    // Non-encapsulated entity.
    Entity o;
    auto transform = o.addComponent<Test::Transform>();
    auto velocity = o.addComponent<Test::Velocity>();
    auto sprite = o.addComponent<Test::Sprite>();
    auto boundingBox = o.addComponent<Test::BoundingBox>();

    sf::Texture texture;
    texture.loadFromFile(__SRC_DIR__ + "/Images/test.png");

    transform->position = sf::Vector2f(150, 150);
    sprite->setTexture(texture);
    boundingBox->setSize(sprite->getLocalBounds());
    transform->centerOrigin(sprite->getLocalBounds());

    velocity->x = 30;

    sf::RenderWindow window(sf::VideoMode(850, 500), "BabyECS");
    window.setFramerateLimit(120);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        o.getComponent<Test::Velocity>()->update(1 / 120.f);
        o.getComponent<Test::Transform>()->rotation += 2;

        window.clear();
        o.getComponent<Test::Sprite>()->draw(window);
        o.getComponent<Test::BoundingBox>()->draw(window);
        window.display();
    }

    return 0;
}
