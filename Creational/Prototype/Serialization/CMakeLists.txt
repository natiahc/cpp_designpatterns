cmake_minimum_required(VERSION 3.11)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{DEPENDENCIES}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "")
    message(" [INFO] VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
endif()

#======= Global Project Configuration =========#

project(ProtoypeSerializationPattern)
set(CMAKE_CXX_STANDARD 17)     

#========== Targets Configurations ============#

message(STATUS "Boost Version:" ${Boost_VERSION})
message(STATUS "Boost Include Dirs:" ${Boost_INCLUDE_DIR})
message(STATUS "Boost Libraries:")
foreach(lib ${BOOST_LIBRARIES})
		message(STATUS ${lib})
endforeach()

find_package(BOOST REQUIRED COMPONENTS serialization)

include_directories(${Boost_INCLUDE_DIR})
add_executable(ProtoypeSerialization Serialization.cpp)
target_link_libraries(ProtoypeSerialization PRIVATE ${Boost_LIBRARIES})

