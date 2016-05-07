/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 07-05-2016 11:07:50
 * Name: transport_service_proxy.cc
 * Description:
 *   This file contains implementation of the proxy class.
 ***************************************************************/

#include <org/labcrypto/hottentot/runtime/configuration.h>
#include <org/labcrypto/hottentot/runtime/logger.h>
#include <org/labcrypto/hottentot/runtime/utils.h>
#include <org/labcrypto/hottentot/runtime/request.h>
#include <org/labcrypto/hottentot/runtime/response.h>
#include <org/labcrypto/hottentot/runtime/protocol_v1.h>
#include <org/labcrypto/hottentot/runtime/proxy/fault.h>
#include <org/labcrypto/hottentot/runtime/proxy/tcp_client.h>
#include <org/labcrypto/hottentot/runtime/proxy/proxy_runtime.h>
#include <org/labcrypto/hottentot/runtime/proxy/tcp_client_factory.h>

#include "transport_service_proxy.h"

#include "../enqueue_report.h"
#include "../transport_message.h"


namespace org {
namespace labcrypto {
namespace fence {
namespace transport {
namespace proxy {
  void
  TransportServiceProxy::Transmit(
      ::org::labcrypto::hottentot::List< ::org::labcrypto::fence::transport::TransportMessage> &messages, 
      ::org::labcrypto::hottentot::List< ::org::labcrypto::fence::transport::EnqueueReport> &out
  ) {
    /*
     * Make request object
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Making request object ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Request request;
    request.SetServiceId(2012270607);
    request.SetMethodId(3587101452);
    request.SetType(::org::labcrypto::hottentot::runtime::Request::InvokeStateless);
    /*
     * Serialize arguments
     */
    uint32_t serializedDataLength = 0;
    unsigned char *serializedData = 0;
    /*
     * Serialization of argument 'messages'
     */
    serializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing argument messages ..." << std::endl;
    }
    serializedData = messages.Serialize(&serializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "messages is serialized." << std::endl;
    }
    request.AddArgument(serializedData, serializedDataLength);

    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is fill with serialized arguments." << std::endl;
    }
    /*
     * Connect to server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connecting to server " << host_ << ":" << port_ << " ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::proxy::TcpClient *tcpClient = 
        ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::GetTcpClientFactory()->CreateTcpClient(host_, port_);
    if (!tcpClient->Connect()) {
      delete tcpClient;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Could not connect.");
    }
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connected." << std::endl;
    }
    /*
     * Serialize request according to HOTP
     */
    ::org::labcrypto::hottentot::runtime::Protocol *protocol = new ::org::labcrypto::hottentot::runtime::ProtocolV1(tcpClient->GetRemoteSocketFD()); // TODO(kamran): Use factory.
    uint32_t requestSerializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing request object ..." << std::endl;
    }
    unsigned char *requestSerializedData = protocol->SerializeRequest(request, &requestSerializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is serialized." << std::endl;
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
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Writing " << sendLength << "    Bytes to socket ..." << std::endl;
      ::org::labcrypto::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
    }
    try {
      tcpClient->Write(sendData, sendLength);
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Written." << std::endl;
      }
    } catch (std::exception &e) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: " + e.what());
    } catch (...) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Exception occurred while writing to server socket.");
    }
    delete [] sendData;
    delete [] requestSerializedData;
    /*
     * Read response from server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Waiting for response ..." << std::endl;
    }
    unsigned char buffer[256];
    while (!protocol->IsResponseComplete()) {
      int numOfReadBytes = tcpClient->Read(buffer, 256);
      if (numOfReadBytes == 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Service is gone.");
      }
      if (numOfReadBytes < 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Read from service failed.");
      }
      protocol->ProcessDataForResponse(buffer, numOfReadBytes);
    }
    if (protocol->GetResponse()->GetStatusCode() == 0) {
      /*
       * Response deserialization
       */
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Response", protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      }
      out.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
    } else {
      ::org::labcrypto::hottentot::Utf8String faultMessage;
      faultMessage.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      uint8_t responseStatusCode = protocol->GetResponse()->GetStatusCode();
      /*
       * Finalization before throwing fault
       */
      tcpClient->Close();
      // delete serializedData;
      delete protocol;
      delete tcpClient;
      throw ::org::labcrypto::hottentot::runtime::proxy::Fault(responseStatusCode, faultMessage.ToStdString());
    }
    /*
     * Finalization
     */
    tcpClient->Close();
    // delete serializedData;
    delete protocol;
    delete tcpClient;
  }
  void
  TransportServiceProxy::Retrieve(
      ::org::labcrypto::hottentot::UInt32 &slaveId, 
      ::org::labcrypto::hottentot::List< ::org::labcrypto::fence::transport::TransportMessage> &out
  ) {
    /*
     * Make request object
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Making request object ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Request request;
    request.SetServiceId(2012270607);
    request.SetMethodId(2373442179);
    request.SetType(::org::labcrypto::hottentot::runtime::Request::InvokeStateless);
    /*
     * Serialize arguments
     */
    uint32_t serializedDataLength = 0;
    unsigned char *serializedData = 0;
    /*
     * Serialization of argument 'slaveId'
     */
    serializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing argument slaveId ..." << std::endl;
    }
    serializedData = slaveId.Serialize(&serializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "slaveId is serialized." << std::endl;
    }
    request.AddArgument(serializedData, serializedDataLength);

    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is fill with serialized arguments." << std::endl;
    }
    /*
     * Connect to server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connecting to server " << host_ << ":" << port_ << " ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::proxy::TcpClient *tcpClient = 
        ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::GetTcpClientFactory()->CreateTcpClient(host_, port_);
    if (!tcpClient->Connect()) {
      delete tcpClient;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Could not connect.");
    }
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connected." << std::endl;
    }
    /*
     * Serialize request according to HOTP
     */
    ::org::labcrypto::hottentot::runtime::Protocol *protocol = new ::org::labcrypto::hottentot::runtime::ProtocolV1(tcpClient->GetRemoteSocketFD()); // TODO(kamran): Use factory.
    uint32_t requestSerializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing request object ..." << std::endl;
    }
    unsigned char *requestSerializedData = protocol->SerializeRequest(request, &requestSerializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is serialized." << std::endl;
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
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Writing " << sendLength << "    Bytes to socket ..." << std::endl;
      ::org::labcrypto::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
    }
    try {
      tcpClient->Write(sendData, sendLength);
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Written." << std::endl;
      }
    } catch (std::exception &e) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: " + e.what());
    } catch (...) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Exception occurred while writing to server socket.");
    }
    delete [] sendData;
    delete [] requestSerializedData;
    /*
     * Read response from server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Waiting for response ..." << std::endl;
    }
    unsigned char buffer[256];
    while (!protocol->IsResponseComplete()) {
      int numOfReadBytes = tcpClient->Read(buffer, 256);
      if (numOfReadBytes == 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Service is gone.");
      }
      if (numOfReadBytes < 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Read from service failed.");
      }
      protocol->ProcessDataForResponse(buffer, numOfReadBytes);
    }
    if (protocol->GetResponse()->GetStatusCode() == 0) {
      /*
       * Response deserialization
       */
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Response", protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      }
      out.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
    } else {
      ::org::labcrypto::hottentot::Utf8String faultMessage;
      faultMessage.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      uint8_t responseStatusCode = protocol->GetResponse()->GetStatusCode();
      /*
       * Finalization before throwing fault
       */
      tcpClient->Close();
      // delete serializedData;
      delete protocol;
      delete tcpClient;
      throw ::org::labcrypto::hottentot::runtime::proxy::Fault(responseStatusCode, faultMessage.ToStdString());
    }
    /*
     * Finalization
     */
    tcpClient->Close();
    // delete serializedData;
    delete protocol;
    delete tcpClient;
  }
  void
  TransportServiceProxy::Ack(
      ::org::labcrypto::hottentot::List< ::org::labcrypto::hottentot::UInt64> &masterMIds
  ) {
    /*
     * Make request object
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Making request object ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Request request;
    request.SetServiceId(2012270607);
    request.SetMethodId(1694709958);
    request.SetType(::org::labcrypto::hottentot::runtime::Request::InvokeStateless);
    /*
     * Serialize arguments
     */
    uint32_t serializedDataLength = 0;
    unsigned char *serializedData = 0;
    /*
     * Serialization of argument 'masterMIds'
     */
    serializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing argument masterMIds ..." << std::endl;
    }
    serializedData = masterMIds.Serialize(&serializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "masterMIds is serialized." << std::endl;
    }
    request.AddArgument(serializedData, serializedDataLength);

    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is fill with serialized arguments." << std::endl;
    }
    /*
     * Connect to server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connecting to server " << host_ << ":" << port_ << " ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::proxy::TcpClient *tcpClient = 
        ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::GetTcpClientFactory()->CreateTcpClient(host_, port_);
    if (!tcpClient->Connect()) {
      delete tcpClient;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Could not connect.");
    }
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connected." << std::endl;
    }
    /*
     * Serialize request according to HOTP
     */
    ::org::labcrypto::hottentot::runtime::Protocol *protocol = new ::org::labcrypto::hottentot::runtime::ProtocolV1(tcpClient->GetRemoteSocketFD()); // TODO(kamran): Use factory.
    uint32_t requestSerializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing request object ..." << std::endl;
    }
    unsigned char *requestSerializedData = protocol->SerializeRequest(request, &requestSerializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is serialized." << std::endl;
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
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Writing " << sendLength << "    Bytes to socket ..." << std::endl;
      ::org::labcrypto::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
    }
    try {
      tcpClient->Write(sendData, sendLength);
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Written." << std::endl;
      }
    } catch (std::exception &e) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: " + e.what());
    } catch (...) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Exception occurred while writing to server socket.");
    }
    delete [] sendData;
    delete [] requestSerializedData;
    /*
     * Read response from server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Waiting for response ..." << std::endl;
    }
    unsigned char buffer[256];
    while (!protocol->IsResponseComplete()) {
      int numOfReadBytes = tcpClient->Read(buffer, 256);
      if (numOfReadBytes == 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Service is gone.");
      }
      if (numOfReadBytes < 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Read from service failed.");
      }
      protocol->ProcessDataForResponse(buffer, numOfReadBytes);
    }
    if (protocol->GetResponse()->GetStatusCode() == 0) {
    } else {
      ::org::labcrypto::hottentot::Utf8String faultMessage;
      faultMessage.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      uint8_t responseStatusCode = protocol->GetResponse()->GetStatusCode();
      /*
       * Finalization before throwing fault
       */
      tcpClient->Close();
      // delete serializedData;
      delete protocol;
      delete tcpClient;
      throw ::org::labcrypto::hottentot::runtime::proxy::Fault(responseStatusCode, faultMessage.ToStdString());
    }
    /*
     * Finalization
     */
    tcpClient->Close();
    // delete serializedData;
    delete protocol;
    delete tcpClient;
  }
  void
  TransportServiceProxy::GetStatus(
      ::org::labcrypto::hottentot::UInt64 &masterMId, 
      ::org::labcrypto::hottentot::UInt16 &out
  ) {
    /*
     * Make request object
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Making request object ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Request request;
    request.SetServiceId(2012270607);
    request.SetMethodId(1154637673);
    request.SetType(::org::labcrypto::hottentot::runtime::Request::InvokeStateless);
    /*
     * Serialize arguments
     */
    uint32_t serializedDataLength = 0;
    unsigned char *serializedData = 0;
    /*
     * Serialization of argument 'masterMId'
     */
    serializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing argument masterMId ..." << std::endl;
    }
    serializedData = masterMId.Serialize(&serializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "masterMId is serialized." << std::endl;
    }
    request.AddArgument(serializedData, serializedDataLength);

    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is fill with serialized arguments." << std::endl;
    }
    /*
     * Connect to server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connecting to server " << host_ << ":" << port_ << " ..." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::proxy::TcpClient *tcpClient = 
        ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::GetTcpClientFactory()->CreateTcpClient(host_, port_);
    if (!tcpClient->Connect()) {
      delete tcpClient;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Could not connect.");
    }
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Connected." << std::endl;
    }
    /*
     * Serialize request according to HOTP
     */
    ::org::labcrypto::hottentot::runtime::Protocol *protocol = new ::org::labcrypto::hottentot::runtime::ProtocolV1(tcpClient->GetRemoteSocketFD()); // TODO(kamran): Use factory.
    uint32_t requestSerializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing request object ..." << std::endl;
    }
    unsigned char *requestSerializedData = protocol->SerializeRequest(request, &requestSerializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is serialized." << std::endl;
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
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Writing " << sendLength << "    Bytes to socket ..." << std::endl;
      ::org::labcrypto::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
    }
    try {
      tcpClient->Write(sendData, sendLength);
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Written." << std::endl;
      }
    } catch (std::exception &e) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: " + e.what());
    } catch (...) {
      delete protocol;
      delete tcpClient;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Exception occurred while writing to server socket.");
    }
    delete [] sendData;
    delete [] requestSerializedData;
    /*
     * Read response from server
     */
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Waiting for response ..." << std::endl;
    }
    unsigned char buffer[256];
    while (!protocol->IsResponseComplete()) {
      int numOfReadBytes = tcpClient->Read(buffer, 256);
      if (numOfReadBytes == 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Service is gone.");
      }
      if (numOfReadBytes < 0) {
        delete protocol;
        delete tcpClient;
        throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Read from service failed.");
      }
      protocol->ProcessDataForResponse(buffer, numOfReadBytes);
    }
    if (protocol->GetResponse()->GetStatusCode() == 0) {
      /*
       * Response deserialization
       */
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Response", protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      }
      out.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
    } else {
      ::org::labcrypto::hottentot::Utf8String faultMessage;
      faultMessage.Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
      uint8_t responseStatusCode = protocol->GetResponse()->GetStatusCode();
      /*
       * Finalization before throwing fault
       */
      tcpClient->Close();
      // delete serializedData;
      delete protocol;
      delete tcpClient;
      throw ::org::labcrypto::hottentot::runtime::proxy::Fault(responseStatusCode, faultMessage.ToStdString());
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
} // END OF NAMESPACE transport
} // END OF NAMESPACE fence
} // END OF NAMESPACE labcrypto
} // END OF NAMESPACE org