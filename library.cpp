#include "library.h"

#include <iostream>

void hello() {


#ifdef _WIN32
    std::cout << "Hello, World win!" << std::endl;
#elifd  __linux__
    std::cout << "Hello, World linux!" << std::endl;
#elif __APPLE__
    std::cout << "Hello, World mac!" << std::endl;
#elif __ANDROID__
    std::cout << "Hello, World android!" << std::endl;
#endif

}
