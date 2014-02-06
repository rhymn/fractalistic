#include "Arduino.h"
#include "Network.h"


Network::Network(byte mac[], IPAddress ip, IPAddress myDns, char server[])
 : _ip(ip), _myDns(myDns) 
{
  _mac = mac;
  _server = server;

  _lastConn = false;

  // Init instance
  EthernetClient _client;
}

void Network::begin(){
  // Start ethernet connection
  Ethernet.begin(_mac, _ip, _myDns);
}

void Network::manageConn(){
  if(!_client.connected() && _lastConn){
    _client.stop();
  }
}


void Network::request(){
  if(_client.connect(_server, 80)){
    _client.println("GET /setstat HTTP/1.1");
    _client.println("Host: r.pnd.se");
    _client.println("User-Agent: ArduinoEthernet");
    _client.println("Connection: close");
  }

  else{
    _client.stop();
  }

  while(Serial.available() > 0){
    char in = Serial.read();
  }


  // Save state of connection
  _lastConn = _client.connected();
}


IPAddress Network::getIP(){
  return Ethernet.localIP();
}

