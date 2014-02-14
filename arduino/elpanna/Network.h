/*
  Network Lib for Fractalistic project
  Created by David 5 feb 2014.
  Released into the public domain.
*/

#include <SPI.h>
#include <Ethernet.h>

#ifndef Network_h
#define Network_h

class Network{
  public:
    Network(byte mac[], IPAddress ip, IPAddress myDns, char server[], int port);
    void begin();
    void manageConn();
    void setstat(int temp, String mode, float output);
    String getsettings();
    IPAddress getIP();
    static String parseJson(String jsonStr, String key);

  private:
    boolean _lastConn;
    byte *_mac;
    IPAddress _ip;
    IPAddress _myDns;
    char *_server;
    int _port;
    EthernetClient _client;
};

#endif