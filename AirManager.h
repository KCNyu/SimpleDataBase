/*================================================================
 * Filename:AirManager.h
 * Author: KCN_yu
 * Createtime:Tue 05 Jan 2021 01:35:06 AM CST
 ================================================================*/
#ifndef AIRMANAGER_H
#define AIRMANAGER_H

#include <iostream>
#include <list>
using namespace std;

enum Country{ EngLand, America, Canada, Russia, France, Germany, Japan, China};
enum Airline{ AA, MU, BA, FK, QR, SQ, UA, SU };
string Country_to_string(Country);
string Airline_to_string(Airline);

class FlightInfo {
    private:
        Country from;
        Country to;
        Airline airline;
        string departure;
        double duration;
    public:
        FlightInfo();
        FlightInfo(const FlightInfo&);
        string GetFrom()const;
        string GetTo()const;
        string GetAirline()const;
        string GetDeparture()const;
        double GetDuration()const;
        string print()const;
        friend ostream& operator<<(ostream&,const FlightInfo&);
        //friend bool operator==(const Fio& f1, const Fio& f2);
        //friend bool operator<(const Fio& f1, const Fio& f2);
};

const int NALL = 32767;

class FlightAll{
    private:
        int nKol;
        list<FlightInfo> Flights;
    public:

};
#endif /* AIRMANAGER_H */
/*
   typedef enum { ADD, SELECT, DELETE, UPDATE, FIND } CommandType;
   typedef enum { FROM, TO, TIME, DURATION, AIRLINE } Field;
   typedef enum { GT, LT, EQUAL, IN } Relation;
   struct Cond { // Одно условие вида поле/отношение/константа
   Field field;
   Relation relation;
   union {
   int i;
   string s;
   double d;
   } value; // Значение константы
   };
   struct Command {
   CommandType cmd;
   SearchConditions conditions;
   };
   Command parse(const string &query);
   */
