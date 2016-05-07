/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:20:04
 * Name: fence_monitor_service_server.cc
 * Description:
 *   This file contains definitions of sample stub.
 ******************************************************************/
 
#include <iostream>

#include <org/labcrypto/hottentot/runtime/configuration.h>
#include <org/labcrypto/hottentot/runtime/logger.h>
#include <org/labcrypto/hottentot/runtime/utils.h>
#include <org/labcrypto/hottentot/runtime/service/service_runtime.h>

#include "../message.h"

#include "fence_monitor_service_impl.h"


int
main(int argc, char **argv) {
  try {
    ::org::labcrypto::hottentot::runtime::Logger::Init();
    ::org::labcrypto::hottentot::runtime::service::ServiceRuntime::Init(argc, argv);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Starting server ..." << std::endl;
    }
    ::org::labcrypto::fence::FenceMonitorServiceImpl *service =
        new ::org::labcrypto::fence::FenceMonitorServiceImpl;
    ::org::labcrypto::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2000, service);
    ::org::labcrypto::hottentot::runtime::service::ServiceRuntime::Start();
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Service runtime is shutdown." << std::endl;
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "About to disable logging system ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::service::ServiceRuntime::Shutdown();
    ::org::labcrypto::hottentot::runtime::Logger::Shutdown();
  } catch (...) {
    std::cout << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Error." << std::endl;
    return 1;
  }
  return 0;
}
