#ifndef GRADUATE_H_INCLUDED
#define GRADUATE_H_INCLUDED
#include"PEOPLE.h"
#include"DATE.h"
#include"STUDENT.h"
class GRADUATE:public STUDENT
{
private:
    char hierophant[N],research_area[N];
public:
    GRADUATE();
    GRADUATE(char NUMBER[N],char ID1[N],char SEX[N],int YEAR,int MONTH,int DAY,char SCHOOL[N],char COLLEGE[N],char MAJOR[N],int _CLASS,int SCORE,char HIEROPHANT[N],char RESEARCH_AREA[N]);
    GRADUATE(GRADUATE &g);
    ~GRADUATE();
    void Cin();
    void Cout();
};
#endif // GRADUATE_H_INCLUDED
