#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;



class TcpIPServer
{
public:
    TcpIPServer();

    void connectToClient();
    void sendString(std::string);
    void sendCoordinate(float x, float y);
    void sender(float x, float y);
    void sendThrowingInformation(std::pair<double,double> baseAngleAndAngularVelocity);
    void readFromClient();
    bool isConnected();

    void closeClientSocket();
    void closeSocket();





private:
    int listening;              //Socket
    sockaddr_in hint;
    int  clientSocket;
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

};

#endif // SERVER_H
