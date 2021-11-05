# example-grpc-cxx

Minimal example of gRPC in C++

## Build

You can build the client and server with:

```shell
$ cmake -S . -B build
$ cmake --build build
```

## Usage

You can run echo server with:

```shell
$ ./build/server/echo_server
```

After that, you may run echo client to ping to the server:

```shell
$ ./build/client/echo_client
```
