function(add_grpc target source_proto_dir source_path)
  get_filename_component(abs_source_path ${source_path} ABSOLUTE)
  file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${abs_source_path})

  get_filename_component(abs_source_proto_dir ${source_proto_dir} ABSOLUTE)
  file(RELATIVE_PATH rel_proto_dir ${CMAKE_SOURCE_DIR} ${abs_source_proto_dir})

  file(RELATIVE_PATH proto_path ${abs_source_proto_dir} ${abs_source_path})
  get_filename_component(proto_name ${proto_path} NAME_WLE)
  get_filename_component(proto_dir ${proto_path} DIRECTORY)
  set(proto_path_wle ${proto_dir}/${proto_name})

  add_custom_command(
	DEPENDS ${source_path}
	OUTPUT
	${proto_path_wle}.pb.cc
	${proto_path_wle}.pb.h
	${proto_path_wle}.grpc.pb.cc
	${proto_path_wle}.grpc.pb.h
	COMMAND protoc -I ${abs_source_proto_dir} --grpc_out . --cpp_out . --plugin=protoc-gen-grpc=$<TARGET_FILE:grpc_cpp_plugin> ${abs_source_path})

  add_library(${target})
  target_sources(${target}
	PRIVATE
	${proto_path_wle}.pb.cc
	${proto_path_wle}.grpc.pb.cc)
  target_include_directories(${target}
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
  target_link_libraries(${target}
	PUBLIC libprotobuf grpc++_reflection grpc++)
endfunction(add_grpc)
