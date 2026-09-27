#include <iostream>
#include "Socket.cpp"
using namespace std;
int main() {
    // Simple Binding Socket
    cout<< "Creating Binding Socket..." << endl;
    BindingSocket* bindingSocket = new BindingSocket(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);

    cout<< "Binding Socket created." << endl;

    //Listening Socket
    cout<< "Creating Listening Socket..." << endl;
    ListeningSocket* listeningSocket = new ListeningSocket(AF_INET, SOCK_STREAM, 0, 8081, INADDR_ANY, 5);

    cout<< "Listening Socket created." << endl;
    return 0;
}