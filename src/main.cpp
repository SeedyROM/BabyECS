#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Event/Event.hpp"
#include "Components/TestComponents.hpp"

using namespace Test;

struct GameObject : Entity {
    GameObject() {
        addComponent<Transform>();
        addComponent<Velocity>();
        addComponent<Sprite>();
        addComponent<BoundingBox>();
    }
    GameObject(float x, float y) : GameObject() {
        getComponent<Transform>()->setPosition(sf::Vector2f(x, y));
    }

    void setupBoundingBox() {
        if(hasComponent<Sprite>()) {
            getComponent<BoundingBox>()->setSize(
                getComponent<Sprite>()->getLocalBounds()
            );
            getComponent<Transform>()->centerOrigin(
                getComponent<Sprite>()->getLocalBounds()
            );
        }
    }
};

int main(int argc, char* argv[])
{
    sf::Texture texture;
    texture.loadFromFile(__SRC_DIR__ + "/Images/test.png");

    GameObject o;
    o.getComponent<Sprite>()->setTexture(texture);
    o.getComponent<Transform>()->setPosition(sf::Vector2f(150, 150));
    o.getComponent<Velocity>()->set(sf::Vector2f(30, 15));
    Event dummyEvent = Event();
    o.getComponent<Velocity>()->sendEvent(dummyEvent);
    o.setupBoundingBox();

    sf::RenderWindow window(sf::VideoMode(850, 500), "BabyECS");
    window.setFramerateLimit(120);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        o.getComponent<Transform>()->rotate(5);
        o.update(1 / 120.f);

        window.clear(sf::Color(0, 0, 0));
        o.draw(window);
        window.display();
    }

    return 0;
}
