//
//  Entity.hpp
//  component_system_test
//
//  Created by Zack Kollar on 30/03/2017.
//
//

#pragma once

#include <unordered_map>
#include <typeinfo>
#include <SFML/Graphics.hpp>

#include "Component.hpp"

struct Entity {
    typedef std::unordered_map<std::string, bool> State;
    typedef std::vector<Component *> Components;

    Entity();
    ~Entity();
    State* getState();
    void setState(const std::string key, bool value);
    Components& getComponents();

    void addComponent(Component *component);
    void removeComponent(Component *component);

    //
    // Templated methods..
    //

    // Add component by type.
    template<typename T>
    T* addComponent() {
        T* component = new T();
        addComponent(component);
        return component;
    }

    // Get by component type.
    template<typename T>
    T* getComponent() {
        for(auto &c : m_components) {
            if(typeid(*c) == typeid(T)) {
                return static_cast<T*>(c);
            }
        }
        return nullptr;
    }

    // Remove by component type.
    template<typename T>
    void removeComponent() {
        for(auto c = m_components.begin(); c != m_components.end(); c++) {
            if(typeid(**c) == typeid(T)) {
                (*c)->onRemove();
                m_components.erase(c);
                return;
            }
        }
    }


private:
    State *m_state;
    Components m_components;
};
