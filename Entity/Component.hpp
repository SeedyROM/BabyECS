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

    void update(float dt);
    void remove();

    Entity* getParent();
    void setParent(Entity *_object);

protected:
    Entity* object;

private:
    virtual void beginStep(float dt) {}
    virtual void step(float dt) {}
    virtual void endStep(float dt) {}
};
