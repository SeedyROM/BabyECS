#include <string>
#include <cstdlib>
#include <cxxabi.h>

namespace Helper {
    template<typename T>
    std::string demangleName()
    {
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
