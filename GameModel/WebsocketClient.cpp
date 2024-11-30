#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<cstring>
#include<graphics.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main()
{
    //一、初始化WSA  
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0){
        return 0;
    }
    while (true) {
        //TCP协议族，TCP连接，IPv4地址
        SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sclient == INVALID_SOCKET){
            MessageBox(NULL, _T("socket创建失败!"), _T("错误"), MB_OK);
            exit(-1);
        }
        sockaddr_in serAddr;
        serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
        serAddr.sin_family = AF_INET;
        serAddr.sin_port = htons(8888);

        if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
        {  //连接失败 
            MessageBox(NULL, _T("连接失败!"), _T("错误"), MB_OK);
            closesocket(sclient);
            exit(-1);
        }

        string data;
        cin >> data;
        // const char * sendData;
        const char* sendData = "hello tcp server, I am client!\n";
        sendData = data.c_str(); 
        send(sclient, sendData, strlen(sendData), 0);

        char recData[255];
        int ret = recv(sclient, recData, 255, 0);
        if (ret > 0) {
            printf("\naccept info from server, content: \n\t\t\t\t\t");

            recData[ret] = 0x00;
            printf(recData);
        }
        closesocket(sclient);
    }
    WSACleanup();
    return 0;
}
