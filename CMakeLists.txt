cmake_minimum_required(VERSION 3.10)
project(car)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lwiringPi -lm -pthread -lcrypt -lrt")
file (GLOB SOURCE_FILES *.cpp)
file (GLOB HEADER_FILES *.hpp)
file (GLOB HEADER_FILES *.h)

# Include our cmake macros
add_definitions (-DBOOST_ERROR_CODE_HEADER_ONLY)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
#include (CMakeHelpers)
#include(CMakePackageConfigHelpers)
# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS})
#add_subdirectory (websocketpp)
#find_package(websocketpp REQUIRED)
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(ArduinoJson)
add_executable(car car.cpp echo_server.hpp)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(car ${WIRINGPI_LIBRARIES} ArduinoJson ${OpenCV_LIBS})


