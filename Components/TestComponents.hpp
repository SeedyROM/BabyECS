//
//  TestComponent.hpp
//  component_system_test
//
//  Created by <author> on 02/04/2017.
//
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../Entity/Entity.hpp"
#include "../Entity/Component.hpp"

namespace Test {
    struct Transform : Component {
        sf::Vector2f position;
        sf::Vector2f scale;
        float rotation;
    };
    struct Velocity : Component {
        float x, y;
        Transform *transform;

        void onAdd() override {
            transform = getParent()->getComponent<Transform>();
        }
        void update(float dt) override {
            transform->position = calculateNewPosition(dt);
        }
        void onRemove() override {
            printf("TestComponent removed!\n");
        }

        sf::Vector2f calculateNewPosition(float dt) {
            return sf::Vector2f(transform->position.x + x * dt, transform->position.y + y * dt);
        }
    };
}
