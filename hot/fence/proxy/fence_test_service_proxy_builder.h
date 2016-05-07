/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:20:04
 * Name: fence_test_service_proxy_builder.h
 * Description:
 *   This file contains definition of the proxy builder class.
 ******************************************************************/

#ifndef _ORG_LABCRYPTO_FENCE__PROXY__FENCE_TEST_SERVICE_PROXY_BUILDER_H_
#define _ORG_LABCRYPTO_FENCE__PROXY__FENCE_TEST_SERVICE_PROXY_BUILDER_H_

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <string>


namespace org {
namespace labcrypto {
namespace fence {
namespace proxy {
class FenceTestService;
  class FenceTestServiceProxyBuilder {
  public:
    static FenceTestService* Create(std::string /* host */, uint32_t /* port */);
    static void Destroy(FenceTestService *);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org

#endif