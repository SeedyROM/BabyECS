#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity/Entity.hpp"
#include "Entity/Component.hpp"
#include "Event/Event.hpp"
#include "Components/TestComponents.hpp"

// Just for testing, because I'm too lazy for C++ TDD.
using namespace Test;

//
// Essentially a factory for Entity's that are all generally the same.
//
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

//
// Create a component that listens for events we send it, and sends back the type name.
//
struct EventEcho : Component {
    void sendEvent(Event &event) override {
        std::cout << event.type() << " was received, over." << std::endl;

        if(event.type() == "TestingTestEvent") {
            auto v = getOwner()->getComponent<Velocity>();
            v->setX(v->getX() * -1.2f);
        }
    }
};

int main(int argc, char* argv[])
{
    // Load an image for testing reasons.
    sf::Texture texture;
    texture.loadFromFile(__SRC_DIR__ + "/Images/test.png");

    // Create a test event to pass later...
    auto aEvent = ATest();
    auto bEvent = TestingTestEvent();

    // Setup our gameobject test.
    GameObject o;
    o.getComponent<Sprite>()->setTexture(texture);
    o.getComponent<Transform>()->setPosition(sf::Vector2f(150, 150));
    o.getComponent<Velocity>()->set(sf::Vector2f(30, 15));
    o.setupBoundingBox();

    // Add our echo component.
    o.addComponent<EventEcho>();
    o.sendEvent<EventEcho>(aEvent);

    sf::RenderWindow window(sf::VideoMode(850, 500), "BabyECS");
    window.setFramerateLimit(120);

    int t;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Send some events periodically because why not?
        if(t % 300 == 0) o.sendEvent<EventEcho>(bEvent);
        if(t % 150 == 0) o.sendEvent<EventEcho>(aEvent);

        o.update(1 / 120.f);

        window.clear(sf::Color(0, 0, 0));
        o.draw(window);
        window.display();
        t++;
    }

    return 0;
}
