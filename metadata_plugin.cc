#include <mutex>
#include <thread>
#include <string>

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

// #include "src/core/lib/gpr/env.h"
// #include "src/core/lib/security/credentials/credentials.h"
// #include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
// #include "src/proto/grpc/testing/echo.grpc.pb.h"
// #include "test/core/util/port.h"
// #include "test/core/util/test_config.h"
// #include "test/cpp/end2end/test_service_impl.h"
// #include "test/cpp/util/string_ref_helper.h"
// #include "test/cpp/util/test_credentials_provider.h"

#include "examples/cpp/helloworld/metadata_plugin.h"
#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <streambuf>

// using grpc::testing::EchoRequest;
// using grpc::testing::EchoResponse;
// using grpc::testing::kTlsCredentialsType;
// using std::chrono::system_clock;

namespace grpc {
namespace testing {

TestMetadataCredentialsPlugin::TestMetadataCredentialsPlugin(grpc::string_ref metadata_key,
                                grpc::string_ref metadata_value,
                                bool is_blocking, bool is_successful)
      : metadata_key_(metadata_key.data(), metadata_key.length()),
        metadata_value_(metadata_value.data(), metadata_value.length()),
        is_blocking_(is_blocking),
        is_successful_(is_successful) {}

bool TestMetadataCredentialsPlugin::IsBlocking() const { return is_blocking_; }

Status TestMetadataCredentialsPlugin::GetMetadata(
    grpc::string_ref service_url, grpc::string_ref method_name,
    const grpc::AuthContext& channel_auth_context,
    std::multimap<grpc::string, grpc::string>* metadata) {
    metadata->insert(std::make_pair(metadata_key_, metadata_value_));
    return Status::OK;
// EXPECT_GT(service_url.length(), 0UL);
// EXPECT_GT(method_name.length(), 0UL);
// EXPECT_TRUE(channel_auth_context.IsPeerAuthenticated());
// EXPECT_TRUE(metadata != nullptr);
// if (is_successful_) {
//   metadata->insert(std::make_pair(metadata_key_, metadata_value_));
//   return Status::OK;
// } else {
//   return Status(StatusCode::NOT_FOUND, kTestCredsPluginErrorMsg);
// }
}

std::string LoadFromFile(std::string filename) {
  std::ifstream t(filename);
  return std::string((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());
}

const char TestMetadataCredentialsPlugin::kBadMetadataKey[] =
    "TestPluginMetadata";
const char TestMetadataCredentialsPlugin::kGoodMetadataKey[] =
    "test-plugin-metadata";

} // testing
} // grpc