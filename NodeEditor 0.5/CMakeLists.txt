cmake_minimum_required(VERSION 3.14)
project(NodeEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

# Path to Qt
set(CMAKE_PREFIX_PATH "D:/Qt/Qt6.5.3/6.5.3/mingw_64/lib/cmake")

# Required Qt module
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ✅ Add vcpkg toolchain OpenCV support
find_package(OpenCV REQUIRED)

include_directories(src)

add_executable(NodeEditor
    src/main.cpp
    src/MainWindow.cpp
    src/NodeCanvas.cpp
    src/NodeItem.cpp
    src/Port.cpp
    src/Edge.cpp
    src/MainWindow.h
    src/NodeCanvas.h
    src/NodeItem.h
    src/Port.h
    src/Edge.h
)

# ✅ Only link once and include both
target_link_libraries(NodeEditor PRIVATE Qt6::Widgets ${OpenCV_LIBS})
