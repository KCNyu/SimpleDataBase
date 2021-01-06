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
        case 2: res = "Canada";break;
        case 3: res = "Russia";break;
        case 4: res = "France";break;
        case 5: res = "Germany";break;
        case 6: res = "Japan";break;
        case 7: res = "China";break;
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
    srand(time(NULL));

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
    departure = to_string(f_h)+":"+to_string(f_m);
    duration = 2+f_d*0.9;
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
string FlightInfo::print() const{
    string tmp = to_string(GetDuration());
    tmp.resize(tmp.size()-5);

    string res = " '" + GetFrom()+" '" +
        " '" + GetTo() + "' " +
        " '" + GetAirline() + "' " +
        " '" + GetDeparture() + "' " +
        " '" + tmp + "hours' ";
    return res;
}
ostream& operator<<(ostream& os, const FlightInfo& info){
    os << info.print();
    return os;
}
/*
int main(int argc, char *argv[])
{
    FlightInfo f1;
    cout << f1 << endl;
    cout << f1.print() << endl;
    return 0;
}
*/
