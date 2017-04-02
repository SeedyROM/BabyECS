//
//  TestComponent.hpp
//  component_system_test
//
//  Created by <author> on 02/04/2017.
//
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Entity/Component.hpp"

struct TestComponent : Component {
    sf::Vector2f position;
    sf::Vector2f velocity;

    void onAdd() {
        printf("Added a TestComponent with parent: %d\n", object);
    }
    void beginStep(float dt) override {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        printf("x: %f | y: %f\n", position.x, position.y);
    }
    void onRemove() override {
        printf("TestComponent removed!\n");
    }
};
