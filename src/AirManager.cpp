/*================================================================
 * Filename:AirManager.cpp
 * Author: KCN_yu
 * Createtime:Wed 06 Jan 2021 02:39:00 PM CST
 ================================================================*/

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
Country string_to_Country(char* s){
    Country c;
    if(strcmp(s,"England\n") == 0) c = England;
    else if(strcmp(s,"America\n") == 0) c = America;
    else if(strcmp(s,"Canada\n") == 0) c = Canada;
    else if(strcmp(s,"Russia\n") == 0) c = Russia;
    else if(strcmp(s,"France\n") == 0) c = France;
    else if(strcmp(s,"Germany\n") == 0) c = Germany;
    else if(strcmp(s,"Japan\n") == 0) c = Japan;
    else if(strcmp(s,"China\n") == 0) c = China;
    else throw "ERROR";
    return c;
}
Airline string_to_Airline(char* s){
    Airline a;
    if(strcmp(s,"AA\n") == 0) a = AA;
    else if(strcmp(s,"MU\n") == 0) a = MU;
    else if(strcmp(s,"BA\n") == 0) a = BA;
    else if(strcmp(s,"FK\n") == 0) a = FK;
    else if(strcmp(s,"QR\n") == 0) a = QR;
    else if(strcmp(s,"SQ\n") == 0) a = SQ;
    else if(strcmp(s,"UA\n") == 0) a = UA;
    else if(strcmp(s,"SU\n") == 0) a = SU;
    else throw "ERROR";
    return a;
}

/////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////

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
