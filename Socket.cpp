#include "Socket.hpp"

#include <cstring>
#include <unistd.h>

using namespace std;


// ==================== Socket ====================

Socket::Socket(
    int domain,
    int type,
    int protocol,
    int port,
    unsigned long interface
) {
    // Create socket
    sock = socket(domain, type, protocol);

    if (sock < 0) {
        cerr << "Error creating socket" << endl;
        exit(EXIT_FAILURE);
    }

    // Clear address structure
    memset(&address, 0, sizeof(address));

    // Configure address
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = interface;
}


int Socket::getSocket() {
    return sock;
}


int Socket::getConnection() {
    return connection;
}


struct sockaddr_in Socket::getAddress() {
    return address;
}


void Socket::setConnection(int conn) {
    connection = conn;
}


// ==================== BindingSocket ====================

BindingSocket::BindingSocket(
    int domain,
    int type,
    int protocol,
    int port,
    unsigned long interface
)
    : Socket(domain, type, protocol, port, interface)
{
    struct sockaddr_in address = getAddress();
    int opt = 1;

    if (setsockopt(
        getSocket(),
        SOL_SOCKET,
        SO_REUSEADDR,
        &opt,
        sizeof(opt)
    ) < 0) {
        cerr << "Error setting SO_REUSEADDR" << endl;
    }
    if (bind(
        getSocket(),
        (struct sockaddr*)&address,
        sizeof(address)
    ) < 0) {
        cerr << "Error binding server socket" << endl;
        exit(EXIT_FAILURE);
    }

    setConnection(0);

    cout << "Server socket bound to port "
         << ntohs(address.sin_port)
         << endl;
}


// ==================== ConnectingSocket ====================

ConnectingSocket::ConnectingSocket(
    int domain,
    int type,
    int protocol,
    int port,
    unsigned long interface
)
    : Socket(domain, type, protocol, port, interface)
{
    struct sockaddr_in address = getAddress();

    int result = connect(
        getSocket(),
        (struct sockaddr*)&address,
        sizeof(address)
    );

    if (result < 0) {
        cerr << "Error connecting to server" << endl;
        exit(EXIT_FAILURE);
    }

    setConnection(result);

    cout << "Client socket connected to server on port "
         << ntohs(address.sin_port)
         << endl;
}


// ==================== ListeningSocket ====================

ListeningSocket::ListeningSocket(
    int domain,
    int type,
    int protocol,
    int port,
    unsigned long interface,
    int bklg
)
    : BindingSocket(domain, type, protocol, port, interface),
      backlog(bklg)
{
    listen_sock = listen(
        getSocket(),
        backlog
    );

    if (listen_sock < 0) {
        cerr << "Error listening on socket" << endl;
        exit(EXIT_FAILURE);
    }

    setConnection(0);

    cout << "Listening on socket with backlog: "
         << backlog
         << endl;
}