/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:07:50
 * Name: enqueue_report.h
 * Description:
 *   This file contains definition of EnqueueReport class.
 ***************************************************************/

#ifndef _ORG_LABCRYPTO_FENCE_TRANSPORT__ENQUEUE_REPORT_H_
#define _ORG_LABCRYPTO_FENCE_TRANSPORT__ENQUEUE_REPORT_H_

#include <string>

#include <org/labcrypto/hottentot/primitives.h>


#include "enums.h"


namespace org {
namespace labcrypto {
namespace fence {
namespace transport {
  class EnqueueReport : public ::org::labcrypto::hottentot::Serializable {
  public:
    EnqueueReport() {
    }
    EnqueueReport(const EnqueueReport &);
    EnqueueReport(EnqueueReport *);
    virtual ~EnqueueReport() {}
  public:
    inline ::org::labcrypto::hottentot::UInt64 GetMasterMId() const {
      return masterMId_;
    }
    inline void SetMasterMId(::org::labcrypto::hottentot::UInt64 masterMId) {
      masterMId_ = masterMId;
    }
    inline ::org::labcrypto::hottentot::UInt64 GetSlaveMId() const {
      return slaveMId_;
    }
    inline void SetSlaveMId(::org::labcrypto::hottentot::UInt64 slaveMId) {
      slaveMId_ = slaveMId;
    }
    inline ::org::labcrypto::hottentot::Boolean GetFailed() const {
      return failed_;
    }
    inline void SetFailed(::org::labcrypto::hottentot::Boolean failed) {
      failed_ = failed;
    }
    inline ::org::labcrypto::hottentot::Utf8String GetErrorMessage() const {
      return errorMessage_;
    }
    inline void SetErrorMessage(::org::labcrypto::hottentot::Utf8String errorMessage) {
      errorMessage_ = errorMessage;
    }
  public:
    virtual unsigned char * Serialize(uint32_t * /* Pointer to length */);
    virtual void Deserialize(unsigned char * /* Data */, uint32_t /* Data length */);
  private:
    ::org::labcrypto::hottentot::UInt64 masterMId_;
    ::org::labcrypto::hottentot::UInt64 slaveMId_;
    ::org::labcrypto::hottentot::Boolean failed_;
    ::org::labcrypto::hottentot::Utf8String errorMessage_;
  };
} // END OF NAMESPACE transport
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org

#endif