/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:20:04
 * Name: fence_test_service_impl.cc
 * Description:
 *   This file contains empty implementation of sample stub.
 ******************************************************************/
 
#include <org/labcrypto/hottentot/runtime/configuration.h>
#include <org/labcrypto/hottentot/runtime/logger.h>
#include <org/labcrypto/hottentot/runtime/utils.h>

#include "fence_test_service_impl.h"

#include "../message.h"


namespace org {
namespace labcrypto {
namespace fence {
  void
  FenceTestServiceImpl::OnInit() {
    // TODO: Called when service is initializing.
  }
  void
  FenceTestServiceImpl::OnShutdown() {
    // TODO: Called when service is shutting down.
  }
  void
  FenceTestServiceImpl::EnqueueAsIncomingMessage(
    ::org::labcrypto::fence::Message &message, 
    ::org::labcrypto::hottentot::UInt64 &out, 
    ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
  ) {
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "FenceTestServiceImpl::EnqueueAsIncomingMessage() is called." << std::endl;
    }
    // TODO
  }
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org