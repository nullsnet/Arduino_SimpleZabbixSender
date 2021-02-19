#include "ZabbixSender.hpp"

void ZabbixSender::Add(String host,String key,String value)
{
  if(!host.isEmpty() && !key.isEmpty() && !value.isEmpty())
  {
    data.push_back("{\"host\":\"" + host + "\",\"key\":\"" + key + "\",\"value\":\"" + value + "\"}");
  }
}

String ZabbixSender::getPayload(){
  String joined;
  if(data.size())
  {
    for(int i = 0;i < data.size() - 1;i++)
    {
      joined += data[i] + ",";
    }
    joined += data.back();
  }
  return Prefix + joined + Suffix;
}