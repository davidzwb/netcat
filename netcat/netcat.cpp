#include <iostream>
#include <string>

#include "../inetaddress.h"
#include "../tcpstream.h"
#include "../netcommon.h"

#define MAXBUFFER 64

//client will 'cat' data read from STDIN to connected server.
int client(char *ip, int port) {

    char buffer[MAXBUFFER];
    int nr;

    InetAddress addr(std::string(ip), port);
    TcpStream tcpstream(addr, false);

    if (!tcpstream.start())
        return 0;

    while (1) {

        ::memset(buffer, 0, MAXBUFFER);
        nr = Read(STDIN_FILENO, buffer, MAXBUFFER-1);

        if (nr == -1) {
            std::cout << "read error." << std::endl;
            return 0;
        }

        if (nr == 0) {
            //write finished.
            tcpstream.shutDownWrite();

            //wait for peer to disconnect
            while (tcpstream.readSome(buffer, MAXBUFFER)) {
                ;
            }

            return 0;
        }

        buffer[nr] = '\0';
        tcpstream.writeALL(buffer, nr);
    }

    return 0;
}

// receive data from client and output to STDOUT.
int server(int port) {

    InetAddress addr("", port);
    TcpStream tcpstream(addr, true);

    if (!tcpstream.start())
        return 0;

    TcpStream connstream;
    tcpstream.accept(connstream);

    char buffer[MAXBUFFER];
    int nr;

    while (1) {
        ::memset(buffer, 0, MAXBUFFER);
        nr = connstream.readSome(buffer, MAXBUFFER);

        if (nr == -1) {
            std::cout << "read error" << std::endl;
            return 0;
        }

        if (nr == 0) {
            return 0;
        }

        buffer[nr] = '\0';
        std::cout << buffer << std::endl;
    }

    return 0;
}


int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cout << "usage: netcat 127.0.0.1 27777 as a client" << std::endl;
        std::cout << "or: netcat -l 27777 as a server" << std::endl;
        return 0;
    }

    if (strcmp(argv[1], "-l") == 0)
        return server(atoi(argv[2]));
    else
        return client(argv[1], atoi(argv[2]));
}


