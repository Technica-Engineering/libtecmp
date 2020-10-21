

conan remote add public-conan https://api.bintray.com/conan/bincrafters/public-conan

::conan install conanfile.txt

conan install -s build_type=Debug conanfile.txt