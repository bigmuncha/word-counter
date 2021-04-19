cmake_minimum_required (VERSION 3.10)

project(word-counter)

set(SOURCE_EXE main.cpp)
set(COUNTER_LIB counter.cpp)

find_package(Boost  REQUIRED COMPONENTS  filesystem thread regex)
if(Boost_FOUND)

  include_directories(${Boost_INCLUDE_DIRS} )
  add_library(counter STATIC ${COUNTER_LIB} )

  add_executable(main ${SOURCE_EXE})
  target_link_libraries(main counter ${Boost_LIBRARIES})


endif()
