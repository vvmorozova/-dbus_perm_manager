cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(dbus_time)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(sdbus-c++ REQUIRED)
find_package (SQLite3 REQUIRED)


include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${SQLITE3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC sqlite3)

# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(${PROJECT_NAME} PRIVATE SDBusCpp::sdbus-c++)

target_link_libraries(${PROJECT_NAME} PRIVATE utils)
