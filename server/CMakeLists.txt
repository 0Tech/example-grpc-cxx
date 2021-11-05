add_executable(echo_server)
target_sources(echo_server
  PRIVATE echo_server.cxx)
target_link_libraries(echo_server
  PRIVATE grpc++ echo_grpc)
