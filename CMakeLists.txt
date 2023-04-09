cmake_minimum_required(VERSION 3.6)

project(FasterMatrix)

# Import Thread Library
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(SOURCE_FILES src/Benchmark.cpp
				 src/ScalarMatrix.cpp src/ScalarMatrix.hpp
				 src/MultithreadedMatrix.cpp src/MultithreadedMatrix.hpp
				 src/MultithreadedAVXMatrix.cpp src/MultithreadedAVXMatrix.hpp
				 src/GPGPUMatrix.cpp src/GPGPUMatrix.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# AVX 2
add_library(avx2 INTERFACE IMPORTED)
if(MSVC)
    target_compile_options(avx2 INTERFACE /arch:AVX2)
else()
    target_compile_options(avx2 INTERFACE -mavx2)
endif()

# Set this project as startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} Threads::Threads)