cmake_minimum_required(VERSION 3.22)
project(SCPPSocket)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions")
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
endif ()

if (MACOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions")
elseif (WINDOWS)

elseif (LINUX)

endif ()



set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
aux_source_directory(. DIR_SRCS1)
if (MACOS)
    #aux_source_directory(./Mac DIR_SRCS2)
    #add_library(SCPPSocketMac ${DIR_SRCS1} ${DIR_SRCS2})
elseif (WINDOWS)
    aux_source_directory(./Win DIR_SRCS2)
    add_library(SCPPSocketWin ${DIR_SRCS1} ${DIR_SRCS2})
elseif (LINUX)
    #aux_source_directory(./Linux DIR_SRCS2)
    #add_library(SCPPSocketLinux ${DIR_SRCS1} ${DIR_SRCS2})
endif ()

