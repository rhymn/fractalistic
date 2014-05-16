#include "Arduino.h"
#include "Network.h"

Network::Network(byte mac[], IPAddress ip, IPAddress myDns, char server[], int port)
 : _ip(ip), _myDns(myDns) 
{
  _mac = mac;
  _server = server;
  _port = port;
  _lastConn = false;
  EthernetClient _client;
}

void Network::begin(){
  if (Ethernet.begin(_mac) == 1) {
    Serial.print("IP from DHCP: ");
    Serial.println(Ethernet.localIP());
  } else{
    Ethernet.begin(_mac, _ip, _myDns);
  }

  delay(1000);
}

void Network::manageConn(){
  if (!_client.connected() && _lastConn) {
    _client.stop();
  }
}


/**
 * @todo Use http POST instead of GET
 *
 */
void Network::setstat(int temp, String mode, float output, int outputRes){
  if (_client.connect(_server, _port)) {
    Serial.print("Sending stats...");
    delay(500);
    _client.print("GET /setstat/temp/");
    _client.print(temp);
    _client.print("/mode/");
    _client.print(mode);
    _client.print("/output/");
    _client.print(output);
    _client.print("/outputRes/");
    _client.print(outputRes);
    _client.println(" HTTP/1.1");

    _client.print("Host: ");
    _client.print(_server);
    _client.println();

    _client.println("User-Agent: Fractalistic");
    _client.println("Connection: close");
    _client.println();

    Serial.println("OK");
  } else {
    // Try to obtain IP if this is the problem ..
    Network::begin();
  }

  delay(200);

  _client.stop();

  // Save state of connection
  _lastConn = _client.connected();
}


String Network::getsettings(){
  boolean loop = true;
  boolean isJson = false;
  String jsonStr = "";
  String mode = "";

  _client.flush();

  if(_client.connect(_server, _port)){
    Serial.print("Receiving settings...");
    delay(500);
    _client.println("GET /getsettings HTTP/1.1");

    _client.print("Host: ");
    _client.print(_server);
    _client.println();

    _client.println("User-Agent: ArduinoEthernet");
    _client.println("Connection: close");
    _client.println();

    Serial.println("OK");
  }

  else{
    _client.stop();
    // Serial.println("getsetttings(): Kan inte ansluta.");

    // Try to obtain IP if this is the problem ..
    Network::begin();
    return false;
  }

  delay(1000);

  loop = true;
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

  _client.stop();

  // Save state of connection
  _lastConn = _client.connected();

  return jsonStr;
}


String Network::parseJson(String jsonStr, String key){
  int kStart = jsonStr.indexOf(key);
  int divider = jsonStr.indexOf(":", kStart + 4);
  int vStart = jsonStr.indexOf("\"", divider) + 1;

  int vEnd = jsonStr.indexOf("\"", vStart) + 1;

  String value = jsonStr.substring(vStart, vEnd - 1);

  return value;
}

