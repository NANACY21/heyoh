#ifndef PEOPLE_H_INCLUDED
#define PEOPLE_H_INCLUDED
#include"DATE.h"
class PEOPLE
{
private:
     char number[N],ID[N],sex[N];
     DATE birthday;
public:
    PEOPLE();
    PEOPLE(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY);
    PEOPLE(PEOPLE &p);
    ~PEOPLE();
    void Cin();
    void Cout();
};
#endif // PEOPLE_H_INCLUDED
