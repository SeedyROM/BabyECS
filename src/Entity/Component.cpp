//
//  Component.cpp
//  component_system_test
//
//  Created by <author> on 30/03/2017.
//
//

#include "Component.hpp"
#include "Entity.hpp"
#include "../Event/Event.hpp"

void Component::remove() {
    m_parent->removeComponent(this);
}

Entity* Component::getOwner() {
    return m_parent;
}
void Component::setOwner(Entity *_object) {
    m_parent = _object;
}

void Component::fail(const std::string name) {
    std::cout <<
    "No " << name << " found on Owner m_parent, removing this component..."
    << std::endl;
    getOwner()->removeComponent(this);
    delete this;
}
