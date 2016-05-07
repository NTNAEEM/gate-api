/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:07:50
 * Name: transport_monitor_service_impl.h
 * Description:
 *   This file contains definitions of sample stub.
 ******************************************************************/
 
#ifndef _ORG_LABCRYPTO_FENCE_TRANSPORT__TRANSPORT_MONITOR_SERVICE_IMPL_H_
#define _ORG_LABCRYPTO_FENCE_TRANSPORT__TRANSPORT_MONITOR_SERVICE_IMPL_H_

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

#include "../service/abstract_transport_monitor_service.h"


namespace org {
namespace labcrypto {
namespace fence {
namespace transport {
  class TransportMonitorServiceImpl : public ::org::labcrypto::fence::transport::service::AbstractTransportMonitorService {
  public:
    TransportMonitorServiceImpl() {}
    virtual ~TransportMonitorServiceImpl() {}
  public:
    virtual void OnInit();
    virtual void OnShutdown();
    virtual void GetCurrentStat(
      ::org::labcrypto::hottentot::Utf8String &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    );
  };
} // END OF NAMESPACE transport
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org

#endif