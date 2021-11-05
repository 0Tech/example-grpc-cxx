add_executable(echo_client)
target_sources(echo_client
  PRIVATE echo_client.cxx)
target_link_libraries(echo_client
  PRIVATE grpc++ echo_grpc)
