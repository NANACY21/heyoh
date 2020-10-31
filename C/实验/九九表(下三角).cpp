#include<stdio.h>
#include <iostream>
using namespace std;
main()
{
    int a,b;
    char space=' ';
    for(a=1;a<=9;a++)
    {
        for(b=1;b<=a;b++)
        {
            cout<<b<<"*"<<a<<"="<<a*b<<"  ";
        }
        printf("\n");
    }
}
