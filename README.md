![](https://img.shields.io/github/workflow/status/Technica-Engineering/libtecmp/CMake)
![](https://img.shields.io/github/license/Technica-Engineering/libtecmp)

# LIBTECMP

This library is intended for decoding TECMP packets and extracting the
captured Ethernet frames and status messages.

### Build

```sh
# Conan is only needed to build the sample app, it's not needed for the library itself
pip install conan==1.61.0

# Build CMAKE
mkdir build
cd build
pip install cmake
cmake ..
# Build release
cmake --build . --config Release
```

# License

Copyright (c) 2020-2023 Technica Engineering GmbH

GNU Lesser General Public License v3.0 or later
