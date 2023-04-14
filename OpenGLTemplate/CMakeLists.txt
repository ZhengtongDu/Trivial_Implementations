# 声明 CMake 最低版本
cmake_minimum_required(VERSION 2.8)
# 声明工程名称
project(OpenGLProjects)
# 设置工程目录变量
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
# 设置glad源文件
set(GLAD_SOURCES
    ${PROJECT_INCLUDE_DIR}/glad/glad.c)
# 查找 GLFW3 库
find_package(glfw3 3.2 REQUIRED)
# 添加头文件搜索路径
include_directories(${PROJECT_INCLUDE_DIR})
# 遍历所有可执行文件
file(GLOB PROJECT_EXECUTABLES ${PROJECT_SOURCE_DIR}/*.cpp)
foreach(PROJECT_EXECUTABLE ${PROJECT_EXECUTABLES})
    # 获取可执行文件的名称
    get_filename_component(PROJECT_EXECUTABLE_NAME ${PROJECT_EXECUTABLE} NAME_WE)
    # 添加可执行文件
    add_executable(${PROJECT_EXECUTABLE_NAME} ${PROJECT_EXECUTABLE} ${GLAD_SOURCES})
    # 链接 GLFW3 库
    target_link_libraries(${PROJECT_EXECUTABLE_NAME} glfw)
endforeach(PROJECT_EXECUTABLE)