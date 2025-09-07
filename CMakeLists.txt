cmake_minimum_required(VERSION 3.21)
project(cputemp_qt6_widgets LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cxx)
qt_add_resources(APP_RESOURCES resources.qrc)

add_executable(app
  ${SRC_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cxx
)
target_sources(app PRIVATE ${APP_RESOURCES})
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(app PRIVATE Qt6::Widgets)

set_target_properties(
  app PROPERTIES OUTPUT_NAME 
  ${CMAKE_CURRENT_SOURCE_DIR}/cputemp_monitor
)
