/*================================================================
 * Filename:server.cpp
 * Author: KCN_yu
 * Createtime:Wed 06 Jan 2021 12:20:22 PM CST
 ================================================================*/

#include "AirManager.h"

using namespace std;

int main(int argc, char *argv[]) {

    srand(time(NULL));
    FlightAll flall;
    Tree<Country> treeFrom;
    Tree<Country> treeTo;
    Tree<Airline> treeAirline;
    int nFl = 100;
    InitFlightTreeAll(flall, treeFrom, treeTo, treeAirline, nFl);

    ////////////////////////////////////////////////////////////////////

    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "socket() error!" << endl;
        exit(-1);
    }
    struct sockaddr_in server_addr;
    InitServerSocket(server_socket, server_addr);
    AvoidBindError(server_socket);
    // avoid Bind error

    ////////////////////////////////////////////////////////////////////

    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int nready;
    struct pollfd client[OPEN_MAX];

    client[0].fd = server_socket;
    client[0].events = POLLIN;

    for(int i = 1; i < OPEN_MAX; i++){
        client[i].fd = -1;
    }

    int maxi = 0, tmp_index;
    char message[MAX_MSG];

    cout << "Accepting client connect ..." << endl;
    while (1) {
        nready = poll(client, maxi+1, -1);
        if(nready < 0){
            cerr << "select error" << endl;
            exit(1);
        }
        if(client[0].revents & POLLIN){
            client_socket =
                Accept(server_socket, reinterpret_cast<sockaddr *>(&client_addr),
                        &client_addr_len);
            PrintInfoClient(client_addr, client_addr_len);
            for(int i = 1; i < OPEN_MAX; i++){
                if(client[i].fd < 0){
                    client[i].fd = client_socket;
                    client[i].events = POLLIN;
                    tmp_index = i;
                    break;
                }
            }
            if(maxi < tmp_index){
                maxi = tmp_index;
            }
            if(nready == 1){
                continue;
            }
        }
        for(int i = 1; i <= maxi; i++){
            bzero(message,sizeof(message));
            int sockfd, n;
            if((sockfd = client[i].fd) < 0){
                continue;
            }
            if(client[i].revents & POLLIN){
                if ((n = read(sockfd, message, sizeof(message))) == 0) {
                    printf("client[%d] closed connection\n", i);
                    close(sockfd);
                    client[i].fd = -1;
                }
                else if(n < 0){
                    if(errno == ECONNRESET){
                        printf("client[%d] aborted connection\n", i);
                        close(sockfd);
                        client[i].fd = -1;
                    }
                }
                else if(n > 0){
                    write(STDOUT_FILENO, message, n);
                    WriteMsg(flall, treeFrom, treeTo, treeAirline, sockfd, message);
                }
                if(--nready == 0){
                    break;
                }
            }
        }
    }
    close(server_socket);
    return 0;
}
