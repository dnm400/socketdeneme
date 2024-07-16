#include <iostream>
#include <winsock2.h>


#define port "27015"

using namespace std;

int main(){

    //Initialize Winsock
    WSADATA wsaData;

    int resdll = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(resdll != 0){
        cout << "WSAStartup failed" << endl;
        return 1;
    }

    //Create a socket
    SOCKET originalsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(originalsocket == INVALID_SOCKET){
        cout << "Creating socket failed" << endl;
        return 1;
    }

}
