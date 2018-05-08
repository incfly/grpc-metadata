#ifndef METADATA_PLUGIN
#define METADATA_PLUGIN

#include <mutex>
#include <thread>

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/resource_quota.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

namespace grpc{
namespace testing {

extern std::string LoadFromFile(string filename);

class TestMetadataCredentialsPlugin : public MetadataCredentialsPlugin {
 public:
  static const char kGoodMetadataKey[];
  static const char kBadMetadataKey[];

  TestMetadataCredentialsPlugin(grpc::string_ref metadata_key,
                                grpc::string_ref metadata_value,
                                bool is_blocking, bool is_successful);

  bool IsBlocking() const override;

  Status GetMetadata(
      grpc::string_ref service_url, grpc::string_ref method_name,
      const grpc::AuthContext& channel_auth_context,
      std::multimap<grpc::string, grpc::string>* metadata) override;

 private:
  grpc::string metadata_key_;
  grpc::string metadata_value_;
  bool is_blocking_;
  bool is_successful_;
};

}
}

#endif