/*================================================================
 * Filename:server.cpp
 * Author: KCN_yu
 * Createtime:Wed 06 Jan 2021 12:20:22 PM CST
 ================================================================*/

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include "AirManager.h"

#define MAX_MSG 1024

using namespace std;

int main(int argc, char* argv[]){

    FlightInfo f;

////////////////////////////////////////////////////////////////////

    if(argc != 2){
        cerr << "use this main with port" << endl;
        exit(1);
    }

    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        cerr << "socket() error!" << endl;
        exit(-1);
    }

    struct sockaddr_in server_addr;

    int on = 1;
    setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    //avoid Bind error
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof server_addr)){
        cerr << "bind() error!" << endl;
        exit(-1);
    }

    if(listen(server_socket, 5)){
        cerr << "listen() error!" << endl;
        exit(-1);
    }

////////////////////////////////////////////////////////////////////

    int client_socket;
    while(1){
        if((client_socket = accept(server_socket, NULL, NULL)) < 0){
            cerr << "accept() error!" << endl;
            exit(1);
        }

        cout << "A new client is connected, and his socket is " << client_socket << endl;

        char message[MAX_MSG];

        while(1){
            memset(message,0,MAX_MSG);
            int read_len;
            if((read_len = read(client_socket, message, sizeof(message))) < 0){
                cerr << "read() error" << endl;
                exit(-1);
            }
            if(!read_len){
                cout << "Client launched chat" << endl;
                break;
            }
            cout << "The client says: " << message << endl;
            /*
            cout << "I want to say to the client: ";
            memset(message,0,MAX_MSG);
            fgets(message,MAX_MSG,stdin);
            */
            if(strcmp(message,"print\n") == 0){
                strcpy(message,f.print().c_str());
            }
            else{
                strcpy(message,"recevied!\n");
            }

            int w_len = write(client_socket, message, strlen(message));

            if(w_len != strlen(message)){
                cout << "write() error!" << endl;
                exit(-1);
            }
        }
    }
    close(client_socket);
    close(server_socket);
    return 0;
}
