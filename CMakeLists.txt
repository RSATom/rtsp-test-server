cmake_minimum_required(VERSION 3.0)

project(rtsp-test-server)

add_subdirectory(CxxPtr)

find_package(PkgConfig REQUIRED)
pkg_search_module(GSTREAMER REQUIRED gstreamer-1.0)
pkg_search_module(GSTREAMER_RTSP_SERVER REQUIRED gstreamer-rtsp-server-1.0)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    snap/snapcraft.yaml
    )

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GSTREAMER_INCLUDE_DIRS}
    ${GSTREAMER_RTSP_SERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${GSTREAMER_LDFLAGS}
    ${GSTREAMER_RTSP_SERVER_LDFLAGS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
