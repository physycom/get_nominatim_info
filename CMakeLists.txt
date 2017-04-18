cmake_minimum_required (VERSION 3.1)
project (get_nominatim_info)
set (CMAKE_CXX_STANDARD 11)
find_package(CURL REQUIRED)

set(JSONCONS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/jsoncons/src)
if(MSVC)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${JSONCONS_INCLUDE_DIR} ${CURL_INCLUDE_DIR} ${PROJECT_BINARY_DIR})

add_executable(get_nominatim_info ${CMAKE_SOURCE_DIR}/src/get_nominatim_info.cpp)
target_link_libraries(get_nominatim_info ${CURL_LIBRARIES})
install (TARGETS get_nominatim_info DESTINATION ${CMAKE_SOURCE_DIR}/bin)
