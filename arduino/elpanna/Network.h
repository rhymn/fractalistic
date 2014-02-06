/*
  Network Lib for Fractalistic project
  Created by David 5 feb 2014.
  Released into the public domain.
*/

#ifndef Network_h
#define Network_h

class Network{
  public:
    Network();
    void manageConn();
    void request();

  private:
    boolean _lastConn;
    byte _mac[];
    IPAddress _ip;
    IPAddress _dns;
    Client _client;
};

#endif