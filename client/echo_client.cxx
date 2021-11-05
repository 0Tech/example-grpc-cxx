#include <iostream>
#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>
#include "com/example/grpc/echo/echo.grpc.pb.h"

using std::operator""s;

class EchoerClient {
public:
  EchoerClient(std::string const& endpoint)
	: stub_{echo::Echoer::NewStub(grpc::CreateChannel(endpoint,
													  grpc::InsecureChannelCredentials()))} {}

  void log(std::string const& message) {
	std::cout << "INFO: " + message << std::endl;
  }

  void ping(std::string const& message) {
	log("ping: "s + message);
	echo::EchoRequest request;
	request.set_message(message);

	echo::EchoReply reply;
	grpc::ClientContext context;
	auto const status{stub_->echoOnce(&context, request, &reply)};
	if (status.ok()) {
	  log("pong: "s + reply.message());
	} else {
	  std::cerr << status.error_code() << ": "s << status.error_message()
				<< std::endl;
	}
  }

private:
  std::unique_ptr<echo::Echoer::Stub> stub_;
};
	
int main(int argc, char* argv[]) {
  std::string const message{(argc > 1) ? argv[1] : "hello"s};
  std::string const endpoint{(argc > 2) ? argv[2] : "localhost:50051"s};

  auto echoer{EchoerClient(endpoint)};
  echoer.ping(message);

  return 0;
}
