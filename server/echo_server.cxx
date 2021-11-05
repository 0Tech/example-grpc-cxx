#include <iostream>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "com/example/grpc/echo/echo.grpc.pb.h"

using std::operator""s;

class EchoerServer {
public:
  EchoerServer(std::string const& endpoint)
	: service_{EchoerService{}},
	  server_{CreateServer(endpoint)}{
  }
  void run() {
	server_->Wait();
  }

private:
  static void log(std::string const& message) {
	std::cout << "INFO: "s + message << std::endl;
  }

  class EchoerService final: public echo::Echoer::Service {
  public:
	grpc::Status echoOnce(grpc::ServerContext* context, echo::EchoRequest const* request,
						  echo::EchoReply* reply) override {
	  auto const message{request->message()};
	  log(message);
	  auto const prefix{"[Echo] "s};
	  reply->set_message(prefix + message);
	  log(reply->message());
	  return grpc::Status::OK;
	}
  };
  EchoerService service_;

  std::unique_ptr<grpc::Server> CreateServer(std::string const& endpoint) {
	grpc::ServerBuilder builder;
	builder.AddListeningPort(endpoint, grpc::InsecureServerCredentials());
	builder.RegisterService(&service_);
	log("Launching server on: "s + endpoint);
	return builder.BuildAndStart();
  }
  std::unique_ptr<grpc::Server> server_;
};

void run_server() {
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  auto const endpoint{"localhost:50051"s};
  EchoerServer server{endpoint};
  server.run();
}

int main() {
  run_server();
  return 0;
}
