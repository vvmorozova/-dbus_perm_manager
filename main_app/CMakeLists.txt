cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(main_app)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(sdbus-c++ REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDBusCpp::sdbus-c++ dbus_perm_lib utils)


