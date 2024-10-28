cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
project(dbus_perm)

find_package(sdbus-c++ REQUIRED)
find_package (SQLite3 REQUIRED)

# find_package(sdbus-c++-tools REQUIRED)

# add_custom_command(
#     OUTPUT myproject-client-glue.h myproject-server-glue.h
#     COMMAND SDBusCpp::sdbus-c++-xml2cpp ${PROJECT_SOURCE_DIR}/dbus/myproject-bindings.xml
#         --proxy=myproject-client-glue.h --adaptor=myproject-server-glue.h
#     DEPENDS dbus/myproject-bindings.xml
#     COMMENT "Generating D-Bus interfaces for ${PROJECT_NAME}."
# )

add_executable(dbus_perm dbus_perm.cpp)

include_directories(${SQLITE3_INCLUDE_DIRS})
target_link_libraries (dbus_perm ${SQLITE3_LIBRARIES})

# Use the sdbus-c++ target in SDBusCpp namespace
target_link_libraries(dbus_perm PRIVATE SDBusCpp::sdbus-c++)
