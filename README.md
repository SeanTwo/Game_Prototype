This project uses raylib and I used MSVC VS 17 2022 to build and develop it
due to that I can't give exact instructions for other compilers like G++

To build first you need to download Raylib 6.0 and build from source in its root folder
then in order to build assuming the Raylib download path is C:/raylib

Powershell:
mkdir build
Set-Location build
cmake -DCMAKE_PREFIX_PATH="E:\Downloads\raylib_testing\raylib" ..
Set-Location ..
$build_type = "Debug"  //Change to "Release" for a release build
cmake --build . --config "$build_type"
Copy-Item -r ./resources "./build/$build_type"

you should now have your compiled binary

