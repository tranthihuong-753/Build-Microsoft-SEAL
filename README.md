# Build-Microsoft-SEAL

## Cấu hình SEAL 

- cai build tool https://visualstudio.microsoft.com/visual-cpp-build-tools/

- chay .exe va install 

“Desktop development with C++”

“MSVC v143 build tools”

“Windows 10 SDK”

- tao du_an/SEAL_Build và du_an/Project_Build 

- cd SEAL_Build 

- cmake ..\SEAL -G "Visual Studio 17 2022" 


## Build SEAL 

- cd SEAL_Build 

- cmake --build . --config Release

## Cấu hình SEAL cho project 

- cd Project_Build  

-  cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DSEAL_DIR="C:/Build-Microsoft-SEAL/SEAL_Build/cmake"

## Build SEAL cho project 


- cd Project_Build  

- cmake --build . --config Release

## Tải vcpkg [Chuyen doi giua json va C++ (string, double, ...)]

- git clone https://github.com/microsoft/vcpkg.git

- cd vcpkg 

- C:\hu\decision-tree-he\vcpkg\bootstrap-vcpkg.bat

- .\vcpkg install nlohmann-json

- .\vcpkg integrate install 

