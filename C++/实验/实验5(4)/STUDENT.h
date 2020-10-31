#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include"PEOPLE.h"
#include"DATE.h"
class STUDENT:public PEOPLE
{
private:
    char school[N],college[N],major[N];
    int _class,score;
public:
    STUDENT();
    STUDENT(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char SCHOOL[N],char COLLEGE[N],char MAJOR[N],int _CLASS,int SCORE);
    STUDENT(STUDENT &s);
    ~STUDENT();
    void Cin();
    void Cout();
};


#endif // STUDENT_H_INCLUDED
