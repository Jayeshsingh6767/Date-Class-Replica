#ifndef __TMDATE__H
#define __TMDATE__H
#include<iostream>
using namespace std;
class TMDate
{
private:
int dayOfMonth;
int month;
int year;
int dayNumber;
void toDayNumber();
int isLeapYear(int);
void fromDayNumber();
void isValidDate(const char *date,int *isValid,int *d,int *m,int *y);
public:
TMDate();
TMDate(const char *dateString);

// operators
TMDate & operator=(const TMDate &other);
TMDate & operator=(const char *dateString);
void operator+=(int days);
void operator-=(int days);

// getter
int getDayOfMonth();
int getMonth();
int getYear();
};
ostream & operator<<(ostream &o,TMDate &date);
#endif