//
//  TestComponent.hpp
//  component_system_test
//
//  Created by <author> on 02/04/2017.
//
//

#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "../Entity/Entity.hpp"
#include "../Entity/Component.hpp"

namespace Test {
    struct Transform : Component {
        sf::Vector2f position;
        sf::Vector2f scale;
        sf::Vector2f origin;
        float rotation;

        Transform() : scale(1, 1) {}

        void centerOrigin(sf::FloatRect rect) {
            origin.x = rect.width / 2;
            origin.y = rect.height / 2;
        }
    };
    struct Velocity : Component {
        float x, y;
        Transform *transform;

        void onAdd() override {
            transform = getParent()->getComponent<Transform>();
            if(transform == nullptr) {
                failWithMissingComponent<Transform>();
            }
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
        sf::Vector2f asVector2f() {
            return sf::Vector2f(x, y);
        }
    };
    struct Sprite : public sf::Sprite, Component {
        Transform *transform;

        void onAdd() override {
            transform = getParent()->getComponent<Transform>();
            if(transform == nullptr) {
                failWithMissingComponent<Transform>();
            }
        }

        void draw(sf::RenderWindow &window) override {
            setOrigin(transform->origin);
            setPosition(transform->position);
            setScale(transform->scale);
            setRotation(transform->rotation);
            window.draw(*this);
        }
    };
    struct BoundingBox : Component {
        Transform *transform;
        float width, height;

        void onAdd() override {
            transform = getParent()->getComponent<Transform>();
            if(transform == nullptr) {
                failWithMissingComponent<Transform>();
            }
        }

        void draw(sf::RenderWindow &window) override {
            sf::RectangleShape boxShape;
            boxShape.setSize(sf::Vector2f(width * transform->scale.x, height * transform->scale.y));
            boxShape.setPosition(transform->position);
            boxShape.setRotation(transform->rotation);
            boxShape.setOrigin(transform->origin);
            boxShape.setFillColor(sf::Color::Transparent);
            boxShape.setOutlineColor(sf::Color::Green);
            boxShape.setOutlineThickness(2);
            window.draw(boxShape);
        }

        void setSize(const sf::Vector2f &size) {
            width = size.x;
            height = size.y;
        }
        void setSize(const sf::FloatRect &size) {
            width = size.width;
            height = size.height;
        }
    };
 }
