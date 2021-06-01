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
    AvoidBindError(server_socket);
    // avoid Bind error
    struct sockaddr_in server_addr;
    InitServerSocket(server_socket, server_addr);

    ////////////////////////////////////////////////////////////////////

    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    pid_t pid;
    char message[MAX_MSG];

    sigset_t set;
    BlockSIGCHLD(set);

    cout << "Accepting client connect ..." << endl;
    while (1) {
        client_socket =
            Accept(server_socket, reinterpret_cast<sockaddr *>(&client_addr),
                    &client_addr_len);
        PrintInfoClient(client_addr, client_addr_len);

        pid = fork();

        if (pid == 0) {
            close(server_socket);
            while (1) {
                memset(message, 0, MAX_MSG);
                if (Read(client_socket, message, sizeof(message)) == -1) {
                    close(client_socket);
                    exit(1);
                }
                ReceivedInfoClient(client_addr);
                WriteMsg(flall, treeFrom, treeTo, treeAirline, client_socket, message);
            }
        } else {
            SigAction(set);
            close(client_socket);
        }
    }
    close(server_socket);
    return 0;
}
