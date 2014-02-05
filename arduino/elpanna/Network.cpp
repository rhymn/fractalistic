#include "Arduino.h"
#include "Network.h"


Network::Network(){
  delay(1000);

  _mac = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  _ip = ;
  _dns = dns;
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

  }
}


IPAdress Network::getIP(){
  return Ethernet.localIP();
}


float PID::getOutputMin(){
  return _outMin;
}

