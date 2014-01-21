project(OpenCVSamples)
cmake_minimum_required(VERSION 2.8)


find_package(OpenCV REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions( -DNDEBUG -Wall )


add_executable( ccapture src/ccapture.cpp )
add_executable( fdetection src/fdetection.cpp )

target_link_libraries(ccapture ${OpenCV_LIBS})
target_link_libraries(fdetection ${OpenCV_LIBS})
