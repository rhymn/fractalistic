#include "Arduino.h"
#include "Network.h"


Network::Network(byte mac[], IPAdress ip, IPAdress dns, char server[])
 : _ip(ip), _dns(dns) 
{
  delay(1000);

  _mac = mac;
  _server = server;

  _lastConn = false;

  // Init instance
  EthernetClient _client;

  // Start ethernet connection
  Ethernet.begin(mac, ip, dns);
}

void Network::manageConn(){
  if(!_client.connected() && _lastConn){
    _client.stop();
  }
}


void Network::request(){
  if(_client.connect(_server, 80)){
    _client.println("GET /getsettings HTTP/1.1");
    _client.println("Host: " + _server);
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


IPAdress Network::getIP(){
  return Ethernet.localIP();
}


float PID::getOutputMin(){
  return _outMin;
}

