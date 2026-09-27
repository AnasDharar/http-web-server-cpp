#include <iostream>
#include "Socket.hpp"
#include "server.hpp"
using namespace std;


int main(){
    TestServer* testServer = new TestServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 5);
}