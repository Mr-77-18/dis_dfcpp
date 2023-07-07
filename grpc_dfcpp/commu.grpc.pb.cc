// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: commu.proto

#include "commu.pb.h"
#include "commu.grpc.pb.h"

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
namespace commu {

static const char* Commu_method_names[] = {
  "/commu.Commu/send_index",
};

std::unique_ptr< Commu::Stub> Commu::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Commu::Stub> stub(new Commu::Stub(channel, options));
  return stub;
}

Commu::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_send_index_(Commu_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Commu::Stub::send_index(::grpc::ClientContext* context, const ::commu::threemess& request, ::commu::reply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::commu::threemess, ::commu::reply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_send_index_, context, request, response);
}

void Commu::Stub::async::send_index(::grpc::ClientContext* context, const ::commu::threemess* request, ::commu::reply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::commu::threemess, ::commu::reply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_send_index_, context, request, response, std::move(f));
}

void Commu::Stub::async::send_index(::grpc::ClientContext* context, const ::commu::threemess* request, ::commu::reply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_send_index_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::commu::reply>* Commu::Stub::PrepareAsyncsend_indexRaw(::grpc::ClientContext* context, const ::commu::threemess& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::commu::reply, ::commu::threemess, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_send_index_, context, request);
}

::grpc::ClientAsyncResponseReader< ::commu::reply>* Commu::Stub::Asyncsend_indexRaw(::grpc::ClientContext* context, const ::commu::threemess& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsend_indexRaw(context, request, cq);
  result->StartCall();
  return result;
}

Commu::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Commu_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Commu::Service, ::commu::threemess, ::commu::reply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Commu::Service* service,
             ::grpc::ServerContext* ctx,
             const ::commu::threemess* req,
             ::commu::reply* resp) {
               return service->send_index(ctx, req, resp);
             }, this)));
}

Commu::Service::~Service() {
}

::grpc::Status Commu::Service::send_index(::grpc::ServerContext* context, const ::commu::threemess* request, ::commu::reply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace commu

