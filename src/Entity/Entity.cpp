//
//  Entity.cpp
//  component_system_test
//
//  Created by <author> on 30/03/2017.
//
//

#include "Entity.hpp"

Entity::Entity()  {
    m_state = new Entity::State();
}
Entity::~Entity() {
    delete m_state;
}

Entity::State* Entity::getState() {
    return m_state;
}
void Entity::setState(const std::string key, bool value) {
    (*m_state)[key] = value;
}
Entity::Components& Entity::getComponents() {
    return m_components;
}

void Entity::addComponent(Component *component) {
    component->setParent(this);
    component->onAdd();
    m_components.push_back(component);
}

// Remove by reference.
void Entity::removeComponent(Component *component) {
    for(auto c = m_components.begin(); c != m_components.end(); c++) {
        if(component == *c) {
            (*c)->onRemove();
            m_components.erase(c);
            return;
        }
    }
}
