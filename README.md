This project uses vcpkg with the following packages
curl:x64-windows

to build from root
mkdir ./build
cmake .. -DCMAKE_TOOLCHAIN_FILE={YOUR_VCPKG_DIR/vcpkg/scripts/buildsystems/vcpkg.cmake}
cmake --build .
