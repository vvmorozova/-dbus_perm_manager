cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(dbus_perm)

#compiling dbus_perm as executable

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(sdbus-c++ REQUIRED)
find_package (SQLite3 REQUIRED)


include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${SQLITE3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC sqlite3)

target_link_libraries(${PROJECT_NAME} PRIVATE SDBusCpp::sdbus-c++ utils)

#compiling dbus_perm as library
add_library(${PROJECT_NAME}_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/permissions_manager.cpp)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries (${PROJECT_NAME}_lib ${SQLITE3_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_lib LINK_PUBLIC sqlite3)

target_link_libraries(${PROJECT_NAME}_lib PRIVATE SDBusCpp::sdbus-c++ utils)