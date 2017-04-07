//
//  Event.cpp
//  BabyECS
//
//  Created by <author> on 06/04/2017.
//
//

#include "Event.hpp"

std::string Event::getClassName(const char* macroName) {
    std::string parsedName(macroName);
    std::size_t split = parsedName.find(":");
    parsedName.substr(0, split - 1);
    return parsedName;
}

const std::string Event::getType() {
    return m_type;
}
