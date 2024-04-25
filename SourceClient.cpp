#include <iostream>

/*
Used files for using sockets
*/

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using std::cout;
using std::cerr;
using std::endl;
using std::string;

/*
Client side main script
*/

int main() {

    /*
    Making the data
    */

    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    /*
    This will create the client side socket for to be sent to the server.
    */
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /*
    This code will define the client address
    Setting port to 8080 making it the same with the server
    Or having the same IP connect client to server
    */

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    /*
    This will now connect the socket we have created to the server address
    */

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        cerr << "Error connecting to server: " << WSAGetLastError() << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    /*
    Now we will send the data we got from the client side to the server
    E.X. we have a score of 100 we will send the server to store on the leaderboard
    */

    int score = 100;
    string playerName = "Test Player";

    int bytesSentInt = send(clientSocket, reinterpret_cast<const char*>(&score), sizeof(score), 0);
    //int bytesSentName = send(clientSocket, playerName.c_str(), playerName.length(), 0);

    cout << "Score on client is " << score << "!" << endl;
    cout << "Score sent to server" << score << "!" << endl;

    /*
    Close the client socket
    */

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
