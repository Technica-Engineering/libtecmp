cmake_minimum_required(VERSION 3.9)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)

conan_cmake_run(
    REQUIRES pcapplusplus/22.05
    GENERATORS CMakeDeps
    BUILD missing
)

add_executable(tecmp_app "app.cpp")
find_package(pcapplusplus REQUIRED CONFIG)

target_link_libraries(tecmp_app PRIVATE tecmp_library pcapplusplus::pcapplusplus)
target_compile_features(tecmp_app PRIVATE cxx_std_17)

add_test(
    NAME "tecmp_app.test"
    COMMAND tecmp_app 
        "${CMAKE_CURRENT_LIST_DIR}/../traces/input_eth.pcap"
        "${CMAKE_CURRENT_LIST_DIR}/../traces/output_eth.pcap"
)
