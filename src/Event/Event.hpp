//
//  Event.hpp
//  BabyECS
//
//  Created by Zack Kollar on 06/04/2017.
//
//

#pragma once
#include <string>

// Real fuckin simple!
struct Event {
    virtual ~Event() {}
    virtual std::string type() {}
};

// Who ever dare use this, beware!
#define GenerateEventStruct(className) \
struct className : Event { \
    using Event::Event; \
    virtual std::string type() override { \
        return #className; \
    }

GenerateEventStruct(TestingTestEvent) // {
};
GenerateEventStruct(ATest) // {
};
