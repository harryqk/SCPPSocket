#include "library.h"

#include <iostream>

void hello() {


#ifdef _WIN32
    std::cout << "Hello, World win!" << std::endl;
#elif _linux_
    std::cout << "Hello, World linux!" << std::endl;
#elif _APPLE_
    std::cout << "Hello, World mac!" << std::endl;
#elif _ANDROID_
    std::cout << "Hello, World android!" << std::endl;
#endif

}
