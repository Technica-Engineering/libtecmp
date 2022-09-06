
add_executable(tecmp_app "app.cpp")

cmake_policy(SET CMP0135 NEW)

include(cmake/libpcap.cmake)
include(cmake/pcapplusplus.cmake)

target_link_libraries(tecmp_app PRIVATE tecmp_library pcapplusplus)
target_compile_features(tecmp_app PRIVATE cxx_std_17)

add_test(
    NAME "tecmp_app.test"
    COMMAND tecmp_app 
        "${CMAKE_CURRENT_LIST_DIR}/../traces/input_eth.pcap"
        "${CMAKE_CURRENT_LIST_DIR}/../traces/output_eth.pcap"
)
