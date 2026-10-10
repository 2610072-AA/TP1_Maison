
#include "entrypoint.h"
#include <winsock2.h>
#include <windows.h>

#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib");
#define DEFAULT_PORT "7099"
#define DEFAULT_BUFLEN 512

WSADATA wsaData;
SOCKET ConnectSocket = INVALID_SOCKET;



// Initialize Winsock


void affichage(){
    system("cls");
    std::cout << "Available requests, and/or end the process" << std::endl;
    std::cout <<"1) Connect to domains example.com or kode.tech" << std::endl;
    std::cout << "2) Communicate to server (GET)" << std::endl;
    std::cout << "3) Communicate to server (HEAD)" << std::endl;
    std::cout << "4) Communicate to server (PUT)" << std::endl;
    std::cout << "5) Communicate to server (DELETE)" << std::endl;
    std::cout << "6) Quit" << std::endl;
}

void affichageChoix(){
    system("cls");
    std::cout << "Available requests, and/or go back to main menu" << std::endl;
    std::cout <<"1) Connect to example.com " << std::endl;
    std::cout <<"2) Connect to kode.tech" << std::endl;
    std::cout <<"3) Go back" << std::endl;
}

void afficheChoixGetHead(){
    system("cls");
    std::cout << "1) Make a GET request" << std::endl;
    std::cout << "2) Make a HEAD request" << std::endl;
    std::cout << "3) Go back" << std::endl;
}

int connectGetDom(std::string domain){
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    int iResult = getaddrinfo(domain.c_str(), "80", &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        return 1;
    }
    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        return 1;
    }

    // Connect to server.
    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        return 1;
    }

    int recvbuflen = DEFAULT_BUFLEN;

    std::string request =
    "GET / HTTP/1.1\r\n"
    "Host: " + domain + "\r\n"
    "Connection: close\r\n"
    "\r\n";

    const char* sendbuf = request.c_str();
    char recvbuf[DEFAULT_BUFLEN];


    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        return 1;
    }

    // Receive data until the server closes the connection
    do
    {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
            printf("%.*s", iResult, recvbuf);
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed: %d\n", WSAGetLastError());
    } while (iResult > 0);
    // shutdown the send half of the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        return 1;
    }
    // cleanup
    closesocket(ConnectSocket);
    return 0;

}

bool connectHeadDom(std::string domain){

}
bool connectD(){
    std::string domains[2] = {"example.com","kode.tech"};
    bool returning = false;
    while ( returning == false)
        {
            int choiceReq;
            int choix;
            affichageChoix();
            std::cin >> choix;
            switch (choix)
            {
                case 1:
                    {
                        afficheChoixGetHead();
                        std::cin >> choiceReq;
                        if (choiceReq == 1){
                            connectGetDom(domains[0]);
                            system("pause");
                        }
                        else if (choiceReq == 2){
                            connectHeadDom(domains[0]);
                            system("pause");
                        }
                        break;
                    }
                case 2:
                {

                    afficheChoixGetHead();
                    std::cin >> choiceReq;
                    if (choiceReq == 1){
                        connectGetDom(domains[1]);
                        system("pause");
                        
                    }
                    else if (choiceReq == 2){
                        connectHeadDom(domains[1]);
                        system("pause");
                    }
                    break;
                }
                case 3:
                    {
                        returning = true;
                        break;
                    }
            }
        }
    return true;
}

int get(){
    return 0;
}

int head(){

}

int put(){

}

int deletec(){

}

int raylib_start(void)
{
    bool endProgram = false;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;

    }

    while(!endProgram){
        
        affichage();
        int choice;
        std::cin >> choice;
        switch(choice){
            case 1:
                connectD();
                break;
            case 2:
                get();
                break;
            case 3:
                head();
                break;
            case 4:
                put();
                break;
            case 5:
                deletec();
                break;
            case 6:
                endProgram = true;
                break;
        }
    }
   
    WSACleanup();

    return 0;
}


 
    // struct addrinfo *result = NULL,
    //                 *ptr = NULL,
    //                 hints;

    // ZeroMemory(&hints, sizeof(hints));
    // hints.ai_family = AF_UNSPEC;
    // hints.ai_socktype = SOCK_STREAM;
    // hints.ai_protocol = IPPROTO_TCP;

    // // Resolve the server address and port
    // iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    // if (iResult != 0)
    // {
    //     printf("getaddrinfo failed: %d\n", iResult);
    //     WSACleanup();
    //     return 1;

       
    // }

    //  // Attempt to connect to the first address returned by
    // // the call to getaddrinfo
    // ptr = result;

    // // Create a SOCKET for connecting to server
    // ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    // if (ConnectSocket == INVALID_SOCKET)
    // {
    //     printf("Error at socket(): %ld\n", WSAGetLastError());
    //     freeaddrinfo(result);
    //     WSACleanup();
    //     return 1;
    // }

    // // Connect to server.
    // iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    // if (iResult == SOCKET_ERROR)
    // {
    //     closesocket(ConnectSocket);
    //     ConnectSocket = INVALID_SOCKET;
    // }

    // // Should really try the next address returned by getaddrinfo
    // // if the connect call failed
    // // But for this simple example we just free the resources
    // // returned by getaddrinfo and print an error message

    // freeaddrinfo(result);

    // if (ConnectSocket == INVALID_SOCKET)
    // {
    //     printf("Unable to connect to server!\n");
    //     WSACleanup();
    //     return 1;
    // }

    // int recvbuflen = DEFAULT_BUFLEN;

    // const char *sendbuf = "this is a test";
    // char recvbuf[DEFAULT_BUFLEN];

    // int iResult;

    // // Send an initial buffer
    // iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    // if (iResult == SOCKET_ERROR)
    // {
    //     printf("send failed: %d\n", WSAGetLastError());
    //     closesocket(ConnectSocket);
    //     WSACleanup();
    //     return 1;
    // }

    // printf("Bytes Sent: %ld\n", iResult);

    // // shutdown the connection for sending since no more data will be sent
    // // the client can still use the ConnectSocket for receiving data
    // iResult = shutdown(ConnectSocket, SD_SEND);
    // if (iResult == SOCKET_ERROR)
    // {
    //     printf("shutdown failed: %d\n", WSAGetLastError());
    //     closesocket(ConnectSocket);
    //     WSACleanup();
    //     return 1;
    // }

    // // Receive data until the server closes the connection
    // do
    // {
    //     iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    //     if (iResult > 0)
    //         printf("Bytes received: %d\n", iResult);
    //     else if (iResult == 0)
    //         printf("Connection closed\n");
    //     else
    //         printf("recv failed: %d\n", WSAGetLastError());
    // } while (iResult > 0);
    // // shutdown the send half of the connection since no more data will be sent
    // iResult = shutdown(ConnectSocket, SD_SEND);
    // if (iResult == SOCKET_ERROR)
    // {
    //     printf("shutdown failed: %d\n", WSAGetLastError());
    //     closesocket(ConnectSocket);
    //     WSACleanup();
    //     return 1;
    // }
    // // cleanup
    // closesocket(ConnectSocket);