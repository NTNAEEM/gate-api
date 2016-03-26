/***********************************************************************
 * Generated by Hottentot CC Generator
 * Date: 27-03-2016 12:53:08
 * Name: gate_monitor_service_request_handler.h
 * Description:
 *   This file contains definition of service's request handler class.
 ***********************************************************************/

#ifndef _IR_NTNAEEM_GATE__SERVICE__GATE_MONITOR_SERVICE_REQUEST_HANDLER_H_
#define _IR_NTNAEEM_GATE__SERVICE__GATE_MONITOR_SERVICE_REQUEST_HANDLER_H_

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

#include <naeem/hottentot/runtime/service/request_handler.h>


namespace ir {
namespace ntnaeem {
namespace gate {
namespace service {
  class GateMonitorServiceRequestHandler : public ::naeem::hottentot::runtime::service::RequestHandler {
  public:
    GateMonitorServiceRequestHandler(::naeem::hottentot::runtime::service::Service *service)
      : ::naeem::hottentot::runtime::service::RequestHandler(service) {
    }
    virtual ~GateMonitorServiceRequestHandler() {}
  public:
    virtual void HandleRequest(::naeem::hottentot::runtime::Request &request,
                                                   ::naeem::hottentot::runtime::Response &response);
  };
} // END OF NAMESPACE service
} // END OF NAMESPACE gate
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif