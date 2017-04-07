#include "Demangler.hpp"

std::string Helper::demangleName(const char* mangled_name) {
    #ifdef __GNUG__
        std::size_t len = 0;
        int status = 0;
        std::unique_ptr<char, decltype(&std::free)> ptr(__cxxabiv1::__cxa_demangle(mangled_name, nullptr, &len, &status), &std::free);
        return ptr.get();
    #else
        return name ;
    #endif
}
