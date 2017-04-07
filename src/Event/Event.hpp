//
//  Event.hpp
//  BabyECS
//
//  Created by <author> on 06/04/2017.
//
//

#pragma once

#include <typeinfo>
#include "../Helpers/GCC/Demangler.hpp"

struct Event {

    Event() : m_type(getClassName(__FUNCTION__)) {}
    virtual ~Event() {}

    const std::string getType();

protected:
    std::string m_type;
    std::string getClassName(const char* macroName);
};
