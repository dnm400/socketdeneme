#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> //for inet_pton
#include <tchar.h> //for _T
#include <vector> //more clients


using namespace std;

int main(){

    //Initialize Winsock
    WSADATA wsaData;

    int resdll = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(resdll != 0){
        cout << "WSAStartup failed" << endl;
        return 0;
    }

    //Create a socket
    SOCKET originalsocket = INVALID_SOCKET;
    originalsocket = socket(AF_INET, SOCK_STREAM, 0);
    if(originalsocket == INVALID_SOCKET){
        cout << "Creating socket failed" << endl;
        WSACleanup();
        return;
    }
    else {
        cout << "Creating socket OK" << endl;
    }

    //Bind socket, address
    int port = 12345;
    sockaddr_in addvar;
    addvar.sin_family = AF_INET;
    addvar.sin_port = htons(port);
    InetPton(AF_INET, _T("127.0.0.1"), &addvar.sin_addr.s_addr);
    if(bind(originalsocket, (SOCKADDR*)&addvar, sizeof(addvar)) == SOCKET_ERROR){
        cout << "Bind failed" << endl;
        closesocket(originalsocket);
        WSACleanup();
        return 0;
    }
    else{
        cout << "Bind OK" << endl;
    }

    //listen 
    if(listen(originalsocket, 2) == SOCKET_ERROR){ //2 -> max # of connection allowed
        cout << "Listen failed" << endl;
        closesocket(originalsocket);
        WSACleanup();
        return 0;

    }
    else{
        cout << "Listen OK" << endl;
    }

   // while(1){
    //accept
    SOCKET newsocket = accept(originalsocket, NULL, NULL);
    if(newsocket == INVALID_SOCKET){
        cout << "New socket and accept failed" << endl;
        WSACleanup();
        return -1;
    }
   // vector<SOCKET> clients;
   // clients.push_back(newsocket);
    // }

    //receive
    char receivebuf[4096];
    int bytelength = recv(newsocket, receivebuf, 4096, 0); //AGAIN
    if(bytelength < 0){
        cout << "Disconnected" << endl;
    }
    else{
        string chat = string(receivebuf, bytelength);
        cout << chat << endl;
    }

    system("pause");
    closesocket(originalsocket);
    WSACleanup();
    return 0;
}
