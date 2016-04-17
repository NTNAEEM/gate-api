/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   This file contains definition of an abstract service class.
 ******************************************************************/
package ir.ntnaeem.gate.hotgen;

import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.ByteArrayToInteger;

public class Message {
  private long id;
  private long relId;
  private String label = "";
  private byte[] content;
  public void setId(long id) {
    this.id = id;
  }
  public long getId() {
    return id;
  }
  public void setRelId(long relId) {
    this.relId = relId;
  }
  public long getRelId() {
    return relId;
  }
  public void setLabel(String label) {
    this.label = label;
  }
  public String getLabel() {
    return label;
  }
  public void setContent(byte[] content) {
    this.content = content;
  }
  public byte[] getContent() {
    return content;
  }
  @Override 
  public String toString() { 
    return "Message{" + 
      "id = '" + id + '\'' + 
      ",relId = '" + relId + '\'' + 
      ",label = '" + label + '\'' + 
      ",content = '" + content + '\'' + 
      "}"; 
  }
	
  public byte[] serialize() {
    byte[] serializedId = PDTSerializer.getInt64(id);
    byte[] serializedRelId = PDTSerializer.getInt64(relId);
    byte[] serializedLabel = PDTSerializer.getString(label);
    byte[] serializedContent = PDTSerializer.getData(content);
    byte[] output = new byte[serializedId.length + serializedRelId.length + serializedLabel.length + serializedContent.length];
    int counter = 0;
    //use a loop for every property
    for (int i = 0; i < serializedId.length; i++) {
      output[counter++] = serializedId[i];
    }
    for (int i = 0; i < serializedRelId.length; i++) {
      output[counter++] = serializedRelId[i];
    }
    for (int i = 0; i < serializedLabel.length; i++) {
      output[counter++] = serializedLabel[i];
    }
    for (int i = 0; i < serializedContent.length; i++) {
      output[counter++] = serializedContent[i];
    }
    return output;
  }
    
  public void deserialize(byte[] serializedByteArray) {
    if(serializedByteArray.length != 0){
      int counter = 0;
      int dataLength = 0;
      int numbersOfBytesForDataLength;
      //do for every property
    //id : long
    byte[] idByteArray = new byte[8];
    for(int i = 0 ; i < 8 ; i++){
      idByteArray[i] = serializedByteArray[counter++];
    }
    setId(PDTDeserializer.getInt64(idByteArray));
    //relId : long
    byte[] relIdByteArray = new byte[8];
    for(int i = 0 ; i < 8 ; i++){
      relIdByteArray[i] = serializedByteArray[counter++];
    }
    setRelId(PDTDeserializer.getInt64(relIdByteArray));
    //label : String
    dataLength = 0;
    if(( serializedByteArray[counter] & 0x80) == 0 ) {
      dataLength = serializedByteArray[counter++];
    }else{
      numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;
      byte[] serializedByteArrayLength = new byte[numbersOfBytesForDataLength];
      for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
        serializedByteArrayLength[i] = serializedByteArray[counter++];
      }
      dataLength = ByteArrayToInteger.getInt(serializedByteArrayLength);
    }
    byte[] labelByteArray = new byte[dataLength];
    System.arraycopy(serializedByteArray,counter,labelByteArray,0,dataLength);
    counter += dataLength;
    setLabel(PDTDeserializer.getString(labelByteArray));
    //content : byte[]
    dataLength = 0;
    if(( serializedByteArray[counter] & 0x80) == 0 ) {
      dataLength = serializedByteArray[counter++];
    }else{
      numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;
      byte[] serializedByteArrayLength = new byte[numbersOfBytesForDataLength];
      for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
        serializedByteArrayLength[i] = serializedByteArray[counter++];
      }
      dataLength = ByteArrayToInteger.getInt(serializedByteArrayLength);
    }
    byte[] contentByteArray = new byte[dataLength];
    System.arraycopy(serializedByteArray,counter,contentByteArray,0,dataLength);
    counter += dataLength;
    setContent(contentByteArray);

    }
  }
}