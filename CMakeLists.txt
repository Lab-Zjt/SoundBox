CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)
PROJECT(sample)

SET(CMAKE_CXX_STANDARD 11)

include_directories(3rdparty)
include_directories(src)

file(GLOB AUDIO_SOURCE src/*.cpp)

add_library(audio ${AUDIO_SOURCE})

add_executable(mp3_sample mp3_sample.cpp)
target_link_libraries(mp3_sample audio)
