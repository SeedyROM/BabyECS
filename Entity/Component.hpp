//
//  Component.hpp
//  component_system_test
//
//  Created by Zack Kollar on 30/03/2017.
//
//

#pragma once

#include <algorithm>

class Entity;
struct Component {
    virtual ~Component() {}
    virtual void onAdd() {}
    virtual void onRemove() {}
    virtual void update(float dt) {}

    void remove();
    Entity* getParent();
    void setParent(Entity *_object);

protected:
    Entity* object;
};
