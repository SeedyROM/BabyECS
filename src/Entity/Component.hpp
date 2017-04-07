//
//  Component.hpp
//  component_system_test
//
//  Created by Zack Kollar on 30/03/2017.
//
//

#pragma once

#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <queue>
#include <SFML/Graphics.hpp>

#include "../Helpers/GCC/Demangler.hpp"

struct Entity;
struct Event;
struct Component {
    virtual ~Component() {}
    virtual void onAdd() {}
    virtual void onRemove() {}
    virtual void update(float dt) {}
    virtual void draw(sf::RenderWindow &window) {}
    virtual void sendEvent(Event &event);

    void remove();
    Entity* getOwner();
    void setOwner(Entity *_object);

protected:
    Entity* m_parent;

    template<typename T>
    void failWithMissingComponent() {
        #ifdef __GNUG__
            fail(Helper::demangleNameByType<T>());
        #else
            fail(typeid(T).name());
        #endif
        return;
    }

private:
    void fail(const std::string name);
};
