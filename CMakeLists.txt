cmake_minimum_required(VERSION 3.2)
project(Timer_poll)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    timer_poll.cpp
    timer_poll.h)

add_executable(Timer_poll ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(Timer_poll pthread)