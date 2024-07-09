cmake_minimum_required(VERSION 3.9)

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

install(
    TARGETS tecmp_app DESTINATION "."
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
