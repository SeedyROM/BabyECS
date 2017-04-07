#pragma once

#include <string>
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

namespace Helper {
    std::string demangleName(const char* mangled_name);

    template<typename T>
    std::string demangleNameByType() {
        int status;
        std::string tname = typeid(T).name();
        char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
        if(status == 0) {
            tname = demangled_name;
            std::free(demangled_name);
        }
        return tname;
    }
}
