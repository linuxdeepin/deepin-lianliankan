
#1.定义cmake版本
cmake_minimum_required(VERSION 3.9.5)

#2.设置项目名称
set(EXE_NAME  deepin-lianliankan)
project(${EXE_NAME})

if (NOT DEFINED VERSION)
    set(VERSION 1.0.0)
endif ()

# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++11" )


set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON) #要显示执行构建过程中详细的信息(比如为了得到更详细的出错信息)
set(CMAKE_AUTOMOC ON) #打开全局moc
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#对DApplication 进行加速
set(CMAKE_EXE_LINKER_FLAGS "-pie")


add_subdirectory(src)
add_subdirectory(tests)



