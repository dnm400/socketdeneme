#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> //for inet_pton
#include <tchar.h> //for _T

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void sendmsg(SOCKET clientsocket){
    char sendbuf[4096];
    while(true){
    memset(sendbuf, 0, sizeof(sendbuf));

    cin.getline(sendbuf, 4096);
    int sendlength = send(clientsocket, sendbuf, 4096, 0);
    if(sendlength == SOCKET_ERROR){
        cout << "Send failed" << endl;
        closesocket(clientsocket);
        WSACleanup();
        break;
    }
    else{
        cout << "Send OK " << endl;
    }
    }
}

int main(){

    //Initialize Winsock
    WSADATA wsaData;

    int resdll = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(resdll != 0){
        cout << "WSAStartup failed" << endl;
        return 0;
    }

    //Create a socket
    SOCKET clientsocket = INVALID_SOCKET;
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientsocket == INVALID_SOCKET){
        cout << "Creating socket failed" << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "Creating socket OK" << endl;
    }

    //Connect
    int port = 12345;
    sockaddr_in clientadd;
    clientadd.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientadd.sin_addr.s_addr);
    clientadd.sin_port = htons(port);
    if(connect(clientsocket, (SOCKADDR*)&clientadd, sizeof(clientadd)) == SOCKET_ERROR){
        cout << "Connect failed" << endl;
        closesocket(clientsocket);
        WSACleanup();
        return 0;
    }
    else{
        cout << "Connect OK" << endl;
    }



    char recbuf[4096];
    while(true){
    memset(recbuf, 0, sizeof(recbuf));

    //receive
    int reclength = recv(clientsocket, recbuf, 4096, 0);
    if(reclength < 0){
        cout << "Receive failed" << endl;
        closesocket(clientsocket);
        WSACleanup();
        return 0;
        break;
    }
    else{
        cout << "Received: " << recbuf << endl;
    }
    }


    system("pause");    
    closesocket(clientsocket);
    WSACleanup();
    return 0;
}