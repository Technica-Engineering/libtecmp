
# Make an automatic library - will be static or dynamic based on user setting
add_library(tecmp_library tecmp.c "endianness.h")

# We need the include directory, and users of our library will need it too
target_include_directories(tecmp_library PUBLIC ../include)

# Library needs at least C99
target_compile_features(tecmp_library PRIVATE c_std_99)
