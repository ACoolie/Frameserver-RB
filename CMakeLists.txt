project(AVC)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_C_FLAGS "-W -Wall -pthread -std=c99 -Wno-unused")

set(SRCS AVC.h AVC.c AVCInput.c AVCFrame.c AVCOutput.c)

include(FindPkgConfig)
find_package(Ruby REQUIRED)
pkg_search_module(LAVC REQUIRED libavcodec)
pkg_search_module(LAVF REQUIRED libavformat)
pkg_search_module(SWS REQUIRED libswscale)

include_directories(${RUBY_HDR_DIR} ${RUBY_HDR_DIR}/${RUBY_SITEARCH})
add_library(AVC SHARED ${SRCS})
target_link_libraries(AVC ${RUBY_LIBRARY} ${LAVC_LIBRARIES} ${LAVF_LIBRARIES} ${SWS_LIBRARIES})

