#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#define N 40
class DATE
{
private:
    int year,month,day;
public:
    DATE();
    DATE(int YEAR,int MONTH,int DAY);
    DATE(DATE &d);
    ~DATE();
    void Cin();
    void Cout();
};
#endif // DATE_H_INCLUDED
