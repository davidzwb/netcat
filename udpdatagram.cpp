#include "udpdatagram.h"

bool UdpDatagram::start()
{
    if (flags == AI_PASSIVE) //server
    {
        if (bind() == -1)
            return false;
    }

    return true;
}

int UdpDatagram::send(char *buf, int len)
{
    return ::sendto(sockfd_, buf, len, 0, addr_.getSockaddrP(), sizeof(*addr_.getSockaddrP()));
}

int UdpDatagram::receive(char *buf, int len)
{
    sockaddr saddr;
    socklen_t slen;

    return ::recvfrom(sockfd_, buf, len, 0, &saddr, &slen);
}
