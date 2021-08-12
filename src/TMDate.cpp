#include<TMDate.h>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
dayOfMonth=now->tm_mday;
month=now->tm_mon+1;
year=now->tm_year+1900;
this->toDayNumber();
}
TMDate::TMDate(const char *dateString)
{
int valid,d,m,y;
isValidDate(dateString,&valid,&d,&m,&y);
if(valid==1)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}
}

TMDate & TMDate::operator=(const TMDate &other)
{
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
this->dayNumber=other.dayNumber;
}
TMDate & TMDate::operator=(const char *dateString)
{
int valid,d,m,y;
isValidDate(dateString,&valid,&d,&m,&y);
if(valid==1)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}
}
void TMDate::operator+=(int days)
{
if(this->dayNumber==0)return;
this->dayNumber=this->dayNumber+days;
this->fromDayNumber();
}
void TMDate::operator-=(int days)
{
if(this->dayNumber==0)return;
this->dayNumber=this->dayNumber-days;
this->fromDayNumber();
}




void TMDate::isValidDate(const char *date,int *isValid,int *d,int *m,int *y)
{
int dd,mm,yy,deb;
if(isValid) *isValid=0;
int x,sepIndex1,sepIndex2;
char sep;
char mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(date==NULL)return;
x=strlen(date);
if(x<8||x>10) return;
if(!(date[1]=='/'||date[2]=='/'||date[1]=='-'||date[2]=='-'))return;
if(date[1]=='/'||date[1]=='-')sepIndex1=1;
else sepIndex1=2;
sep=date[sepIndex1];
if(date[0]<48||date[0]>57)return;
if(sepIndex1==2&&(date[1]<48||date[1]>57)) return;
if(sepIndex1==1)
{
dd=date[0]-48;
if(dd==0) return;
}
else
{
dd=((date[0]-48)*10)+(date[1]-48);
if(dd==0)return;
}
int i=sepIndex1+1;
if(!(date[i+1]==sep||date[i+2]==sep))return;
if(date[i+1]==sep)sepIndex2=i+1;
else sepIndex2=i+2;
if(date[i]<48||date[i]>57)return;
if(sepIndex2==i+2&&(date[i+1]<48||date[i+1]>57)) return;
if(sepIndex2==i+1)
{
mm=date[i]-48;
}
else
{
mm=((date[i]-48)*10)+(date[i+1]-48);
}
if(mm<1||mm>12)return;
i=sepIndex2+1;
int r=0;
yy=0;
while(r<=3)
{
if(date[i+r]<48||date[i+r]>57)return;
yy=(yy*10)+(date[i+r]-48);
r++;
}
if(yy<1901) return;
if(yy%400==0) mth[1]=29;
else if(yy%100==0) mth[1]=28;
else if(yy%4==0) mth[1]=29;
else mth[1]=28;
if(dd<1||dd>mth[mm-1]) return;
if(isValid) *isValid=1;
*d=dd;
*y=yy;
*m=mm;
}




int TMDate::isLeapYear(int y)
{
if(y%400==0) return 1;
else if(y%100==0) return 0;
else if(y%4==0) return 1;
else return 0;
}

void TMDate::toDayNumber()
{
int x=0;
int y=1901;
while(y<this->year)
{
if(isLeapYear(y)) x=x+366;
else x=x+365;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(this->year)) mth[1]=29;
int ep=this->month-2;
int m=0;
while(m<=ep)
{
x=x+mth[m];
m++;
}
x=x+this->dayOfMonth;
this->dayNumber=x;
}

void TMDate::fromDayNumber()
{
if(this->dayNumber==0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
return;
}
int x,d,m,y;
x=this->dayNumber;
int daysInYear;
int daysInMonth;
y=1901;
while(1)
{
if(isLeapYear(y)) daysInYear=366;
else daysInYear=365;
if(x<=daysInYear) break;
x=x-daysInYear;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(y)) mth[1]=29;
m=0;
while(1)
{
daysInMonth=mth[m];
if(x<=daysInMonth) break;
x=x-daysInMonth;
m++;
}
m++;
d=x;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}

int TMDate::getDayOfMonth()
{
return this->dayOfMonth;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::getYear()
{
return this->year;
}
ostream & operator<<(ostream &o,TMDate &date)
{
o<<date.getDayOfMonth()<<"/"<<date.getMonth()<<"/"<<date.getYear()<<endl;
return o;
}


