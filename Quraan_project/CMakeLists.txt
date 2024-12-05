cmake_minimum_required(VERSION 3.29)
project(Quraan_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Quraan_project
        main.cpp
        surah.cpp
        doublyLinkedList.cpp
        App.cpp
        playList.cpp
)

# Link the winmm library to the executable
target_link_libraries(Quraan_project PRIVATE winmm)

# If winmm is not in the default location, specify its path
# For example, if using MSYS2/MinGW, add the path like this:
# link_directories("C:/msys64/mingw64/lib")