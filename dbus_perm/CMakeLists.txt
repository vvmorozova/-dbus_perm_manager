cmake_minimum_required(VERSION 3.22)
find_package(sdbus-c++ REQUIRED)
find_package (SQLite3 REQUIRED)

add_executable(dbus_perm dbus_perm.cpp)

include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (dbus_perm ${SQLITE3_LIBRARIES})

# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(dbus_perm PRIVATE SDBusCpp::sdbus-c++)
