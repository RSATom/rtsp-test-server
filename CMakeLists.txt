cmake_minimum_required(VERSION 3.0)

project(rtsp-test-server)

if(DEFINED ENV{SNAPCRAFT_PROJECT_NAME})
    add_definitions(-DSNAPCRAFT_BUILD=1)
    set(SNAPCRAFT_BUILD YES)
endif()

add_subdirectory(CxxPtr)

find_package(PkgConfig REQUIRED)
pkg_search_module(GSTREAMER REQUIRED gstreamer-1.0)
pkg_search_module(GSTREAMER_RTSP_SERVER REQUIRED gstreamer-rtsp-server-1.0)
pkg_search_module(SPDLOG REQUIRED spdlog)
pkg_search_module(LIBCONFIG REQUIRED libconfig)

find_package(fmt REQUIRED)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    [^.]*.cpp
    [^.]*.h
    [^.]*.cmake
    *.conf.sample
    snap/snapcraft.yaml
    )

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GSTREAMER_INCLUDE_DIRS}
    ${GSTREAMER_RTSP_SERVER_INCLUDE_DIRS}
    ${SPDLOG_INCLUDE_DIRS}
    ${LIBCONFIG_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    fmt::fmt
    ${GSTREAMER_LDFLAGS}
    ${GSTREAMER_RTSP_SERVER_LDFLAGS}
    ${SPDLOG_LDFLAGS}
    ${LIBCONFIG_LDFLAGS})

if(SNAPCRAFT_BUILD)
    install(TARGETS ${PROJECT_NAME} DESTINATION bin)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/rtsp-test-server.conf.sample DESTINATION etc)
endif()
