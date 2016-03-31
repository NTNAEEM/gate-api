/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 31-03-2016 06:42:34
 * Name: gate_monitor_service_proxy_builder.h
 * Description:
 *   This file contains definition of the proxy builder class.
 ******************************************************************/

#ifndef _IR_NTNAEEM_GATE__PROXY__GATE_MONITOR_SERVICE_PROXY_BUILDER_H_
#define _IR_NTNAEEM_GATE__PROXY__GATE_MONITOR_SERVICE_PROXY_BUILDER_H_

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


namespace ir {
namespace ntnaeem {
namespace gate {
namespace proxy {
class GateMonitorService;
  class GateMonitorServiceProxyBuilder {
  public:
    static GateMonitorService* Create(std::string /* host */, uint32_t /* port */);
    static void Destroy(GateMonitorService *);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE gate
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif