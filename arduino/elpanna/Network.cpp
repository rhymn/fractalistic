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


void Network::setstat(int temp){
  if(_client.connect(_server, 3000)){
    delay(1000);
    Serial.println("Ansluten.");
    _client.print("GET /setstat/temp/");
    _client.print(temp);
    _client.println(" HTTP/1.1");

    _client.print("Host: ");
    _client.print(_server);
    _client.println();

    _client.println("User-Agent: ArduinoEthernet");
    _client.println("Connection: close");
    _client.println();
  }

  delay(1000);

  Serial.println("Kopplar fran.");
  _client.stop();

  // Save state of connection
  _lastConn = _client.connected();
}


void Network::getsettings(){
  boolean loop = true;
  boolean isJson = false;
  String jsonStr = "";

  _client.flush();

  if(_client.connect(_server, 3000)){
    Serial.println("Ansluten.");
    _client.println("GET /getsettings HTTP/1.1");

    _client.print("Host: ");
    _client.print(_server);
    _client.println();

    _client.println("User-Agent: ArduinoEthernet");
    _client.println("Connection: close");
    _client.println();
  }

  else{
    _client.stop();
    Serial.println("Stoppar klient.");
  }

  delay(1000);

  while(loop){
    if(_client.available()){
      char in = _client.read();

      if(in == '{'){
        isJson = true;
      }

      if(isJson){
        jsonStr += in;
      }

      if(in == '}'){
        isJson = false;
      }

    }

    if(!_client.available() && !_client.connected()){
      loop = false;
    }
  }

  Serial.println(jsonStr);
  Serial.println();
  delay(200);

  _client.stop();

  // Save state of connection
  _lastConn = _client.connected();

}






IPAddress Network::getIP(){
  return Ethernet.localIP();
}

