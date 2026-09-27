#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket {
private:
    int sock;
    int connection;
    struct sockaddr_in address;

public:
    Socket(
        int domain,
        int type,
        int protocol,
        int port,
        unsigned long interface
    );

    int getSocket();
    int getConnection();
    struct sockaddr_in getAddress();

    void setConnection(int conn);

    virtual ~Socket() = default;
};


class BindingSocket : public Socket {
public:
    BindingSocket(
        int domain,
        int type,
        int protocol,
        int port,
        unsigned long interface
    );
};


class ConnectingSocket : public Socket {
public:
    ConnectingSocket(
        int domain,
        int type,
        int protocol,
        int port,
        unsigned long interface
    );
};


class ListeningSocket : public BindingSocket {
private:
    int backlog;
    int listen_sock;

public:
    ListeningSocket(
        int domain,
        int type,
        int protocol,
        int port,
        unsigned long interface,
        int bklg
    );
};

#endif // SOCKET_HPP