#ifndef UDPDATAGRAM_H
#define UDPDATAGRAM_H

#include <sys/types.h>
#include <sys/socket.h>

#include "socket.h"

class UdpDatagram : public Socket
{
public:
    UdpDatagram() : Socket() {}
    UdpDatagram(InetAddress addr, bool isPassive = false) : Socket(addr, false, isPassive) {}
    ~UdpDatagram() = default;

    bool start();

    int send(char *buf, int len);
    int receive(char *buf, int len);
};

#endif // UDPDATAGRAM_H
