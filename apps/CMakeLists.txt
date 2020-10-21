
add_executable(tecmp_app "app.cpp")

target_link_libraries(tecmp_app PRIVATE tecmp_library CONAN_PKG::pcapplusplus)
target_compile_features(tecmp_app PRIVATE cxx_std_17)
