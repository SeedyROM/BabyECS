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
#include <SFML/Graphics.hpp>

#include "../Helpers/GCC/Demangler.hpp"

class Entity;
struct Component {
    virtual ~Component() {}
    virtual void onAdd() {}
    virtual void onRemove() {}
    virtual void update(float dt) {}
    virtual void draw(sf::RenderWindow &window) {}

    void remove();
    Entity* getParent();
    void setParent(Entity *_object);

protected:
    Entity* object;

    template<typename T>
    void failWithMissingComponent() {
        #ifdef __GNUG__
            fail(Helper::demangleName<T>());
        #else
            fail(typeid(T).name());
        #endif
        return;
    }

private:
    void fail(const std::string name);
};
