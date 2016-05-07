/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:20:04
 * Name: fence_test_service_proxy_builder.cc
 * Description:
 *   This file contains implementation of the proxy builder class.
 ******************************************************************/

#include "fence_test_service_proxy_builder.h"
#include "fence_test_service_proxy.h"


namespace org {
namespace labcrypto {
namespace fence {
namespace proxy {
  FenceTestService*
  FenceTestServiceProxyBuilder::Create(std::string host, uint32_t port) {
    return new FenceTestServiceProxy(host, port);
  }
  void
  FenceTestServiceProxyBuilder::Destroy(FenceTestService *service) {
    delete service;
  }
} // END OF NAMESPACE proxy
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org