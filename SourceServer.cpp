
#include <iostream>

#include <vector>

//used for the sort
#include <algorithm>


/*
Used files for using sockets
*/

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using std::string;
using std::vector;
using std::sort;
using std::cout;
using std::endl;

/*
This is the SERVER side script which means this happens wants the client has successfully been connecte
*/

/* 
Here would be the example of the struct for the leaderboard we would have
the score they gotten and the player name who got it.
*/

/*
IMPORTANT:
run the program and make sure it says: Server listening on port 8080...
for running what I do is connect open a browser with and copy and paste use this:
127.0.0.1:8080 
^ this is the IP and port I have set in the code couldn't figure out how to connect any IP
now check output and should have connected the client and printed a leaderboard
*/

struct leaderboard {
    string playerName;
    int score;
};

/*
Making a vector for the leaderboard.
*/
vector<leaderboard> curLeaderboard;

/*
 This function will add the player data to the leaderboard vector
 it will add the player name which is a string and an int for there score.
*/
void addToLeaderboard(const string& playerName, int score) {
    curLeaderboard.push_back({ playerName, score });

    sort(curLeaderboard.begin(), curLeaderboard.end(), [](const leaderboard& a, const leaderboard& b) {
        return a.score > b.score;
        }
    );
}

/*
This function will display the current leaderboard to the output
*/
void displayLeaderboard() {
    cout << "Leaderboard:\n";
    for (const auto& entry : curLeaderboard) {
        cout << entry.playerName << ": " << entry.score << " points\n";
    }
}

/*
Server side main script
*/

int main() {
    
    /*
    Making the data
    */

    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    /*
    This will create the server side socket for the client
    */
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /*
    This code will define the server address
    setting the port to 8080 or any IP trying to connect
    */

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    /*
    This will now bind the socket we have created to the address
    */
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding to port: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    /*
    This will now wait and listen for communication from the client to come in
    */
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error listening on socket: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server listening on port 8080...\n";

    /*
    This will now accept client communication and cose the server side socket
    */
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error accepting connection: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

   // cout << "Client connected\n";

    /*
    This will connect the data from whatever the client has sent to the server it wants to store
    so for here this will store the score the current client has gotten and make the name "player"
    */
    int clientScore = 0;
    char name[100] = {0};
    string playerName = "";
    int bytesReceivedInt = recv(clientSocket, reinterpret_cast<char*>(&clientScore), sizeof(clientScore), 0);
    /*int bytesReceivedName = recv(clientSocket, name, sizeof(playerName) - 1, 0);
   
    if (bytesReceivedName == 0) {
        closesocket(clientSocket);
        return 0;
    }
    name[bytesReceivedName] = '\0';
    playerName = name;*/

    //cout << "Current player name is " << playerName << endl;
    cout << "Received score from client: " << clientScore << endl;
    addToLeaderboard("Test Player", clientScore);
    displayLeaderboard();

    /*
    Closing both sockets
    */
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
