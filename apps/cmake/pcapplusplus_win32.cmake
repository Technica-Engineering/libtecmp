cmake_minimum_required(VERSION 3.12)

include(FetchContent)

set(PCAPPLUSPLUS_URL_PREFIX "https://github.com/seladb/PcapPlusPlus/releases/download")
set(PCAPPLUSPLUS_VERSION "22.05")

if(MSVC)
    if(MSVC_TOOLSET_VERSION EQUAL 143)
        set(PCAPPLUSPLUS_PLATFORM "windows-vs2019") 
    elseif(MSVC_TOOLSET_VERSION EQUAL 142)
        set(PCAPPLUSPLUS_PLATFORM "windows-vs2019")
    elseif(MSVC_TOOLSET_VERSION EQUAL 141)
        set(PCAPPLUSPLUS_PLATFORM "windows-vs2017")
    elseif(MSVC_TOOLSET_VERSION EQUAL 140)
        set(PCAPPLUSPLUS_PLATFORM "windows-vs2015") 
    endif()
endif()

if(NOT DEFINED PCAPPLUSPLUS_PLATFORM)
    message(FATAL_ERROR "Unsupported Toolchain")
endif()

set(PCAPPLUSPLUS_FILE "pcapplusplus-${PCAPPLUSPLUS_VERSION}-${PCAPPLUSPLUS_PLATFORM}")
set(PCAPPLUSPLUS_URL "${PCAPPLUSPLUS_URL_PREFIX}/v${PCAPPLUSPLUS_VERSION}/${PCAPPLUSPLUS_FILE}.zip")

FetchContent_Declare(
    pcapplusplus
    URL ${PCAPPLUSPLUS_URL}
    SOURCE_SUBDIR ${PCAPPLUSPLUS_FILE}
)

FetchContent_MakeAvailable(pcapplusplus)

set(PCAPPLUSPLUS_INCLUDE_DIR "${pcapplusplus_SOURCE_DIR}/header")

if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    set(PCAPPLUSPLUS_LIBRARY_DIR "${pcapplusplus_SOURCE_DIR}/x64")
else()
    set(PCAPPLUSPLUS_LIBRARY_DIR "${pcapplusplus_SOURCE_DIR}/x86")
endif()

add_library(pcapplusplus INTERFACE IMPORTED)
add_library(pcapplusplus_common UNKNOWN IMPORTED)
add_library(pcapplusplus_packet UNKNOWN IMPORTED)
add_library(pcapplusplus_pcap UNKNOWN IMPORTED)

target_include_directories(pcapplusplus INTERFACE "${PCAPPLUSPLUS_INCLUDE_DIR}")

target_link_libraries(pcapplusplus_common INTERFACE wsock32 ws2_32)
target_link_libraries(pcapplusplus_pcap INTERFACE libpcap)
target_link_libraries(pcapplusplus INTERFACE pcapplusplus_common pcapplusplus_packet pcapplusplus_pcap)


set_target_properties(pcapplusplus_common PROPERTIES
    IMPORTED_LOCATION "${PCAPPLUSPLUS_LIBRARY_DIR}/Release/Common++.lib"
    IMPORTED_LOCATION_DEBUG "${PCAPPLUSPLUS_LIBRARY_DIR}/Debug/Common++.lib"
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
)
set_target_properties(pcapplusplus_packet PROPERTIES
    IMPORTED_LOCATION "${PCAPPLUSPLUS_LIBRARY_DIR}/Release/Packet++.lib"
    IMPORTED_LOCATION_DEBUG "${PCAPPLUSPLUS_LIBRARY_DIR}/Debug/Packet++.lib"
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
)
set_target_properties(pcapplusplus_pcap PROPERTIES
    IMPORTED_LOCATION "${PCAPPLUSPLUS_LIBRARY_DIR}/Release/Pcap++.lib"
    IMPORTED_LOCATION_DEBUG "${PCAPPLUSPLUS_LIBRARY_DIR}/Debug/Pcap++.lib"
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
)
