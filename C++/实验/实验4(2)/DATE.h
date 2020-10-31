#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#define N 20
class DATE
{
private:
    int year,month,day;
public:
    DATE(int YEAR=0,int MONTH=0,int DAY=0);
    void Cin();
    void Cout();
};
#endif // DATE_H_INCLUDED
