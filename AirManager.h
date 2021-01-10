/*================================================================
 * Filename:AirManager.h
 * Author: KCN_yu
 * Createtime:Tue 05 Jan 2021 01:35:06 AM CST
 ================================================================*/
#ifndef AIRMANAGER_H
#define AIRMANAGER_H

#include <iostream>
using namespace std;

#define MAX_INFO 32767

enum Country{ England, America, Canada, Russia, France, Germany, Japan, China};
enum Airline{ AA, MU, BA, FK, QR, SQ, UA, SU };
string Country_to_string(Country);
string Airline_to_string(Airline);
Country string_to_Country(char*);
Airline string_to_Airline(char*);

class FlightInfo {
    private:
        Country from;
        Country to;
        Airline airline;
        string departure;
        double duration;
    public:
        FlightInfo();
        //FlightInfo(const FlightInfo&);
        Country GetFrom_country()const;
        Country GetTo_country()const;
        Airline GetAirline_Airline()const;
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

class FlightAll{
    private:
        int nKol;
        FlightInfo Flights[MAX_INFO];
    public:
        FlightAll();
        FlightInfo GetFlight(int)const;
        Country GetFrom_country(int)const;
        Country GetTo_country(int)const;
        Airline GetAirline_Airline(int)const;
        int GetKol()const;
        string GetFrom(int)const;
        string GetTo(int)const;
        string GetAirline(int)const;
        string GetDeparture(int)const;
        double GetDuration(int);
        bool Add(FlightInfo& info);
        string print()const;
        friend ostream& operator<<(ostream& os, const FlightAll& flall);

};
template <typename Key>
class Tree{
    private:
        int nDepth;
        Key* pKey;
        int nNom[MAX_INFO];
        int nNom_i;
        Tree* pParent;
        Tree* pLeft;
        Tree* pRight;
    public:
        Tree();
        ~Tree();
        int GetDepth()const;
        int* GetNom()const;
        Tree* GetLeft();
        Tree* GetRight();
        bool Add(Key* pkey, Tree* pParent, int nNom);
        int* Search(Key* pKey);
        int Search_i(Key* pKey)const;
        string Search_print(Key* pKey,const FlightAll& flall);
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
