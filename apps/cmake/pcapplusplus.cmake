
if(WIN32)
    include(cmake/pcapplusplus_win32.cmake)
else()
    include(cmake/pcapplusplus_conan.cmake)
endif()
