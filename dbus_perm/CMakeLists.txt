cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(dbus_perm)

include_directories(${CMAKE_SOURCE_DIR}/inc)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*cpp)

find_package(sdbus-c++ REQUIRED)
find_package (SQLite3 REQUIRED)

add_executable(dbus_perm ${SRC_FILES})

include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (dbus_perm ${SQLITE3_LIBRARIES})

# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(dbus_perm PRIVATE SDBusCpp::sdbus-c++)
