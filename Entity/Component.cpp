//
//  Component.cpp
//  component_system_test
//
//  Created by <author> on 30/03/2017.
//
//

#include "Entity.hpp"
#include "Component.hpp"

void Component::remove() {
    object->removeComponent(this);
}

Entity* Component::getParent() {
    return object;
}
void Component::setParent(Entity *_object) {
    object = _object;
}
