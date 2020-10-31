#include<iostream>
#include<fstream>
#define N 20
using namespace std;
//同级!!!!!
/*void main()
{
    People p1;
    ifstream file("people.dat",ios::in);
    file.read((char *)&a,sizeof(a));
    while(file.good())
    {
        p1.Show();
        file.read((char *)&p1,sizeof(p1));
    }
}*/
/*int main()
{
    std::fstream of("D:\\实验8.txt");
    std::cout<<of.rdbuf();
}*/
int main()
{
    char a[N],b;
    ifstream file1("实验8.txt",ios::in);
    if(!file1)
        cout<<"ok"<<endl;
    int i=0;
    while(file1.good())
    {
        file1.get(b);
        cout.put(b);
        a[i]=b;
        i++;
    }
}
/*void main()
{
    ofstream f1("people.dat",ios::out);
    cout<<sizeof(People)<<endl;
    int n;
    cin>>n;
    People *p=new People[n];
    for(int i=0;i<n;i++)
    {
        p[i].Set();
        f1.write((char *)&p[i],sizeof(p[i]));
    }
    delete []p;
    f1.close();
}*/

