/*================================================================
 * Filename:AirManager.cpp
 * Author: KCN_yu
 * Createtime:Wed 06 Jan 2021 02:39:00 PM CST
 ================================================================*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <iomanip>
#include "AirManager.h"

using namespace std;

string Country_to_string(Country c){
    string res;
    switch(c){
        case 0: res = "England";break;
        case 1: res = "America";break;
        case 2: res = "Canada ";break;
        case 3: res = "Russia ";break;
        case 4: res = "France ";break;
        case 5: res = "Germany";break;
        case 6: res = "Japan  ";break;
        case 7: res = "China  ";break;
    }
    return res;
}
string Airline_to_string(Airline a){
    string res;
    switch(a){
        case 0: res = "AA";break;
        case 1: res = "MU";break;
        case 2: res = "BA";break;
        case 3: res = "FK";break;
        case 4: res = "QR";break;
        case 5: res = "SQ";break;
        case 6: res = "UA";break;
        case 7: res = "SU";break;
    }
    return res;
}
FlightInfo::FlightInfo(){
    int f_r = rand()%8;
    int f_t = rand()%8;
    int f_a = rand()%8;
    int f_h = rand()%23;
    int f_m = rand()%59;
    int f_d = rand()%23;
    while(f_t == f_r) f_t = rand()%8;

    from = (Country) f_r;
    to = (Country) f_t;
    airline = (Airline) f_a;
    string h,m;
    if(f_h < 10) h = '0'+to_string(f_h);
    else h = to_string(f_h);
    if(f_m < 10) m = '0'+to_string(f_m);
    else m = to_string(f_m);
    departure = h + ":" + m;
    duration = 2+f_d*0.9;
}
Country FlightInfo::GetFrom_country() const{
    return from;
}
Country FlightInfo::GetTo_country() const{
    return to;
}
Airline FlightInfo::GetAirline_Airline() const{
    return airline;
}
string FlightInfo::GetFrom() const{
    return Country_to_string(from);
}
string FlightInfo::GetTo() const{
    return Country_to_string(to);
}
string FlightInfo::GetAirline() const{
    return Airline_to_string(airline);
}
string FlightInfo::GetDeparture() const{
    return departure;
}
double FlightInfo::GetDuration() const{
    return duration;
}
ostream& operator<<(ostream& os, const FlightInfo& info){
    string tmp = to_string(info.GetDuration());
    tmp.resize(tmp.size()-5);
    os << "FROM: " << info.GetFrom() << " "; os.width(4);
    os << "TO: " << setw(4) << info.GetTo() << " ";os.width(4);
    os << "AIRLINE: " << setw(2) << info.GetAirline() << " ";os.width(4);
    os << "DEPARTURE: " << setw(4) << info.GetDeparture() << " ";
    os << "DURATION: " << setw(4) << tmp << "hours";
    os << endl;
    return os;
}
string FlightInfo::print() const{
    stringstream ss;
    streambuf* buffer = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    cout << *this;
    string res(ss.str());
    cout.rdbuf(buffer);
    return res;
}
FlightAll::FlightAll(){
    nKol = 0;
}
FlightInfo FlightAll::GetFlight(int i) const{
    return Flights[i];
}
Country FlightAll::GetFrom_country(int i) const{
    return Flights[i].GetFrom_country();
}
Country FlightAll::GetTo_country(int i) const{
    return Flights[i].GetTo_country();
}
Airline FlightAll::GetAirline_Airline(int i) const{
    return Flights[i].GetAirline_Airline();
}
int FlightAll::GetKol() const{
    return nKol;
}
string FlightAll::GetFrom(int i) const{
    return Flights[i].GetFrom();
}
string FlightAll::GetTo(int i) const{
    return Flights[i].GetTo();
}
string FlightAll::GetAirline(int i) const{
    return Flights[i].GetAirline();
}
string FlightAll::GetDeparture(int i) const{
    return Flights[i].GetDeparture();
}
double FlightAll::GetDuration(int i){
    return Flights[i].GetDuration();
}
bool FlightAll::Add(FlightInfo& info){
    if(nKol >= MAX_INFO) return false;
    Flights[nKol++] = info;
    return true;
}
ostream& operator<<(ostream& os, const FlightAll& flall){
    for(int i = 0; i < flall.nKol; i++){
        os.width(4); os << i << ".  ";
        os << flall.Flights[i] << endl;
    }
    return os;
}
string FlightAll::print() const{
    stringstream ss;
    streambuf* buffer = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    cout << *this;
    string res(ss.str());
    cout.rdbuf(buffer);
    return res;
}
template <typename Key>
Tree<Key>::Tree(){
    nDepth = -1;
    nNom_i = 0;
}
template <typename Key>
Tree<Key>::~Tree(){
    if(nDepth < 0) return;
    delete pKey;
    delete pLeft;
    delete pRight;
}
template <typename Key>
int Tree<Key>::GetDepth() const{
    return nDepth;
}
template <typename Key>
int* Tree<Key>::GetNom() const{
    return nNom;
}
template <typename Key>
Tree<Key>* Tree<Key>::GetLeft(){
    return pLeft;
}
template <typename Key>
Tree<Key>* Tree<Key>::GetRight(){
    return pRight;
}
template <typename Key>
bool Tree<Key>::Add(Key* pKey, Tree* pParent, int nNom){
    if(nDepth < 0){
        nDepth = 0;
        this->pKey = new Key(*pKey);
        this->nNom[nNom_i++] = nNom;
        this->pParent = pParent;
        this->pLeft = new Tree<Key>;
        this->pRight = new Tree<Key>;
        return true;
    }
    if(*this->pKey == *pKey){
        this->nNom[nNom_i++] = nNom;
        return true;
    }
    if(*this->pKey < *pKey) { if(!pLeft->Add(pKey,this,nNom)) return false; }
    else { if(!pRight->Add(pKey,this,nNom)) return false; }
    nDepth = max(pLeft->GetDepth(),pRight->GetDepth())+1;
    return true;
}
template <typename Key>
int* Tree<Key>::Search(Key* pKey){
    if(*this->pKey == *pKey) return this->nNom;
    return (*this->pKey < *pKey) ? pLeft->Search(pKey) : pRight->Search(pKey);
}
template <typename Key>
int Tree<Key>::Search_i(Key* pKey) const{
    if(nDepth < 0) return -1;
    if(*this->pKey == *pKey) return this->nNom_i;
    return (*this->pKey < *pKey) ? pLeft->Search_i(pKey) : pRight->Search_i(pKey);
}
/*
int main(int argc, char *argv[])
{
    srand(time(NULL));
    FlightAll flall;
    Tree<Country> treeFrom;
    Tree<Country> treeTo;
    Tree<Airline> treeAirline;
    Tree<double> treeDuration;
    int nFl = 100;
    for(int i = 0; i < nFl; i++){
        FlightInfo f;
        flall.Add(f);

        Country c_from = flall.GetFrom_country(i);
        Country c_to = flall.GetTo_country(i);
        Airline a = flall.GetAirline_Airline(i);
        treeFrom.Add(&c_from,NULL,flall.GetKol()-1);
        treeTo.Add(&c_to,NULL,flall.GetKol()-1);
        treeAirline.Add(&a,NULL,flall.GetKol()-1);
    }
    cout << flall;

    Country c = Russia;
    Airline a = UA;

    int *res;
    int res_n;

    if((res_n = treeFrom.Search_i(&c)) != -1) res = treeFrom.Search(&c);
    for(int i = 0; i < res_n; i++) cout << flall.GetFlight(res[i]) << endl;


    if((res_n = treeTo.Search_i(&c)) != -1) res = treeTo.Search(&c);
    for(int i = 0; i < res_n; i++) cout << flall.GetFlight(res[i]) << endl;

    if((res_n = treeAirline.Search_i(&a)) != -1) res = treeAirline.Search(&a);
    for(int i = 0; i < res_n; i++) cout << flall.GetFlight(res[i]) << endl;

    return 0;
}*/
