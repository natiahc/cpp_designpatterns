cmake_minimum_required(VERSION 3.14)
project(FacetBuilderPattern)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(FACET_BUILDER_FILES Person.h Person.cpp PersonBuilder.h PersonBuilder.cpp PersonAdressBuilder.h PersonJobBuilder.h FacetBuilder.cpp)
add_executable(FacetBuilder ${FACET_BUILDER_FILES})