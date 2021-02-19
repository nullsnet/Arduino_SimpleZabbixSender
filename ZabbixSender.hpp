#ifndef __ZabbixSender_HPP
#define __ZabbixSender_HPP

#include <Arduino.h>

class ZabbixSender
{
private:
  enum ProtocolFlag : uint8_t{
    ZabbixCommunicationsProtocol = 0x01u,
    Compression = 0x02u,
  };
  const String Protocol = "ZBXD";
  const String Prefix = "{\"request\":\"sender data\",\"data\":[";
  const String Suffix = "]}";
  std::vector<String> data;
  String getPayload(void);
public:
  ZabbixSender(void){}
  void Add(String host,String key,String value);
  template <typename STREAM> size_t Send(STREAM &stream)
  {
    String payload = getPayload();
    if(!payload.isEmpty())
    {
      size_t sendsize;
      sendsize += stream.print(Protocol);
      sendsize += stream.write(ProtocolFlag::ZabbixCommunicationsProtocol);

      for (int i = 0; i < 64; i += 8) {
        sendsize += stream.write(lowByte(payload.length() >> i));
      }

      return sendsize + stream.print(payload);
    }else
    {
      return 0;
    }
  }
};

#endif