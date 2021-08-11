#定义cmake版本
cmake_minimum_required(VERSION 3.9.5)

#设置项目名称
set(EXE_NAME deepin-lianliankan)
project(${EXE_NAME})

# #配置版本号
# configure_file(environments.h.in environments.h @ONLY)


# Find the library
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools REQUIRED)
find_package(DtkWidget REQUIRED)
pkg_search_module(DtkWidget REQUIRED dtkwidget)

#lupdate start
set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../translations")
set(TS_FILES
    "${TS_DIR}/${EXE_NAME}.ts"
)
find_program(LUPDATE_EXECUTABLE lupdate)
foreach(_ts_file ${TS_FILES})
    execute_process(
        COMMAND ${LUPDATE_EXECUTABLE} -recursive ${CMAKE_SOURCE_DIR} -ts ${_ts_file})
endforeach()
#lupdate end

file (GLOB APP_TS_FILES translations/*.ts)

#Generate the qm file
set(APP_TRANS_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/translate_generation.sh")
execute_process(COMMAND bash ${APP_TRANS_SCRIPT}
    WORKING_DIRECTORY ${TS_DIR})
qt5_create_translation(APP_QM_FILES ${APP_TS_FILES} ${APP_QM_FILES})

#源文件、头文件和资源文件
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${DtkWidget_INCLUDE_DIRS})
include_directories(${DtkCore_INCLUDE_DIRS})
include_directories(${DtkGui_INCLUDE_DIRS})
file(GLOB_RECURSE c_files RELATIVE ${PROJECT_SOURCE_DIR} source/*.cpp source/*.c ../main.cpp)
file(GLOB_RECURSE h_files RELATIVE ${PROJECT_SOURCE_DIR} source/*.h *.h)
file(GLOB_RECURSE res_files RELATIVE ${PROJECT_SOURCE_DIR} *.qrc)

#添加资源文件
QT5_ADD_RESOURCES(QRC_FILES ${res_files})

#生成可执行程序
add_executable(${EXE_NAME} ${c_files} ${h_files} ${QRC_FILES} ${APP_QM_FILES})


target_include_directories(${EXE_NAME} PUBLIC ${DtkWidget_INCLUDE_DIRS} ${OBJECT_BINARY_DIR})
target_link_libraries(${EXE_NAME}
    ${DtkWidget_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)

# Install files
set(CMAKE_INSTALL_PREFIX /usr)
install(FILES ${APP_QM_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-lianliankan/translations)
install(FILES assets/deepin-lianliankan.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES assets/images/deepin-lianliankan.svg
            DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps/)
install(TARGETS ${EXE_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
#install(DIRECTORY assets/deepin-log-viewer DESTINATION /usr/share/deepin-manual/manual-assets/application/)

