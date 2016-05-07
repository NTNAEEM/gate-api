/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:20:04
 * Name: fence_test_service_proxy.h
 * Description:
 *   This file contains definition of the proxy class.
 ***************************************************************/

#ifndef _ORG_LABCRYPTO_FENCE__PROXY__FENCE_TEST_SERVICE_PROXY_H_
#define _ORG_LABCRYPTO_FENCE__PROXY__FENCE_TEST_SERVICE_PROXY_H_

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

#include <org/labcrypto/hottentot/primitives.h>
#include <org/labcrypto/hottentot/runtime/proxy/proxy.h>

#include "fence_test_service.h"
#include "../enums.h"


namespace org {
namespace labcrypto {
namespace fence {
class Message;
namespace proxy {
  class FenceTestServiceProxy : public FenceTestService, 
    public ::org::labcrypto::hottentot::runtime::proxy::Proxy {
  public:
    FenceTestServiceProxy(std::string host, uint32_t port) 
      : ::org::labcrypto::hottentot::runtime::proxy::Proxy(host, port) {}
    virtual ~FenceTestServiceProxy() {}
  public:
    virtual void EnqueueAsIncomingMessage(
      ::org::labcrypto::fence::Message &message, 
      ::org::labcrypto::hottentot::UInt64 &out
    );
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org

#endif