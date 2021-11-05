cmake_minimum_required(VERSION 3.18)
project(grpc-example-cxx)

set(CMAKE_CXX_STANDARD 17)

set(GRPC_VERSION 1.41.0 CACHE STRING "Version of gRPC")
mark_as_advanced(GRPC_VERSION)

include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc.git
  GIT_TAG v${GRPC_VERSION})
FetchContent_MakeAvailable(gRPC)

include(cmake/AddGrpc.cmake)

add_subdirectory(protobuf)
add_subdirectory(server)
