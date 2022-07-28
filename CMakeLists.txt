cmake_minimum_required(VERSION 3.22)
project(SCPPSocket)
set(CMAKE_CXX_STANDARD 14)

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
endif ()

if (MACOS)

elseif (WINDOWS)

elseif (LINUX)

endif ()



set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
aux_source_directory(. DIR_SRCS)

if (MACOS)
    add_library(SCPPSocketMac ${DIR_SRCS})
elseif (WINDOWS)
    add_library(SCPPSocketWin library.cpp)
elseif (LINUX)
    add_library(SCPPSocketLinux library.cpp cmake-build-debug/SCPPSocketFactoryWin.cpp cmake-build-debug/SCPPSocketFactoryWin.h)
endif ()


