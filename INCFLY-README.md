# Prototype for gRPC metadata credentials plugin.

gRPC supports different credentials and allows developers to [write customized
per-call
credentials](https://grpc.io/docs/guides/auth.html#extending-grpc-to-support-other-authentication-mechanisms).
They're represented as key-value pairs of metadata, and is transported as HTTP2
header.

We use a self-signed x509 certificate to establish SSL channel, because gRPC
only allows [sending credentials transport in a
securechannel](https://grpc.io/docs/guides/auth.html#supported-auth-mechanisms).

Instructions to use this repo.

1.  Checkout the gRPC main repo.
1.  Copy files from this folder to override gRPC provided examples.
1.  Compile and run.
    1.  `./greeter_server`, printing the received key/values from the client.
    1.  `./greeter_client`, in a separate terminal.
