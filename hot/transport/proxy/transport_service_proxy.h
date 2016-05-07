/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:07:50
 * Name: transport_service_proxy.h
 * Description:
 *   This file contains definition of the proxy class.
 ***************************************************************/

#ifndef _ORG_LABCRYPTO_FENCE_TRANSPORT__PROXY__TRANSPORT_SERVICE_PROXY_H_
#define _ORG_LABCRYPTO_FENCE_TRANSPORT__PROXY__TRANSPORT_SERVICE_PROXY_H_

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

#include "transport_service.h"
#include "../enums.h"


namespace org {
namespace labcrypto {
namespace fence {
namespace transport {
class EnqueueReport;
class TransportMessage;
namespace proxy {
  class TransportServiceProxy : public TransportService, 
    public ::org::labcrypto::hottentot::runtime::proxy::Proxy {
  public:
    TransportServiceProxy(std::string host, uint32_t port) 
      : ::org::labcrypto::hottentot::runtime::proxy::Proxy(host, port) {}
    virtual ~TransportServiceProxy() {}
  public:
    virtual void Transmit(
      ::org::labcrypto::hottentot::List< ::org::labcrypto::fence::transport::TransportMessage> &messages, 
      ::org::labcrypto::hottentot::List< ::org::labcrypto::fence::transport::EnqueueReport> &out
    );
    virtual void Retrieve(
      ::org::labcrypto::hottentot::UInt32 &slaveId, 
      ::org::labcrypto::hottentot::List< ::org::labcrypto::fence::transport::TransportMessage> &out
    );
    virtual void Ack(
      ::org::labcrypto::hottentot::List< ::org::labcrypto::hottentot::UInt64> &masterMIds
    );
    virtual void GetStatus(
      ::org::labcrypto::hottentot::UInt64 &masterMId, 
      ::org::labcrypto::hottentot::UInt16 &out
    );
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE transport
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org

#endif