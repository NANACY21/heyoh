#include<stdio.h>
#include<ctype.h>//调用字符函数
#include<stdlib.h>
#include<conio.h>//通用输入输出库
#include<string.h>
#include<iostream>
#include<queue>//队列,优先队列
#include<vector>//向量
#include<algorithm>//sort()库函数
#include<iomanip>
#define EMPTY_BLOCK 0x0000
#define LAST_BLOCK 0xFFFF
#define MAX_SIZE 1000
using namespace std;
typedef struct FCB/* 文件控制块,目录控制块 */
{
    string name;//名
    long double size;//大小(该FCB占 size 字节)
    int first_block;
    int layer;//所在层(根目录在第 0 层)
    char type;//'C':目录,'F':文件,'X':已删除
    int block[MAX_SIZE];//该FCB所占的外存块(存块号)
    //string datetime;//该FCB的建立日期
    FCB *parent;
    FCB *next;
}FCB,*FCB1;
int block_size;
int begin_address;//开辟的外存空间起始块号
int size;//开辟的外存空间的块数
int block_show[MAX_SIZE];//外存位示图(0:空闲,1:占用)
string current_directory[MAX_SIZE];//当前目录下
int current_layer;//当前目录层
void bitmap_init();
void get_bitmap();
int get_free_size();
FCB1 FCB_belong_to(FCB1 &arg0,int &arg1,string &arg2,char &arg3,string &arg4);
void delete_FAT_i(FCB1 &arg0,int &arg1,string &arg2,char &arg3,string &arg4);
void FAT_init(FCB1 &arg0);
void md(FCB1 &arg0);
void cd(FCB1 &arg0);
void cd_(FCB1 &arg0);
void rd(FCB1 &arg0);
void mk(FCB1 &arg0);
void de(FCB1 &arg0);
void dir(FCB1 &arg0);
void help();
void menu(FCB1 &arg0);
void bitmap_init()
{
    for(int i=0;i<size;i++)
    {
        block_show[i]=0;
    }
}
void get_bitmap()
{
    int i=0;
    cout<<"--------------外存位示图--------------"<<endl;
    for(i=0;i<size;i++)
    {
        cout<<"第"<<setw(2)<<i<<"块"<<setw(2)<<block_show[i]<<"  ";
        if(i%4==3 || i==size-1)
        {
            cout<<endl;
        }
    }
    cout<<"--------------------------------------"<<endl;
}
int get_free_size()
{
    int i=0,count=0;
    for(i=0;i<size;i++)
    {
        if(block_show[i]==0)
        {
            count=count+1;
        }
    }
    count=count*block_size;
    return count;
}
FCB1 FCB_belong_to(FCB1 &arg0,int &arg1,string &arg2,char &arg3,string &arg4)
{
    FCB1 f=arg0->next;
    do//原来do-while里有5行代码
    {
        if(f->parent==NULL || f->parent->name==arg0->next->name)//?
        {
            if(f->layer==arg1 && f->name==arg2 && f->type==arg3)
            {
                return f;
            }
        }
        else
        {
            if(f->layer==arg1 && f->name==arg2 && f->type==arg3 && f->parent->name==arg4)
            {
                return f;
            }
        }
        f=f->next;
    }while(f!=arg0->next);
    return NULL;
}
void delete_FAT_i(FCB1 &arg0,int &arg1,string &arg2,char &arg3,string &arg4)
{
    FCB1 f=arg0->next,f_pre=arg0,head=arg0->next;
    do
    {
        if(f->parent==NULL || f->parent->name==arg0->next->name)
        {
            if(f->layer==arg1 && f->name==arg2 && f->type==arg3)
            {
                f_pre->next=f->next;
                delete f;
                f=head;//当只有头结点和尾指针两个结点的时候,删尾指针,需要修改尾指针
                while(f->next!=head)
                {
                    f=f->next;
                }
                arg0=f;
                break;
            }
        }
        else
        {
            if(f->layer==arg1 && f->name==arg2 && f->type==arg3 && f->parent->name==arg4)
            {
                f_pre->next=f->next;
                delete f;
                f=head;//当只有头结点和尾指针两个结点的时候,删尾指针,需要修改尾指针
                while(f->next!=head)
                {
                    f=f->next;
                }
                arg0=f;
                break;
            }
        }
        f=f->next;
        f_pre=f_pre->next;
    }while(f!=arg0->next);
}
void FAT_init(FCB1 &arg0)
{
    arg0=new FCB;//头结点为根目录
    arg0->next=arg0;
    for(int i=0;i<size;i++)
    {
        if(block_show[i]==0)
        {
            arg0->first_block=i;
            arg0->size=block_size;
            block_show[i]=1;
            break;
        }
    }
    //arg0->datetime="2018/5/7 13:30";//编译时的时刻
    arg0->name="H:";
    arg0->parent=NULL;
    arg0->type='C';
    arg0->layer=0;//
    current_directory[0]=arg0->name;
    current_layer=0;
    cout<<"已建立根目录(根目录名:"<<arg0->name<<")"<<endl;
}
void md(FCB1 &arg0)//创建一个目录
{
    FCB *f=new FCB;int i;char c='C';
    f->next=NULL;
    cin>>f->name;
    f->layer=current_layer+1;
    if(FCB_belong_to(arg0,f->layer,f->name,c,current_directory[current_layer])!=NULL)
    {
        cout<<"有重名目录"<<endl;
        delete f;
    }
    else
    {
        if(get_free_size() < block_size)
        {
            cout<<"外存空间不足"<<endl;
            delete f;
        }
        else
        {
            for(i=0;i<size;i++)
            {
                if(block_show[i]==0)
                {
                    f->first_block=i;
                    f->size=block_size;//规定新建文件夹大小为1块
                    block_show[i]=1;
                    f->block[0]=i;
                    f->block[1]=999;
                    break;
                }
            }
            f->parent=FCB_belong_to(arg0,current_layer,current_directory[current_layer],c,current_directory[current_layer]);
            f->type='C';
            f->next=arg0->next;
            arg0->next=f;
            arg0=f;
            long double temp=f->size;
            while(f->parent!=NULL)
            {
                f->parent->size += temp;
                f=f->next;
            }
        }
    }
}
void rd(FCB1 &arg0)
{
    string str;
    char c='C';
    cin>>str;
    int temp=current_layer+1,i=0,j=0;
    FCB *f=FCB_belong_to(arg0,temp,str,c,current_directory[current_layer]);
    if(f==NULL)
    {
        cout<<"该子目录不存在"<<endl;
    }
    else if(f->size!=block_size)
    {
        cout<<"删除失败(该子目录非空)"<<endl;
    }
    else
    {
        //FCB_belong_to(arg0,str,temp)->type='X';
        while(f->block[i]!=999)
        {
            j=f->block[i];
            block_show[j]=0;
            i++;
        }
        while(f->parent!=NULL)
        {
            f->parent->size -= block_size;
            f=f->next;
        }
        delete_FAT_i(arg0,temp,str,c,current_directory[current_layer]);
    }
}
void mk(FCB1 &arg0)
{
    FCB *f=new FCB;int temp,i,j=0,count=0;char c='F',d='C';
    f->next=NULL;
    cin>>f->name;
    cin>>f->size;
    f->layer=current_layer+1;
    if(FCB_belong_to(arg0,f->layer,f->name,c,current_directory[current_layer])!=NULL)
    {
        cout<<"有重名文件"<<endl;
        delete f;
    }
    else
    {
        temp=f->size/block_size + 1;
        if(get_free_size() < f->size)
        {
            cout<<"外存空间不足"<<endl;
            delete f;
        }
        else
        {
            for(i=0;i<size;i++)
            {
                if(block_show[i]==0)
                {
                    f->first_block=i;
                    break;
                }
            }
            for(i=0;i<size;i++)//从位示图头捋,把temp个0变1
            {
                if(block_show[i]==0)
                {
                    block_show[i]=1;
                    f->block[j]=i;
                    count++;
                    j++;
                }
                if(count==temp)
                {
                    f->block[j]=999;//结束符
                    break;
                }
            }
            f->parent=FCB_belong_to(arg0,current_layer,current_directory[current_layer],d,current_directory[current_layer-1]);
            f->type='F';
            f->next=arg0->next;
            arg0->next=f;
            arg0=f;
            long double temp1=f->size;
            while(f->parent!=NULL)
            {
                f->parent->size += temp1;
                f=f->next;
            }
        }
    }
}
void de(FCB1 &arg0)
{
    string str;int i=0,j=0;char c='F';
    cin>>str;
    int temp=current_layer+1;
    FCB *f=FCB_belong_to(arg0,temp,str,c,current_directory[current_layer]);
    if(f==NULL)
    {
        cout<<"该文件不存在"<<endl;
    }
    else
    {
        //FCB_belong_to(arg0,str,temp)->type='X';
        long double temp1=f->size;
        while(f->block[i]!=999)
        {
            j=f->block[i];
            block_show[j]=0;
            i++;
        }
        while(f->parent!=NULL)
        {
            f->parent->size -= temp1;
            f=f->next;
        }
        delete_FAT_i(arg0,temp,str,c,current_directory[current_layer]);
    }
}
void cd(FCB1 &arg0)
{
    char c='C';
    string str;
    cin>>str;
    int temp=current_layer+1;
    if(FCB_belong_to(arg0,temp,str,c,current_directory[current_layer])==NULL)
    {
        cout<<"错误"<<endl;
    }
    else
    {
        current_layer++;
        current_directory[current_layer]=str;
    }
}
void cd_(FCB1 &arg0)
{
    char c='C';
    if(current_layer==0)
    {

    }
    else
    {
        //current_directory=FCBs_belong_to(arg0,current_layer,current_directory,c)->parent->name;
        current_layer--;
    }
}
void dir(FCB1 &arg0)
{
    //遍历FAT链表
    FCB1 f=arg0->next->next;int flag=0;
    if(arg0->next==arg0)//若只有头结点
    {
        cout<<"该文件夹为空"<<endl;
    }
    else
    {
        do
        {
            if(f->layer==current_layer+1 && f->parent->name==current_directory[current_layer])
            {
                cout<<left<<setw(12)<<f->name<<"类型:";
                if(f->type=='C')
                {
                    cout<<left<<setw(10)<<"文件夹";
                }
                else
                {
                    cout<<left<<setw(10)<<"文件";
                }
                cout<<"大小:"<<f->size<<left<<setw(8)<<"字节";
                cout<<"所占外存块号:";
                int i=0;
                while(f->block[i]!=999)
                {
                    cout<<f->block[i]<<" ";
                    i++;
                }
                cout<<endl;
                flag=1;
            }
            f=f->next;
        }while(f!=arg0->next);
        if(flag==0)
        {
            cout<<"该文件夹为空"<<endl;
        }
    }
}
void help()
{
    cout<<"/*命令*/"<<endl;
    cout<<"MD/md 目录名:在当前目录下创建一个子目录"<<endl;
    cout<<"RD/rd 目录名:删除当前目录下的一个子目录"<<endl;
    cout<<"MK/mk 文件名 文件所占字节数:在当前目录下创建一个空文件"<<endl;
    cout<<"DE/de 文件名:删除当前目录下的一个文件"<<endl;
    cout<<"CD/cd 目录名:切换到下一级目录"<<endl;
    cout<<"cd..:切换到上一级目录"<<endl;
    cout<<"cd\\:切换到根目录"<<endl;
    cout<<"DIR/dir:显示当前目录的所有目录项"<<endl;
    cout<<"bitmap:显示外存位示图"<<endl;
    cout<<"HELP/help:帮助"<<endl;
    cout<<"Q/q:退出"<<endl;
}
void menu(FCB1 &arg0)
{
    string a;
    for(int i=0;i<=current_layer;i++)
    {
        if(i==current_layer)
        {
            cout<<current_directory[i];
        }
        else
        {
            cout<<current_directory[i]<<"\\";
        }
    }
    cout<<">";
    cin>>a;
    if(a=="MD" || a=="md")
    {
        md(arg0);
    }
    else if(a=="RD" || a=="rd")
    {
        rd(arg0);
    }
    else if(a=="MK" || a=="mk")
    {
        mk(arg0);
    }
    else if(a=="DE" || a=="de")
    {
        de(arg0);
    }
    else if(a=="CD" || a=="cd")
    {
        cd(arg0);
    }
    else if(a=="cd..")
    {
        cd_(arg0);
    }
    else if(a=="cd\\")
    {
        current_layer=0;
    }
    else if(a=="DIR" || a=="dir")
    {
        dir(arg0);
    }
    else if(a=="bitmap")
    {
        get_bitmap();
    }
    else if(a=="HELP" || a=="help")
    {
        help();
    }
    else if(a=="Q" || a=="q")
    {
        exit(0);
    }
    else
    {
        cout<<"错误的命令"<<endl;
    }
    menu(arg0);
}
main()
{
    FCB1 FAT=NULL;//尾指针,带头结点(FAT是一个链表,有很多FCB型结点)
    cout<<"外存按固定大小分成块"<<endl;
    cout<<"块的大小(1块占多少字节)(十进制):";
    cin>>block_size;//输入1024
    cout<<"--------------------------------------"<<endl;
    cout<<"开辟一个新外存空间"<<endl;
    cout<<"起始块号:";
    cin>>begin_address;
    cout<<"占多少块:";
    cin>>size;
    bitmap_init();
    cout<<"已成功开辟一个新外存空间"<<endl;
    FAT_init(FAT);//就1个分区    c: d:等均为根目录
    get_bitmap();//外存位示图
    menu(FAT);
}
