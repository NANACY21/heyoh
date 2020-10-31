#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED
#include"PEOPLE.h"
#include"DATE.h"
class TEACHER:public PEOPLE
{
private:
    char job[N],department[N],job_title[N];
public:
    TEACHER();
    TEACHER(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char JOB[N],char DEPARTMENT[N],char JOB_TITLE[N]);
    TEACHER(TEACHER &t);
    ~TEACHER();
    void Cin();
    void Cout();
};

#endif // TEACHER_H_INCLUDED
