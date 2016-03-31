/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 31-03-2016 01:18:44
 * Name: enqueue_report.h
 * Description:
 *   This file contains definition of EnqueueReport class.
 ***************************************************************/

#ifndef _IR_NTNAEEM_GATE_TRANSPORT__ENQUEUE_REPORT_H_
#define _IR_NTNAEEM_GATE_TRANSPORT__ENQUEUE_REPORT_H_

#include <string>

#include <naeem/hottentot/runtime/types/primitives.h>
#include <naeem/hottentot/runtime/serializable.h>


#include "enums.h"


namespace ir {
namespace ntnaeem {
namespace gate {
namespace transport {
  class EnqueueReport : public ::naeem::hottentot::runtime::Serializable {
  public:
    EnqueueReport() {
    }
    EnqueueReport(const EnqueueReport &);
    EnqueueReport(EnqueueReport *);
    virtual ~EnqueueReport() {}
  public:
    inline ::naeem::hottentot::runtime::types::UInt64 GetMasterMId() const {
      return masterMId_;
    }
    inline void SetMasterMId(::naeem::hottentot::runtime::types::UInt64 masterMId) {
      masterMId_ = masterMId;
    }
    inline ::naeem::hottentot::runtime::types::UInt64 GetSlaveMId() const {
      return slaveMId_;
    }
    inline void SetSlaveMId(::naeem::hottentot::runtime::types::UInt64 slaveMId) {
      slaveMId_ = slaveMId;
    }
    inline ::naeem::hottentot::runtime::types::Boolean GetFailed() const {
      return failed_;
    }
    inline void SetFailed(::naeem::hottentot::runtime::types::Boolean failed) {
      failed_ = failed;
    }
    inline ::naeem::hottentot::runtime::types::Utf8String GetErrorMessage() const {
      return errorMessage_;
    }
    inline void SetErrorMessage(::naeem::hottentot::runtime::types::Utf8String errorMessage) {
      errorMessage_ = errorMessage;
    }
  public:
    virtual unsigned char * Serialize(uint32_t * /* Pointer to length */);
    virtual void Deserialize(unsigned char * /* Data */, uint32_t /* Data length */);
  private:
    ::naeem::hottentot::runtime::types::UInt64 masterMId_;
    ::naeem::hottentot::runtime::types::UInt64 slaveMId_;
    ::naeem::hottentot::runtime::types::Boolean failed_;
    ::naeem::hottentot::runtime::types::Utf8String errorMessage_;
  };
} // END OF NAMESPACE transport
} // END OF NAMESPACE gate
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif