#include "tcpipserver.h"
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

void TcpIPServer::connectToClientandStoplistening()
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




double TcpIPServer::getAngularVelocity(double ballHeight, double distanceToCup)
{
    double v;
    //v = (sqrt(62990043593.51803) * distanceToCup * sqrt(351457206744.5472 * distanceToCup + 906137116100.7427 * ballHeight)) / (2 * (351457206744.5472 * distanceToCup + 906137116100.7427 * ballHeight)); brug af albue
    //v = (0.04282 * distanceToCup * sqrt(ballHeight + 0.38786 * distanceToCup)) / (ballHeight + 0.38786 * distanceToCup); brug af albue og skulder
    v = (sqrt(15869125933.325) * distanceToCup * sqrt(tan(0.37) * distanceToCup + ballHeight)) / (1618200.5 * cos(0.37) * tan(0.37) * distanceToCup + 1618200.5 * cos(0.37) * ballHeight);// brug af skulder
        return v;
}




double TcpIPServer::getBaseAngle(double x, double y, double distanceToCup)
{
    double Angle = 1.5707963268 - atan(x / y);
    double a1 = 0;
    double a2 = 0;
    double b1 = 0;
    double b2 = 0;
    double A = 2.2849850567;
    double distanceToGripper = 144.65;
    double x3 = x;
    double y3 = y;
    while (true) {
        double B = A - Angle - 1.5707963268;
        double x1 = distanceToGripper * sin(B);
        double y1 = distanceToGripper * cos(B);
        a1 = (y3 - 0) / (x3 - 0);
        b1 = round(y3 - a1 * x3);
        //cout << "Angle: " << Angle << endl;
        //cout << "A: " << A << endl;
        //cout << "B: " << B << endl;
        //cout << "x1: " << x1 << endl;
        //cout << "y1: " << y1 << endl;
        a2 = a1;
        //cout << "a: " << a2 << endl;
        b2 = (y1 - a2 * x1) * -1;
        //cout << "b: " << b2 << endl;
        double dist = abs(a2 * x + b2 - y) / sqrt(pow(a2, 2) + 1);
        //std::cout << "dist: " << dist << std::endl;
        std::cerr << "dist: " << dist;
        if (dist < 0.3 && dist > -0.3) {
            std::cerr << "End angle: " << Angle;
            break;
        }
        else if (dist > 10) {
            Angle = Angle + 0.011;
            x3 = distanceToCup * cos(Angle);
            y3 = distanceToCup * sin(Angle);
            //cout << "y3: " << y3 << endl;
            //cout << "x3: " << x3 << endl;

        }
        else if (dist <= 10) {
            Angle = Angle + 0.0003;
            x3 = distanceToCup * cos(Angle);
            y3 = distanceToCup * sin(Angle);
            //cout << "y3: " << y3 << endl;
            //cout << "x3: " << x3 << endl;
        }
    }

    return Angle;
}

double TcpIPServer::getGribberToCup(double x1, double y1, double BaseAngle) {
    double GribberToCup = 0;
    double Angle = BaseAngle - 0.85660759688;
    double distanceToGripper = 144.65;
    double x2 = distanceToGripper * cos(Angle);
    double y2 = distanceToGripper * sin(Angle);

    return GribberToCup = abs(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));


}

void TcpIPServer::sendThrowingInformation(double x, double y) {
    double dist = abs(sqrt(pow(x, 2) + pow(y, 2)));
    double A = 0;
    double V = 0;


    A = getBaseAngle(x, y, dist);

    if (A > 1.5708) {
        A = A - 6.2832;
    }

    double GribberToCup = getGribberToCup(x, y, A);


    V = getAngularVelocity(838.369, GribberToCup);

    std::string Abuff = std::to_string(A);
    std::string Vbuff = std::to_string(V);

    std::string sending="( " + Abuff + ",-0.77079, 0, -1.1, 1.56722 ,-1.56722 )";

    sendString(sending);

    sendString("( 5 , 0.8 )");

    readFromClient();

    sending = "( " + Abuff+ " ,-1.83, 0, -1.10, 1.56722 ,-1.56722 )";

    sendString(sending);

    sendString("( 13, " + Vbuff + " )");

    readFromClient();
}

void TcpIPServer::readFromClient()
{
    int length = 100;
    char received [length];
    recv(clientSocket, received, sizeof(received), 0);

    if (received[0] != '\0') {
        std::cout << received << std::endl;
    }
}

bool TcpIPServer::isConnected()
{
    if (listening == 0) {
        return false;
    }
    return true;
}
