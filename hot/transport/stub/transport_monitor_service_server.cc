/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-04-2016 12:37:55
 * Name: transport_monitor_service_server.cc
 * Description:
 *   This file contains definitions of sample stub.
 ******************************************************************/
 
#include <iostream>

#include <naeem/hottentot/runtime/configuration.h>
#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/service/service_runtime.h>

#include "../enqueue_report.h"
#include "../transport_message.h"

#include "transport_monitor_service_impl.h"


int
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::Logger::Init();
    ::naeem::hottentot::runtime::service::ServiceRuntime::Init(argc, argv);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Starting server ..." << std::endl;
    }
    ::ir::ntnaeem::gate::transport::TransportMonitorServiceImpl *service =
        new ::ir::ntnaeem::gate::transport::TransportMonitorServiceImpl;
    ::naeem::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2000, service);
    ::naeem::hottentot::runtime::service::ServiceRuntime::Start();
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Service runtime is shutdown." << std::endl;
      ::naeem::hottentot::runtime::Logger::GetOut() << "About to disable logging system ..." << std::endl;
    }
    ::naeem::hottentot::runtime::service::ServiceRuntime::Shutdown();
    ::naeem::hottentot::runtime::Logger::Shutdown();
  } catch (...) {
    std::cout << "Error." << std::endl;
    return 1;
  }
  return 0;
}
