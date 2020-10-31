#include<iostream>
#include<string.h>
#include"DATE.h"
using namespace std;
DATE::DATE(int YEAR,int MONTH,int DAY)
{
    year=YEAR;
    month=MONTH;
    day=DAY;
}
void DATE::Cin()
{
    cin>>year>>month>>day;
}
void DATE::Cout()
{
    cout<<year<<"Äê"<<month<<"ÔÂ"<<day<<"ÈÕ";
}
