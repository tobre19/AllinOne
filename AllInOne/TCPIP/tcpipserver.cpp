#include "tcpipserver.h"
#include <fstream>
#include <sstream>
#include <iostream>

TcpIPServer::TcpIPServer()
{
    // Create a socket
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Can't create a socket! Quitting" << std::endl;

    }

    // Bind the ip address and port to a socket
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
}

void TcpIPServer::connectToClient()
{
    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        std::cout << host << " connected on port " << service << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
    }

//    while (true) {
//        int length = 200;
//        char received [length];
//        recv(clientSocket, received, sizeof(received), 0);
//        if (received[0] != '\0') {
//            std::cout << received << std::endl;
//        }
//    }


}

void TcpIPServer::closeClientSocket()
{

    // Close the socket
    close(clientSocket);
}

void TcpIPServer::closeSocket()
{
    close(listening);
}

void TcpIPServer::sendString(std::string data)
{
    const char* converter=data.c_str();

    send(clientSocket, converter, data.size(),0);
}

void TcpIPServer::sendCoordinate(float x, float y)
{
    std::string vX = std::to_string(x);
    std::string vY = std::to_string(y);

    std::string sending="[" + vX + "," + vY + ",0,0.613,-3.078,0]";

    std::cout << sending << std::endl;

    sendString(sending);
}

void TcpIPServer::sendThrowingInformation(std::pair<double,double> baseAngleAndAngularVelocity )
{
    std::string Abuff = std::to_string(baseAngleAndAngularVelocity.first);
    std::string Vbuff = std::to_string(baseAngleAndAngularVelocity.second);

    std::string sending="( " + Abuff + ",-0.4, 0, 0, 1.56722 ,-1.56722 )";

    sendString(sending);

    sendString("( 5 , 0.8 )");

    readFromClient();

    sending = "( " + Abuff+ " ,-1.83, 0, 0, 1.56722 ,-1.56722 )";

    sendString(sending);

    sendString("( 13, " + Vbuff + " )");

    readFromClient();

    std::cout << "This is it" << std::endl;

    for (int i = 0; i < 12; i++) {
        readFromClient();
    }

    std::cout << "This is it" << std::endl;
}

void TcpIPServer::readFromClient()
{
    int length = 100;
    char buffer [length];
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::string str(buffer);
    std::string str2;

    std::istringstream iss(str);

    std::getline(iss, str2, '\0');

//    char c = buffer[0];
//    int count = 1;
//    while (c != '\0') {
//        std::cout << c;
//        c = buffer[count];
//        count++;
//    }
//    std::cout << std::endl;
}

void TcpIPServer::readFloatFromClient()
{


    int length = 100;
    char buffer [length];
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::string str(buffer);
    std::string str2;

    std::istringstream iss(str);

    std::getline(iss, str2, '\0' );
//    char c = buffer[0];
//    int count = 1;
//    while (c != '\0') {
//        std::cout << c;
//        c = buffer[count];
//        count++;
//    }
//    std::cout << std::endl;

}

bool TcpIPServer::isConnected()
{
    if (listening == 0) {
        return false;
    }
    return true;
}
