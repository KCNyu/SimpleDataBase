/*================================================================
 * Filename:AirManager.h
 * Author: KCN_yu
 * Createtime:Tue 05 Jan 2021 01:35:06 AM CST
 ================================================================*/
#ifndef AIRMANAGER_H
#define AIRMANAGER_H

#include <arpa/inet.h>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <netinet/in.h>
#include <signal.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

using namespace std;

#define MAX_INFO 32767
#define SRV_PORT 9999
#define LISTEN_MAX 128
#define MAX_MSG 65536

enum Country {
    England,
    America,
    Canada,
    Russia,
    France,
    Germany,
    Japan,
    China
};
enum Airline { AA, MU, BA, FK, QR, SQ, UA, SU };
string Country_to_string(Country);
string Airline_to_string(Airline);
Country string_to_Country(char *);
Airline string_to_Airline(char *);

/////////////////////////////////////////////////////////////////////////

class FlightInfo {
    private:
        Country from;
        Country to;
        Airline airline;
        string departure;
        double duration;

    public:
        FlightInfo();
        // FlightInfo(const FlightInfo&);
        Country GetFrom_country() const;
        Country GetTo_country() const;
        Airline GetAirline_Airline() const;
        string GetFrom() const;
        string GetTo() const;
        string GetAirline() const;
        string GetDeparture() const;
        double GetDuration() const;
        string print() const;
        friend ostream &operator<<(ostream &, const FlightInfo &);
        // friend bool operator==(const Fio& f1, const Fio& f2);
        // friend bool operator<(const Fio& f1, const Fio& f2);
};

/////////////////////////////////////////////////////////////////////////

class FlightAll {
    private:
        int nKol;
        FlightInfo Flights[MAX_INFO];

    public:
        FlightAll();
        FlightInfo GetFlight(int) const;
        Country GetFrom_country(int) const;
        Country GetTo_country(int) const;
        Airline GetAirline_Airline(int) const;
        int GetKol() const;
        string GetFrom(int) const;
        string GetTo(int) const;
        string GetAirline(int) const;
        string GetDeparture(int) const;
        double GetDuration(int);
        bool Add(FlightInfo &info);
        string print() const;
        friend ostream &operator<<(ostream &os, const FlightAll &flall);
};

/////////////////////////////////////////////////////////////////////////

template <typename Key> class Tree {
    private:
        int nDepth;
        Key *pKey;
        int nNom[MAX_INFO];
        int nNom_i;
        Tree *pParent;
        Tree *pLeft;
        Tree *pRight;

    public:
        Tree();
        ~Tree();
        int GetDepth() const;
        int *GetNom() const;
        Tree *GetLeft();
        Tree *GetRight();
        bool Add(Key *pkey, Tree *pParent, int nNom);
        int *Search(Key *pKey);
        int Search_i(Key *pKey) const;
        string Search_print(Key *pKey, const FlightAll &flall);
};

template <typename Key> Tree<Key>::Tree() {
    nDepth = -1;
    nNom_i = 0;
}
template <typename Key> Tree<Key>::~Tree() {
    if (nDepth < 0)
        return;
    delete pKey;
    delete pLeft;
    delete pRight;
}
template <typename Key> int Tree<Key>::GetDepth() const { return nDepth; }
template <typename Key> int *Tree<Key>::GetNom() const { return nNom; }
template <typename Key> Tree<Key> *Tree<Key>::GetLeft() { return pLeft; }
template <typename Key> Tree<Key> *Tree<Key>::GetRight() { return pRight; }
template <typename Key>
bool Tree<Key>::Add(Key *pKey, Tree *pParent, int nNom) {
    if (nDepth < 0) {
        nDepth = 0;
        this->pKey = new Key(*pKey);
        this->nNom[nNom_i++] = nNom;
        this->pParent = pParent;
        this->pLeft = new Tree<Key>;
        this->pRight = new Tree<Key>;
        return true;
    }
    if (*this->pKey == *pKey) {
        this->nNom[nNom_i++] = nNom;
        return true;
    }
    if (*this->pKey < *pKey) {
        if (!pLeft->Add(pKey, this, nNom))
            return false;
    } else {
        if (!pRight->Add(pKey, this, nNom))
            return false;
    }
    nDepth = max(pLeft->GetDepth(), pRight->GetDepth()) + 1;
    return true;
}
template <typename Key> int *Tree<Key>::Search(Key *pKey) {
    if (*this->pKey == *pKey)
        return this->nNom;
    return (*this->pKey < *pKey) ? pLeft->Search(pKey) : pRight->Search(pKey);
}
template <typename Key> int Tree<Key>::Search_i(Key *pKey) const {
    if (nDepth < 0)
        return -1;
    if (*this->pKey == *pKey)
        return this->nNom_i;
    return (*this->pKey < *pKey) ? pLeft->Search_i(pKey) : pRight->Search_i(pKey);
}
template <typename Key>
string Tree<Key>::Search_print(Key *pKey, const FlightAll &flall) {
    stringstream ss;
    streambuf *buffer = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    int *res;
    int res_n;
    if ((res_n = Search_i(pKey)) != -1)
        res = Search(pKey);
    for (int i = 0; i < res_n; i++)
        cout << flall.GetFlight(res[i]) << endl;
    string s(ss.str());
    cout.rdbuf(buffer);
    return s;
}

/////////////////////////////////////////////////////////////////////////

void BlockSIGCHLD(sigset_t &set);
void InitFlightTreeAll(FlightAll &flall, Tree<Country> &treeFrom,
        Tree<Country> &treeTo, Tree<Airline> &treeAirline,
        const int nFl);
void AvoidBindError(int &server_socket);
void InitServerSocket(int &server_socket, struct sockaddr_in &server_addr);
void PrintInfoClient(const sockaddr_in &clit_addr,
        const socklen_t &clit_addr_len);
void ReceivedInfoClient(const sockaddr_in &clit_addr);
void WriteMsg(FlightAll &flall, Tree<Country> &treeFrom, Tree<Country> &treeTo,
        Tree<Airline> &treeAirline, int fd, char *message);
void catch_child(int signum);
void SigAction(sigset_t &set);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
ssize_t Read(int fd, void *buf, size_t count);

#endif /* AIRMANAGER_H */
