cmake_minimum_required(VERSION 3.28)

project(spotifire)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(Qt6 CONFIG REQUIRED Core DBus)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

qt_wrap_cpp(SERVER_MOC ${INCLUDE_DIR}/SpotiFire.hpp)

add_executable(spotifire
  ${SERVER_MOC}
  ${SOURCE_DIR}/Server.cpp
  ${SOURCE_DIR}/SpotiFire.cpp
)

target_include_directories(spotifire
  PRIVATE
  ${INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(spotifire
  Qt6::Core
  Qt6::DBus
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    COMPILE_OPTIONS -Wall -Wextra -pedantic
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
