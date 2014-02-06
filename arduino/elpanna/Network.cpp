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
  if(Ethernet.begin(_mac) == 1){
    Serial.print("ip fran dhcp:)");
    Serial.println();
  }

  else{
    Serial.print("dhcp svarar ej. Satter statisk ip.");
    Serial.println();
    Ethernet.begin(_mac, _ip, _myDns);
  }

  delay(1000);
}

void Network::manageConn(){
  if(!_client.connected() && _lastConn){
    _client.stop();
  }
}


void Network::request(int temp){

  Serial.print("T: ");
  Serial.print(temp);
  Serial.println();

  if(_client.connect(_server, 80)){
    Serial.println("Ansluten.");
    _client.println("GET /setstat HTTP/1.1");
    _client.println("Host: r.pnd.se");
    _client.println("User-Agent: ArduinoEthernet");
    _client.println("Connection: close");
    _client.println();
  }

  else{
    _client.stop();
    Serial.println("Stoppar klient.");
  }

  while(_client.available() > 0){
    char in = _client.read();
    Serial.print(in);
  }


  // Save state of connection
  _lastConn = _client.connected();
}


IPAddress Network::getIP(){
  return Ethernet.localIP();
}

