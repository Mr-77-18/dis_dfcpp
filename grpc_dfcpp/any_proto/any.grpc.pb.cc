// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: any.proto

#include "any.pb.h"
#include "any.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace any {

static const char* Any_method_names[] = {
  "/any.Any/send_any",
};

std::unique_ptr< Any::Stub> Any::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Any::Stub> stub(new Any::Stub(channel, options));
  return stub;
}

Any::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_send_any_(Any_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Any::Stub::send_any(::grpc::ClientContext* context, const ::any::request& request, ::any::reply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::any::request, ::any::reply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_send_any_, context, request, response);
}

void Any::Stub::async::send_any(::grpc::ClientContext* context, const ::any::request* request, ::any::reply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::any::request, ::any::reply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_send_any_, context, request, response, std::move(f));
}

void Any::Stub::async::send_any(::grpc::ClientContext* context, const ::any::request* request, ::any::reply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_send_any_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::any::reply>* Any::Stub::PrepareAsyncsend_anyRaw(::grpc::ClientContext* context, const ::any::request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::any::reply, ::any::request, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_send_any_, context, request);
}

::grpc::ClientAsyncResponseReader< ::any::reply>* Any::Stub::Asyncsend_anyRaw(::grpc::ClientContext* context, const ::any::request& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsend_anyRaw(context, request, cq);
  result->StartCall();
  return result;
}

Any::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Any_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Any::Service, ::any::request, ::any::reply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Any::Service* service,
             ::grpc::ServerContext* ctx,
             const ::any::request* req,
             ::any::reply* resp) {
               return service->send_any(ctx, req, resp);
             }, this)));
}

Any::Service::~Service() {
}

::grpc::Status Any::Service::send_any(::grpc::ServerContext* context, const ::any::request* request, ::any::reply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace any

