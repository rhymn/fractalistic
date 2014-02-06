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
    Network(byte mac[], IPAddress ip, IPAddress myDns, char server[]);
    void manageConn();
    void request();
    IPAddress getIP();

  private:
    boolean _lastConn;
    byte *_mac;
    IPAddress _ip;
    IPAddress _myDns;
    char *_server;
    EthernetClient _client;
};

#endif