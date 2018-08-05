CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)
PROJECT(soundbox)

SET(CMAKE_CXX_STANDARD 11)

include_directories(src)

file(GLOB AUDIO_SOURCE src/*.cpp)

add_library(audio ${AUDIO_SOURCE})

add_executable(soundbox soundbox.cpp)
target_link_libraries(soundbox audio)
