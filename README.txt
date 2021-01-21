# Build instructions 

## Windows 
```
mkdir build && cd build
conan remote add xxhash https://api.bintray.com/conan/nshutchinson/conan
conan install .. --build xxhash
cmake .. -G "Visual Studio 16"
cmake --build . --config Release
```

## Unix / MacOS
```
mkdir build && cd build
conan remote add xxhash https://api.bintray.com/conan/nshutchinson/conan
conan install .. --build xxhash
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
make
```