#定义cmake版本
cmake_minimum_required(VERSION 3.9.5)

#设置项目名称
set(EXE_NAME deepin-lianliankan)
#set(APP_TRANS_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/translate_generation.sh")
project(${EXE_NAME})

# #配置版本号
# configure_file(environments.h.in environments.h @ONLY)


# Find the library
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(DtkWidget REQUIRED)
pkg_search_module(DtkWidget REQUIRED dtkwidget)
include_directories(${DtkWidget_INCLUDE_DIRS})



#源文件、头文件和资源文件
include_directories(${PROJECT_SOURCE_DIR})
file(GLOB_RECURSE c_files RELATIVE ${PROJECT_SOURCE_DIR} source/*.cpp source/*.c ../main.cpp)
file(GLOB_RECURSE h_files RELATIVE ${PROJECT_SOURCE_DIR} source/*.h *.h)
file(GLOB_RECURSE res_files RELATIVE ${PROJECT_SOURCE_DIR} *.qrc)

# #添加资源文件
 QT5_ADD_RESOURCES(QRC_FILES ${res_files})

#生成可执行程序
add_executable(${EXE_NAME} ${c_files} ${h_files} ${QRC_FILES})

target_include_directories(${EXE_NAME} PUBLIC ${DtkWidget_INCLUDE_DIRS} ${OBJECT_BINARY_DIR})
target_link_libraries(${EXE_NAME}
    ${DtkWidget_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)


