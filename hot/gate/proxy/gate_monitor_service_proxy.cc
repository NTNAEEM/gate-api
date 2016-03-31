/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 31-03-2016 06:42:34
 * Name: gate_monitor_service_proxy.cc
 * Description:
 *   This file contains implementation of the proxy class.
 ***************************************************************/

#include <naeem/hottentot/runtime/configuration.h>
#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/utils.h>
#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/response.h>
#include <naeem/hottentot/runtime/protocol_v1.h>
#include <naeem/hottentot/runtime/proxy/fault.h>
#include <naeem/hottentot/runtime/proxy/tcp_client.h>
#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>
#include <naeem/hottentot/runtime/proxy/tcp_client_factory.h>

#include "gate_monitor_service_proxy.h"

#include "../message.h"


namespace ir {
namespace ntnaeem {
namespace gate {
namespace proxy {
  void
  GateMonitorServiceProxy::GetCurrentStat(
      ::naeem::hottentot::runtime::types::Utf8String &out
  ) {
    /*
     * Make request object
     */
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Making request object ..." << std::endl;
    }
    ::naeem::hottentot::runtime::Request request;
    request.SetServiceId(3344047614);
    request.SetMethodId(382105227);
    request.SetType(::naeem::hottentot::runtime::Request::InvokeStateless);
    /*
     * Serialize arguments
     */
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Request object is fill with serialized arguments." << std::endl;
    }
    /*
     * Connect to server
     */
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Connecting to server " << host_ << ":" << port_ << " ..." << std::endl;
    }
    ::naeem::hottentot::runtime::proxy::TcpClient *tcpClient = 
        ::naeem::hottentot::runtime::proxy::ProxyRuntime::GetTcpClientFactory()->CreateTcpClient(host_, port_);
    if (!tcpClient->Connect()) {
      delete tcpClient;
      throw std::runtime_error("Could not connect.");
    }
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Connected." << std::endl;
    }
    /*
     * Serialize request according to HOTP
     */
    ::naeem::hottentot::runtime::Protocol *protocol = new ::naeem::hottentot::runtime::ProtocolV1(tcpClient->GetRemoteSocketFD()); // TODO(kamran): Use factory.
    uint32_t requestSerializedDataLength = 0;
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Serializing request object ..." << std::endl;
    }
    unsigned char *requestSerializedData = protocol->SerializeRequest(request, &requestSerializedDataLength);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Request object is serialized." << std::endl;
    }
    /*
     * Send request byte array
     */
    uint32_t sendLength = 0;
    if (requestSerializedDataLength < 128) {
      sendLength = 1 + requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256) {
      sendLength = 2 + requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256 * 256) {
      sendLength = 3 + requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256 * 256 * 256) {
      sendLength = 4 + requestSerializedDataLength;
    }
    unsigned char *sendData = new unsigned char[sendLength];
    uint32_t c = 0;
    if (requestSerializedDataLength < 128) {
      sendData[c++] = requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256) {
      sendData[c++] = 0x81;
      sendData[c++] = requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256 * 256) {
      sendData[c++] = 0x82;
      sendData[c++] = requestSerializedDataLength / 256;
      sendData[c++] = requestSerializedDataLength % 256;
    } else if (requestSerializedDataLength < 256 * 256 * 256) {
      sendData[c] = 0x83;
      sendData[c + 1] = requestSerializedDataLength / (256 * 256);
      sendData[c + 2] = (requestSerializedDataLength - sendData[c + 1] * 256 * 256) / 256;
      sendData[c + 3] = requestSerializedDataLength % (256 * 256);
      c += 4;
    }
    for (uint32_t i = 0; i < requestSerializedDataLength; i++) {
      sendData[c++] = requestSerializedData[i];
    }
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Writing " << sendLength << "    Bytes to socket ..." << std::endl;
      ::naeem::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
    }
    try {
      tcpClient->Write(sendData, sendLength);
      if (::naeem::hottentot::runtime::Configuration::Verbose()) {
        ::naeem::hottentot::runtime::Logger::GetOut() << "Written." << std::endl;
      }
    } catch (std::exception &e) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error(e.what());
    } catch (...) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("Exception occurred while writing to server socket.");
    }
    delete [] sendData;
    delete [] requestSerializedData;
    /*
     * Read response from server
     */
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Waiting for response ..." << std::endl;
    }
    unsigned char buffer[256];
    while (!protocol->IsResponseComplete()) {
      int numOfReadBytes = tcpClient->Read(buffer, 256);
      if (numOfReadBytes == 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("Service is gone.");
      }
      if (numOfReadBytes < 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("Read from service failed.");
      }
      protocol->ProcessDataForResponse(buffer, numOfReadBytes);
    }
    if (protocol->GetResponse()->GetStatusCode() == 0) {
      /*
       * Response deserialization
       */
      if (::naeem::hottentot::runtime::Configuration::Verbose()) {
        ::naeem::hottentot::runtime::Utils::PrintArray("Response", protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      }
      out.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
    } else {
      ::naeem::hottentot::runtime::types::Utf8String faultMessage;
      faultMessage.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      uint8_t responseStatusCode = protocol->GetResponse()->GetStatusCode();
      /*
       * Finalization before throwing fault
       */
      tcpClient->Close();
      // delete serializedData;
      delete protocol;
      delete tcpClient;
      throw ::naeem::hottentot::runtime::proxy::Fault(responseStatusCode, faultMessage.ToStdString());
    }
    /*
     * Finalization
     */
    tcpClient->Close();
    // delete serializedData;
    delete protocol;
    delete tcpClient;
  }
} // END OF NAMESPACE proxy
}  // END OF NAMESPACE gate
}  // END OF NAMESPACE ntnaeem
}  // END OF NAMESPACE ir