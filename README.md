![](https://img.shields.io/github/workflow/status/Technica-Engineering/libtecmp/CMake)
![](https://img.shields.io/github/license/Technica-Engineering/libtecmp)

# LIBTECMP

This library is intended for decoding TECMP packets and extracting the
captured Ethernet frames and status messages.

### Build

```sh
# Conan is only needed to build the sample app, it's not needed for the library itself
pip install conan
conan remote add public-conan https://api.bintray.com/conan/bincrafters/public-conan

conan install conanfile.txt
# or if building Debug
conan install -s build_type=Debug conanfile.txt

# Build CMAKE
mkdir build
cd build
cmake ..
```

# License

Copyright (c) 2020 Technica Engineering GmbH

GNU General Public License v3.0 or later

If you want to get a non-GPL version of this lib, please get in touch with technicalsales(at)technica-engineering.de or lars.voelker(at)technica-engineering.de
