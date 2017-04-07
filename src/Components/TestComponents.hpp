//
//  TestComponent.hpp
//  BabyECS
//
//  Created by Zack Kollar on 02/04/2017.
//
//

#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../Entity/Entity.hpp"
#include "../Entity/Component.hpp"
#include "../Event/Event.hpp"

namespace Test {
    struct Transform : Component {
        Transform()
        : m_scale( 1, 1), m_position(0, 0),
          m_origin(0, 0), m_rotation(0) {}

        void centerOrigin(sf::FloatRect rect) {
            m_origin.x = rect.width / 2;
            m_origin.y = rect.height / 2;
        }

        sf::Vector2f getPosition() const                { return m_position; }
        void         setPosition(sf::Vector2f position) { m_position = position; }
        sf::Vector2f getScale() const                   { return m_scale; }
        void         setScale(sf::Vector2f scale)       { m_scale = scale; }
        sf::Vector2f getOrigin() const                  { return m_origin; }
        void         setOrigin(sf::Vector2f origin)     { m_origin = origin; }
        float        getRotation() const                { return m_rotation; }
        void         setRotation(float rotation)        { m_rotation = rotation; }

        void rotate(float angle) {
            m_rotation += angle;
        }
        void move(float x, float y) {
            m_position = sf::Vector2f(m_position.x + x, m_position.y + y);
        }

    protected:
        sf::Vector2f m_position;
        sf::Vector2f m_scale;
        sf::Vector2f m_origin;
        float m_rotation;
    };
    struct Velocity : Component {
        void onAdd() override {
            m_transform = getOwner()->getComponent<Transform>();
            if(m_transform == nullptr) {
                failWithMissingComponent<Transform>();
            }
        }
        void update(float dt) override {
            m_transform->setPosition(calculateNewPosition(dt));
        }

        float getX() const  { return m_x; }
        void  setX(float x) { m_x = x; }
        float getY() const  { return m_y; }
        void  setY(float y) { m_y = y; }

        sf::Vector2f calculateNewPosition(float dt) {
            return sf::Vector2f(m_transform->getPosition().x + m_x * dt, m_transform->getPosition().y + m_y * dt);
        }

        void set(sf::Vector2f dimensions) {
            m_x = dimensions.x;
            m_y = dimensions.y;
        }
        sf::Vector2f get() {
            return sf::Vector2f(m_x, m_y);
        }

    protected:
        float m_x, m_y;
        Transform *m_transform;
    };
    struct Sprite : public sf::Sprite, Component {
        void onAdd() override {
            m_transform = getOwner()->getComponent<Transform>();
            if(m_transform == nullptr) {
                failWithMissingComponent<Transform>();
            }
        }
        void draw(sf::RenderWindow &window) override {
            setOrigin(m_transform->getOrigin());
            setPosition(m_transform->getPosition());
            setScale(m_transform->getScale());
            setRotation(m_transform->getRotation());
            window.draw(*this);
        }

    protected:
        Transform *m_transform;
    };
    struct BoundingBox : Component {
        void onAdd() override {
            auto object = getOwner();
            m_transform = object->getComponent<Transform>();
            if(m_transform == nullptr) {
                failWithMissingComponent<Transform>();
            }
        }
        void draw(sf::RenderWindow &window) override {
            sf::RectangleShape boxShape;
            boxShape.setSize(sf::Vector2f(m_width * m_transform->getScale().x, m_height * m_transform->getScale().y));
            boxShape.setOrigin(m_transform->getOrigin());
            boxShape.setPosition(m_transform->getPosition());
            boxShape.setRotation(m_transform->getRotation());
            boxShape.setFillColor(sf::Color::Transparent);
            boxShape.setOutlineColor(sf::Color::Green);
            boxShape.setOutlineThickness(2);
            window.draw(boxShape);
        }

        void setSize(const float width, const float height) {
            m_width = width;
            m_height = height;
        }
        void setSize(const sf::Vector2f &size) {
            m_width = size.x;
            m_height = size.y;
        }
        void setSize(const sf::FloatRect &size) {
            m_width = size.width;
            m_height = size.height;
        }


    protected:
        Transform *m_transform;
        float m_width, m_height;
    };
 }
