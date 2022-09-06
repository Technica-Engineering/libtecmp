cmake_minimum_required(VERSION 3.17)

# Project name and a few useful settings. Other commands can pick up the results
project(LIBTECMP
    VERSION 0.1
    DESCRIPTION "TECMP Library"
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # The executable code is here
    add_subdirectory(apps)

    include(CTest)

endif()

# The compiled library code is here
add_subdirectory(src)
