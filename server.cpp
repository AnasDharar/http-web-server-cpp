#include "server.hpp"

#include <unistd.h>
#include <cstring>

using namespace std;


// ==================== SimpleServer ====================

SimpleServer::SimpleServer(
    int domain,
    int type,
    int protocol,
    int port,
    unsigned long interface,
    int backlog
)
{
    listeningSocket = new ListeningSocket(
        domain,
        type,
        protocol,
        port,
        interface,
        backlog
    );
}


ListeningSocket* SimpleServer::getListeningSocket() {
    return listeningSocket;
}


SimpleServer::~SimpleServer() {
    delete listeningSocket;
}


// ==================== TestServer ====================

TestServer::TestServer(
    int domain,
    int type,
    int protocol,
    int port,
    unsigned long interface,
    int backlog
)
    : SimpleServer(
        domain,
        type,
        protocol,
        port,
        interface,
        backlog
    )
{
    run();
}


void TestServer::accepter() {

    cout << "Accepting connections..." << endl;

    struct sockaddr_in address =
        getListeningSocket()->getAddress();

    socklen_t address_length = sizeof(address);

    new_socket = accept(
        getListeningSocket()->getSocket(),
        (struct sockaddr*)&address,
        &address_length
    );

    if (new_socket < 0) {
        cerr << "Error accepting connection" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Connection accepted on socket: "
         << new_socket
         << endl;


    // Clear buffer before reading
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytes_read = read(
        new_socket,
        buffer,
        sizeof(buffer) - 1
    );

    if (bytes_read < 0) {
        cerr << "Error reading from socket" << endl;
        close(new_socket);
        return;
    }

    buffer[bytes_read] = '\0';
}


void TestServer::handler() {

    cout << "Handling requests..." << endl;

    cout << "Received data:" << endl;
    cout << "------------------------" << endl;
    cout << buffer;
    cout << "------------------------" << endl;
}


void TestServer::responder() {

    cout << "Sending response..." << endl;

    const char* response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 12\r\n"
        "\r\n"
        "Hello world!";

    ssize_t bytes_sent = send(
        new_socket,
        response,
        strlen(response),
        0
    );

    if (bytes_sent < 0) {
        cerr << "Error sending response" << endl;
    }
    else {
        cout << "Response sent." << endl;
    }

    close(new_socket);
}


void TestServer::run() {

    while (true) {
        accepter();
        handler();
        responder();
    }
}