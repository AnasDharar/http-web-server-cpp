#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Socket.hpp"

class SimpleServer {
private:
    ListeningSocket* listeningSocket;

    virtual void accepter() = 0;
    virtual void handler() = 0;
    virtual void responder() = 0;

public:
    SimpleServer(
        int domain,
        int type,
        int protocol,
        int port,
        unsigned long interface,
        int backlog
    );

    virtual void run() = 0;

    ListeningSocket* getListeningSocket();

    virtual ~SimpleServer();
};


class TestServer : public SimpleServer {
private:
    char buffer[30000] = {0};
    int new_socket;

public:
    TestServer(
        int domain,
        int type,
        int protocol,
        int port,
        unsigned long interface,
        int backlog
    );

    void accepter() override;
    void handler() override;
    void responder() override;
    void run() override;
};

#endif // SERVER_HPP