#include<stdio.h>
#include<ctype.h>/* 调用字符函数 */
#include<stdlib.h>
#include<conio.h>/* 通用输入输出库 */
#include<string.h>
#include<iostream>
#include<queue>/* 队列,优先队列 */
#include<vector>/* 向量 */
#include<algorithm>/* sort()库函数 */
#include<iomanip>
#define MAX_SIZE 9999
using namespace std;
struct page_i/* 某一页 */
{
    int page_No;//页号(即下标)
    int block_No;//块号
    int state;//状态位(该页在内存中 置1)
    int flag;//辅助OPT算法
};
typedef struct pageNo/* 队列 */
{
    int data;//页号
    pageNo *next;
}pageNo,*pageNo1;
typedef struct/* 进程类 */
{
    string name;//名
    long double begin_address;//所占内存空间起始地址(第 begin_address 字节)
    long double size;//所占内存空间大小(占 size 字节)
    int give_block;
    page_i *page_table_FIFO;//PCB表中有指针指向页表
    page_i *page_table_LRU;//PCB表中有指针指向页表
    page_i *page_table_OPT;//PCB表中有指针指向页表
    int page_table_length;//页表长度(该进程实际占 page_table_length 块)
    pageNo1 FIFO;//队列
    pageNo1 LRU;//队列
    pageNo1 OPT;//队列
    int give_block_count;
    int *logical_address;//记录逻辑地址
    int i;//logical_address[]下标
    int miss_page_fifo;//缺页次数
    int miss_page_lru;//缺页次数
    int miss_page_opt;//缺页次数
    double *miss_page_FIFO;//记录缺页率
    double *miss_page_LRU;//记录缺页率
    double *miss_page_OPT;//记录缺页率
    int lastest;//和OPT算法有关
    int length_count;//和OPT算法有关
    double arrival_time;//到达时刻
    double burst_time;//服务时间(运行时间)
    double finished_time;//结束运行时间(完成时刻)
    double runned_time;//已运行时间
    double start_time;//开始时刻
    double priority;//优先级(数小优先级大)
    double T;//周转时间
    double w;//带权周转时间
}process;
typedef struct PCB/* 链队存储结构(不带头结点的单向循环链表,不同于教材) */
{
    process pro;
    PCB *next;
}PCB,*PCB1;
struct free_memory_i/* 一段空闲内存空间类 */
{
    long double begin_address;//起始地址
    long double size;//大小
};
typedef struct Free_Memory_i
{
    free_memory_i fmi;
    Free_Memory_i *next;
}Free_Memory_i,*Free_Memory_i1;
typedef struct Node/* 通道,控制器,设备(链队) */
{
    string name;//名
    Node *next;
    Node *parent;//父结点
    PCB *process;//占用该结点的进程
    int state;//状态位(0:空闲,1:占用)
    char type;//类型
    PCB *waitinglist;//等待该结点的进程队列(尾指针)
}Node,*Node1;
string SDTs[4]={"键盘","鼠标","显示器","打印机"};/* 系统设备表 */
int block_size;
int begin_address;/* 开辟的内存空间起始块号 */
int size;/* 开辟的内存空间的块数 */
int block_show[MAX_SIZE];/* 内存位示图(0表示空闲) */
double _T=0;/* 平均周转时间 */
double _w=0;/* 平均带权周转时间 */
void bitmap_init();//内存位示图初始化
void bitmap_display();//内存位示图显示
void PCB_init(process &arg0);//PCB初始化
void LD_init_(pageNo1 &arg0);
void LD_rudui_(pageNo1 &arg0,int &arg1);
void LD_chudui_(pageNo1 &arg0,int &arg1);
int LD_get_front_(pageNo1 &arg0);
void LD_change(pageNo1 &arg0,int &arg1);
bool LD_belong_to(pageNo1 &arg0,int &arg1);//判断arg1是否为队列元素
int LD_length_(pageNo1 &arg0);
void delete_LD_i(pageNo1 &arg0,int &arg1);
void LD_display_(pageNo1 &arg0);
void page_table_display(PCB1 &arg0);//页表显示
void address_translation(PCB1 &arg0);
void run_process(PCB1 &arg0);
void LD_init(PCB1 &arg0);
void LD_rudui(PCB1 &arg0,process &arg1);
void LD_chudui(PCB1 &arg0,process &arg1);
void delete_PCB(PCB1 &arg0,process &arg1);
PCB1 LD_get_front(PCB1 &arg0);
int LD_length(PCB1 &arg0);
void LD_display(PCB1 &arg0);//不带头结点的单向循环链表的遍历
bool LD_empty(PCB1 &arg0);
void choose_scheduling_algorithm(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished);   //选择进程调度算法
void FCFS(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished);                          //进程调度算法 - FCFS
void SPF_PSA_HRRN(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0);        //进程调度算法 - SPF / PSA / HRRN
int find_shortest_process(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0);//进程调度算法 - SPF 辅助算法
int find_VIPest_process(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0);  //进程调度算法 - PSA 辅助算法
int find_max_w_process(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0);   //进程调度算法 - HRRN辅助算法
void RR(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished);                            //进程调度算法 - RR
bool all_process_finished(PCB1 &arg0);                                                //进程调度算法 - RR  辅助算法
void MFQ(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished);                           //进程调度算法 - MFQ
void Auto(PCB1 &ready,PCB1 &run);                                                     //自动调度
void process_sort(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished);                  //把进程按到达时间排序
void process_situation(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished);
void process_situation_time(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished);
void Copy(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,PCB1 &ready_,PCB1 &run_,PCB1 &block_,PCB1 &finished_);//生成副本
void free_memory_init(Free_Memory_i1 &head);
void free_memory_create(Free_Memory_i1 &head,free_memory_i &arg0);
void free_memory_display(Free_Memory_i1 &head);
Node1 Node_belong_to(Node1 &arg0,string &arg1);
void delete_Node(Node1 &arg0,string &arg1);
void IO_hardware_init(Node1 &CHCTs,Node1 &COCTs,Node1 &DCTs);
void IO_hardware_display(Node1 &CHCTs,Node1 &COCTs,Node1 &DCTs);
void help();
void menu(Node1 &CHCTs,Node1 &COCTs,Node1 &DCTs,PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,Free_Memory_i1 &free_memory);
void bitmap_init()//内存位示图初始化
{
    for(int i=0;i<size;i++)
    {
        block_show[i]=0;
    }
}
void bitmap_display()//内存位示图显示
{
    cout<<"--------------内存位示图--------------"<<endl;
    for(int i=0;i<size;i++)
    {
        cout<<"第"<<setw(2)<<i<<"块"<<setw(2)<<block_show[i]<<"  ";
        if(i%4==3 || i==size-1)
        {
            cout<<endl;
        }
    }
    cout<<"--------------------------------------"<<endl;
}
void PCB_init(process &arg0)//PCB初始化
{
    for(int i=0;i<arg0.page_table_length;i++)//进程页表初始化
    {
        arg0.page_table_FIFO[i].page_No=i;
        arg0.page_table_FIFO[i].block_No=-1;
        arg0.page_table_FIFO[i].state=0;
        arg0.page_table_FIFO[i].flag=0;
        arg0.page_table_LRU[i].page_No=i;
        arg0.page_table_LRU[i].block_No=-1;
        arg0.page_table_LRU[i].state=0;
        arg0.page_table_LRU[i].flag=0;
        arg0.page_table_OPT[i].page_No=i;
        arg0.page_table_OPT[i].block_No=-1;
        arg0.page_table_OPT[i].state=0;
        arg0.page_table_OPT[i].flag=0;
    }
    arg0.give_block_count=0;
    arg0.logical_address=new int[MAX_SIZE];
    arg0.i=0;
    arg0.miss_page_fifo=0;
    arg0.miss_page_lru=0;
    arg0.miss_page_opt=0;
    arg0.miss_page_FIFO=new double[MAX_SIZE];
    arg0.miss_page_LRU=new double[MAX_SIZE];
    arg0.miss_page_OPT=new double[MAX_SIZE];
    arg0.lastest=0;
    arg0.length_count=0;
    arg0.runned_time=0;
    arg0.finished_time=MAX_SIZE;
}
void LD_init_(pageNo1 &arg0)
{
    arg0 = NULL;
}
void LD_rudui_(pageNo1 &arg0,int &arg1)
{
    pageNo *p=new pageNo;
    p->data=arg1;
    if(arg0==NULL)//如果链队为空
    {
        p->next=p;
        arg0=p;
    }
    else//如果链队不为空
    {
        p->next=arg0->next;
        arg0->next=p;
        arg0=p;
    }
}
void LD_chudui_(pageNo1 &arg0,int &arg1)
{
    pageNo *q;
    if(arg0==NULL)
    {
        exit(0);
    }
    else if(arg0->next==arg0)
    {
        arg1=arg0->data;
        delete arg0;
        arg0=NULL;
    }
    else
    {
        q=arg0->next;
        arg1=q->data;
        arg0->next=q->next;
        delete q;
    }
}
int LD_get_front_(pageNo1 &arg0)
{
    return arg0->next->data;
}
void LD_change(pageNo1 &arg0,int &arg1)
{
    /* 功能:把链队中的arg1移到队尾 */
    pageNo *p=arg0->next,*p_pre=arg0;
    if(arg0->data==arg1)
    {

    }
    else
    {
        while(p->data!=arg0->data)
        {
            if(p->data==arg1)
            {
                p_pre->next=p->next;
                delete p;
                break;
            }
            p=p->next;
            p_pre=p_pre->next;
        }
        LD_rudui_(arg0,arg1);
    }
}
bool LD_belong_to(pageNo1 &arg0,int &arg1)//判断arg1是否为队列元素
{
    pageNo *p=arg0->next;
    if(arg0->data==arg1)
    {
        return true;
    }
    else
    {
        while(p->data!=arg0->data)
        {
            if(p->data==arg1)
            {
                return true;
            }
            p=p->next;
        }
        return false;
    }
}
int LD_length_(pageNo1 &arg0)
{
    /* 功能:返回队列元素个数 */
    int count=0;
    if(arg0==NULL)
    {

    }
    else
    {
        pageNo *p=arg0->next;
        do
        {
            count++;
            p=p->next;//指针后移
        }while(p!=arg0->next);
    }
    return count;
}
void delete_LD_i(pageNo1 &arg0,int &arg1)
{
    pageNo1 p=arg0->next,p_pre=arg0;
    do
    {
        if(p->data==arg1)
        {
            p_pre->next=p->next;
            delete p;
            break;
        }
        p=p->next;
        p_pre=p_pre->next;
    }while(p!=arg0->next);
}
void LD_display_(pageNo1 &arg0)
{
    if(arg0==NULL)
    {
        cout<<""<<endl;
    }
    else
    {
        pageNo *p=arg0->next;
        do
        {
            cout<<p->data<<" ";
            p=p->next;//指针后移
        }while(p!=arg0->next);
        cout<<endl;
    }
}
void page_table_display(PCB1 &arg0)//页表显示
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"| 页表(FIFO置换) |  页表(LRU置换) |  页表(OPT置换) |"<<endl;
    cout<<"|----------------|----------------|----------------|"<<endl;
    cout<<"|页号 块号 状态位|页号 块号 状态位|页号 块号 状态位|"<<endl;
    for(int i=0;i<arg0->pro.page_table_length;i++)
    {
        cout<<"|"<<setw(3)<<arg0->pro.page_table_FIFO[i].page_No<<setw(5)<<arg0->pro.page_table_FIFO[i].block_No<<setw(6)<<arg0->pro.page_table_FIFO[i].state<<setw(3)<<"|"<<setw(3)<<arg0->pro.page_table_LRU[i].page_No<<setw(5)<<arg0->pro.page_table_LRU[i].block_No<<setw(6)<<arg0->pro.page_table_LRU[i].state<<setw(3)<<"|"<<setw(3)<<arg0->pro.page_table_OPT[i].page_No<<setw(5)<<arg0->pro.page_table_OPT[i].block_No<<setw(6)<<arg0->pro.page_table_OPT[i].state<<setw(3)<<"|"<<endl;
    }
    cout<<"----------------------------------------------------"<<endl;
}
void address_translation(PCB1 &arg0)
{
    int i=arg0->pro.i;
    cout<<"-----------------------------------"<<endl;
    printf("这个进程逻辑地址范围 0 - %x (16进制)\n",arg0->pro.size-1);
    cout<<"-----------------------------------"<<endl;
    printf("输入逻辑地址(16进制)以得到对应物理地址:");//输入逻辑地址以确定页号
    scanf("%x",&arg0->pro.logical_address[i]);
    cout<<"-----------------------------------"<<endl;
    int page_No=(int)(arg0->pro.logical_address[i]/block_size);//页号
    if(page_No<0 || page_No>=arg0->pro.page_table_length || arg0->pro.logical_address[i]<0 || arg0->pro.logical_address[i]>arg0->pro.size-1)
    {
        printf("%x不是这个进程的逻辑地址\n",arg0->pro.logical_address[i]);
    }
    else
    {
        i=arg0->pro.i;
        printf("逻辑地址:%x\n",arg0->pro.logical_address[i]);
        /*块没满或刚满(块没满或刚满时,要么都命中,要么都没命中)*/
        if(arg0->pro.give_block_count<arg0->pro.give_block)
        {
            if(arg0->pro.page_table_FIFO[page_No].state==1)
            {
                printf("对应物理地址为%x(FIFO置换)\n",arg0->pro.page_table_FIFO[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
                LD_change(arg0->pro.LRU,page_No);/* 一旦命中page_No移动到LRU队列队尾 */
                printf("对应物理地址为%x(LRU置换)\n",arg0->pro.page_table_LRU[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
            }
            else
            {
                arg0->pro.miss_page_fifo++;
                arg0->pro.miss_page_lru++;
                for(int z=0;z<32;z++)
                {
                    if(block_show[z]==0)
                    {
                        arg0->pro.page_table_FIFO[page_No].state=1;//该页进内存
                        arg0->pro.page_table_FIFO[page_No].block_No=z;
                        arg0->pro.page_table_LRU[page_No].state=1;//该页进内存
                        arg0->pro.page_table_LRU[page_No].block_No=z;
                        block_show[z]=1;
                        arg0->pro.give_block_count++;
                        LD_rudui_(arg0->pro.FIFO,page_No);//队列中的是页号
                        LD_rudui_(arg0->pro.LRU,page_No);
                        break;
                    }
                }
                printf("对应物理地址为%x(FIFO置换)\n",arg0->pro.page_table_FIFO[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
                printf("对应物理地址为%x(LRU置换)\n",arg0->pro.page_table_LRU[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
            }
        }
        else
        {
            if(arg0->pro.page_table_FIFO[page_No].state==1)
            {
                printf("对应物理地址为%x(FIFO置换)\n",arg0->pro.page_table_FIFO[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
            }
            if(arg0->pro.page_table_FIFO[page_No].state==0)
            {
                arg0->pro.miss_page_fifo++;
                int arg,arg1;
                arg=LD_get_front_(arg0->pro.FIFO);
                arg0->pro.page_table_FIFO[arg].state=0;//出队的那个页状态位置0
                arg0->pro.page_table_FIFO[page_No].block_No=arg0->pro.page_table_FIFO[arg].block_No;//出队的那个页的块号为这个页的块号
                arg0->pro.page_table_FIFO[arg].block_No=-1;//出队的那个页的块号置-1
                arg0->pro.page_table_FIFO[page_No].state=1;//该页进内存
                LD_chudui_(arg0->pro.FIFO,arg1);
                LD_rudui_(arg0->pro.FIFO,page_No);//队列中的是页号
                printf("对应物理地址为:%x(FIFO置换)\n",arg0->pro.page_table_FIFO[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
            }
            if(arg0->pro.page_table_LRU[page_No].state==1)
            {
                LD_change(arg0->pro.LRU,page_No);/* 一旦命中page_No移动到LRU队列队尾 */
                printf("对应物理地址为%x(LRU置换)\n",arg0->pro.page_table_LRU[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
            }
            if(arg0->pro.page_table_LRU[page_No].state==0)
            {
                arg0->pro.miss_page_lru++;
                int arg,arg1;
                arg=LD_get_front_(arg0->pro.LRU);
                arg0->pro.page_table_LRU[arg].state=0;//出队的那个页状态位置0
                arg0->pro.page_table_LRU[page_No].block_No=arg0->pro.page_table_LRU[arg].block_No;//出队的那个页的块号为这个页的块号
                arg0->pro.page_table_LRU[arg].block_No=-1;//出队的那个页的块号置-1
                arg0->pro.page_table_LRU[page_No].state=1;//该页进内存
                LD_chudui_(arg0->pro.LRU,arg1);
                LD_rudui_(arg0->pro.LRU,page_No);
                printf("对应物理地址为:%x(LRU置换)\n",arg0->pro.page_table_LRU[page_No].block_No*block_size + arg0->pro.logical_address[i]%block_size);
            }
        }
        arg0->pro.miss_page_FIFO[i]=((float)arg0->pro.miss_page_fifo / (float)(i+1))*100;
        arg0->pro.miss_page_LRU[i]=((float)arg0->pro.miss_page_lru / (float)(i+1))*100;
        cout<<"缺页率:"<<endl;
        cout<<arg0->pro.miss_page_FIFO[i]<<"%(FIFO置换)"<<endl;
        cout<<arg0->pro.miss_page_LRU[i]<<"%(LRU置换)"<<endl;
        arg0->pro.i++;
    }
    page_table_display(arg0);
    cout<<"当前FIFO队列页号:";LD_display_(arg0->pro.FIFO);
    cout<<"-----------------------------------"<<endl;
    cout<<"当前LRU队列页号:";LD_display_(arg0->pro.LRU);
    bitmap_display();
    run_process(arg0);
}
void run_process(PCB1 &arg0)
{
    char a,b;
    if(arg0->pro.i==0)
    {
        cout<<"运行这个进程?(y or n)";
    }
    else
    {
        cout<<"继续运行这个进程?(y or n)";
    }
    do
    {
        cin>>b;
        if(b!='n'&&b!='y')
        {
            cout<<"(输入有误)(y or n)";
            a='y';
            getchar();
        }
        else
        {
            a=0;
        }
    }while(a=='y');
    switch(b)
    {
        case 'y':
            address_translation(arg0);
            break;
        case 'n':
            arg0->pro.give_block_count=0;
            cout<<"OPT页面置换算法:"<<endl;
            cout<<"-----------------------------------"<<endl;
            cout<<"这个进程逻辑地址轨迹:"<<endl;
            for(int i=0;i<arg0->pro.i;i++)
            {
                cout<<arg0->pro.logical_address[i]<<" ";
            }
            cout<<endl;
            cout<<"-----------------------------------"<<endl;
            for(int z=0;z<arg0->pro.i;z++)
            {
                printf("输入逻辑地址(16进制)以得到对应物理地址:");//输入逻辑地址以确定页号
                scanf("%x",&arg0->pro.logical_address[z]);
                cout<<"-----------------------------------"<<endl;
                int page_No=(int)(arg0->pro.logical_address[z]/block_size);//页号
                printf("逻辑地址:%x\n",arg0->pro.logical_address[z]);
                if(arg0->pro.give_block_count<arg0->pro.give_block)
                {
                    if(arg0->pro.page_table_OPT[page_No].state==1)
                    {
                        printf("对应物理地址为%x(OPT置换)\n",arg0->pro.page_table_OPT[page_No].block_No*block_size + arg0->pro.logical_address[z]%block_size);
                    }
                    else
                    {
                        arg0->pro.miss_page_opt++;
                        for(int x=0;x<32;x++)
                        {
                            if(block_show[x]==0)
                            {
                                arg0->pro.page_table_OPT[page_No].state=1;//该页进内存
                                arg0->pro.page_table_OPT[page_No].block_No=x;
                                block_show[x]=1;
                                arg0->pro.give_block_count++;
                                LD_rudui_(arg0->pro.OPT,page_No);//队列中的是页号
                                break;
                            }
                        }
                        printf("对应物理地址为%x(OPT置换)\n",arg0->pro.page_table_OPT[page_No].block_No*block_size + arg0->pro.logical_address[z]%block_size);
                    }
                }
                else
                {
                    if(arg0->pro.page_table_OPT[page_No].state==1)
                    {
                        printf("对应物理地址为%x(OPT置换)\n",arg0->pro.page_table_OPT[page_No].block_No*block_size + arg0->pro.logical_address[z]%block_size);
                    }
                    else//OPT页面置换算法
                    {
                        arg0->pro.miss_page_opt++;
                        for(int k=z+1;k<arg0->pro.i;k++)
                        {
                            int page_No=(int)(arg0->pro.logical_address[k]/block_size);//页号
                            if(LD_belong_to(arg0->pro.OPT,page_No)==true)
                            {
                                arg0->pro.page_table_OPT[page_No].flag++;
                                if(arg0->pro.page_table_OPT[page_No].flag==1)
                                {
                                    arg0->pro.lastest=k;
                                }
                            }
                        }
                        pageNo *p=arg0->pro.OPT;
                        if(arg0->pro.page_table_OPT[p->data].flag==0)
                        {

                        }
                        else
                        {
                            int page_No=(int)(arg0->pro.logical_address[arg0->pro.lastest]/block_size);//页号
                            delete_LD_i(arg0->pro.OPT,page_No);//删队列里为page_No的元素
                        }
                    }
                }
                arg0->pro.miss_page_LRU[z]=((float)arg0->pro.miss_page_opt / (float)(z+1))*100;
                cout<<"缺页率:"<<endl;
                cout<<arg0->pro.miss_page_FIFO[z]<<"%(FIFO置换)"<<endl;
                cout<<arg0->pro.miss_page_LRU[z]<<"%(LRU置换)"<<endl;
                cout<<((float)arg0->pro.miss_page_opt / (float)(z+1))*100<<"%(OPT置换)"<<endl;
            }
            page_table_display(arg0);
            cout<<"当前OPT队列页号:";LD_display_(arg0->pro.FIFO);
            bitmap_display();
            break;
    }
}
void LD_init(PCB1 &arg0)
{
    arg0 = NULL;
}
void LD_rudui(PCB1 &arg0,process &arg1)
{
    PCB *p=new PCB;
    p->pro=arg1;
    if(arg0==NULL)//如果链队为空
    {
        p->next=p;
        arg0=p;
    }
    else//如果链队不为空
    {
        p->next=arg0->next;
        arg0->next=p;
        arg0=p;
    }
}
void LD_chudui(PCB1 &arg0,process &arg1)
{
    PCB *q;
    if(arg0==NULL)
    {
        exit(0);
    }
    else if(arg0->next==arg0)
    {
        arg1=arg0->pro;
        delete arg0;
        arg0=NULL;
    }
    else
    {
        q=arg0->next;
        arg1=q->pro;
        arg0->next=q->next;
        delete q;
    }
}
void delete_PCB(PCB1 &arg0,process &arg1)
{
    if(arg0==NULL)
    {

    }
    else
    {
        PCB *p=arg0->next,*p_pre=arg0;
        if(arg0->pro.name==arg1.name)
        {
            delete arg0;
            arg0=NULL;
        }
        else
        {
            while(p->pro.name!=arg0->pro.name)
            {
                if(p->pro.name==arg1.name)
                {
                    p_pre->next=p->next;
                    delete p;
                    break;
                }
                p=p->next;
                p_pre=p_pre->next;
            }
        }
    }
}
PCB1 LD_get_front(PCB1 &arg0)
{
    PCB1 p=arg0->next;
    return p;
}
int LD_length(PCB1 &arg0)
{
    int count=0;
    if(arg0==NULL)
    {
        return count;
    }
    else
    {
        PCB *p=arg0->next;
        do
        {
            count++;
            p=p->next;//指针后移
        }while(p!=arg0->next);
    }
    return count;
}
void LD_display(PCB1 &arg0)//不带头结点的单向循环链表的遍历
{
    if(arg0==NULL)
    {
        cout<<""<<endl;
    }
    else
    {
        PCB *p=arg0->next;
        do
        {
            cout<<p->pro.name<<"("<<p->pro.begin_address<<" "<<p->pro.size<<")    ";
            p=p->next;//指针后移
        }while(p!=arg0->next);
        cout<<endl;
    }
}
bool LD_empty(PCB1 &arg0)
{
    if(arg0==NULL)//如果链队为空则返回true
    {
        return true;
    }
    else
    {
        return false;
    }
}
void choose_scheduling_algorithm(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished)
{
    if(LD_empty(ready)==true)
    {

    }
    else
    {
        int b,c;
        cout<<"选择调度算法"<<endl;
        cout<<"(1)先来先服务(FCFS)"<<endl;
        cout<<"(2)短进程优先(SPF)"<<endl;
        cout<<"(3)时间片轮转(RR)"<<endl;
        cout<<"(4)优先级(PSA)"<<endl;
        cout<<"(5)响应比高者优先(HRRN)"<<endl;
        cout<<"(6)多级队列"<<endl;
        cout<<"(7)多级反馈队列(MFQ)"<<endl;
        cout<<"(8)自动调度(Auto)"<<endl;
        cout<<"(9)稍后调度"<<endl;
        do
        {
            cin>>b;
            if(b<1||b>9)
            {
                cout<<"(输入有误)(1-9)";
                c=1;
                getchar();
            }
            else
            {
                c=0;
            }
        }while(c==1);
        switch(b)
        {
            case 1:
                FCFS(ready,run,block,finished);
                break;
            case 2:
                SPF_PSA_HRRN(ready,run,block,finished,b);
                break;
            case 3:
                RR(ready,run,block,finished);
                break;
            case 4:
                SPF_PSA_HRRN(ready,run,block,finished,b);
                break;
            case 5:
                SPF_PSA_HRRN(ready,run,block,finished,b);
                break;
            case 6:

                break;
            case 7:
                MFQ(ready,run,block,finished);
                break;
            case 8:
                Auto(ready,run);
                break;
            case 9:

                break;
        }
    }
}
void FCFS(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished)
{
    PCB1 p=LD_get_front(ready),p_pre=ready;
    p_pre->pro.finished_time=p->pro.arrival_time;
    do
    {
        p->pro.start_time=p_pre->pro.finished_time;
        p->pro.finished_time=p->pro.start_time+p->pro.burst_time;
        p->pro.T=p->pro.finished_time-p->pro.arrival_time;
        p->pro.w=p->pro.T/p->pro.burst_time;
        p=p->next;
        p_pre=p_pre->next;
    }while(p!=ready->next);
    p=LD_get_front(ready);
    _T=0;
    _w=0;
    do
    {
        _T=_T+p->pro.T;
        _w=_w+p->pro.w;
        p=p->next;
    }while(p!=ready->next);
    _T=_T/LD_length(ready);
    _w=_w/LD_length(ready);
}
void SPF_PSA_HRRN(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0)
{
    PCB1 p=LD_get_front(ready);
    int arg1=p->pro.arrival_time,arg2=LD_length(ready);
    if(arg0==2)
    {
        while(arg2--)
        {
            arg1=find_shortest_process(ready,run,block,finished,arg1);
        }
    }
    if(arg0==4)
    {
        while(arg2--)
        {
            arg1=find_VIPest_process(ready,run,block,finished,arg1);
        }
    }
    if(arg0==5)
    {
        while(arg2--)
        {
            arg1=find_max_w_process(ready,run,block,finished,arg1);
        }
    }
    p=LD_get_front(ready);
    _T=0;
    _w=0;
    do
    {
        _T=_T+p->pro.T;
        _w=_w+p->pro.w;
        p=p->next;
    }while(p!=ready->next);
    _T=_T/LD_length(ready);
    _w=_w/LD_length(ready);
}

int find_shortest_process(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0)//arg0为当前时刻
{
    /*函数功能:在 到达时间在 0 - arg0 且 未结束运行的进程里找运行时间最短的进程q*/
    PCB1 p=LD_get_front(ready),q=NULL;
    int shortest=0;
    do//初始化
    {
        if(p->pro.arrival_time <= arg0 && p->pro.runned_time != p->pro.burst_time)
        {
            q=p;
            shortest=p->pro.burst_time;
            break;
        }
        p=p->next;
    }while(p!=ready->next);
    if(q==NULL)
    {
        return arg0;
    }
    else
    {
        p=LD_get_front(ready);
        do
        {
            if(p->pro.arrival_time <= arg0 && p->pro.runned_time!=p->pro.burst_time && p->pro.burst_time < shortest)
            {
                shortest=p->pro.burst_time;
                q=p;
            }
            p=p->next;
        }while(p!=ready->next);
        q->pro.start_time=arg0;
        q->pro.finished_time=q->pro.start_time + q->pro.burst_time;
        q->pro.runned_time=q->pro.burst_time;
        q->pro.T=q->pro.finished_time - q->pro.arrival_time;
        q->pro.w=q->pro.T / q->pro.burst_time;
        return q->pro.finished_time;
    }
}

int find_VIPest_process(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0)//进程调度算法-PRI 辅助算法
{
    /*函数功能:在 到达时间在 0 - arg0 且 未结束运行的进程里找优先级最高的进程q*/
    PCB1 p=LD_get_front(ready),q=NULL;
    int VIPest=0;
    do//初始化
    {
        if(p->pro.arrival_time <= arg0 && p->pro.runned_time != p->pro.burst_time)
        {
            q=p;
            VIPest=p->pro.burst_time;
            break;
        }
        p=p->next;
    }while(p!=ready->next);
    if(q==NULL)
    {
        return arg0;
    }
    else
    {
        p=LD_get_front(ready);
        do
        {
            if(p->pro.arrival_time <= arg0 && p->pro.runned_time!=p->pro.burst_time && p->pro.priority < VIPest)
            {
                VIPest=p->pro.priority;
                q=p;
            }
            p=p->next;
        }while(p!=ready->next);
        q->pro.start_time=arg0;
        q->pro.finished_time=q->pro.start_time + q->pro.burst_time;
        q->pro.runned_time=q->pro.burst_time;
        q->pro.T=q->pro.finished_time - q->pro.arrival_time;
        q->pro.w=q->pro.T / q->pro.burst_time;
        return q->pro.finished_time;
    }
}
int find_max_w_process(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,int &arg0)  //进程调度算法 - HRRN辅助算法
{
    /*函数功能:在 到达时间在 0 - arg0 且 未结束运行的进程里找w最大的进程q*/
    PCB1 p=LD_get_front(ready),q=NULL;
    int max_w=0;
    do//初始化
    {
        if(p->pro.arrival_time <= arg0 && p->pro.runned_time != p->pro.burst_time)
        {
            q = p;
            max_w = (arg0 - p->pro.arrival_time) / p->pro.burst_time;
            break;
        }
        p=p->next;
    }while(p!=ready->next);
    if(q==NULL)
    {
        return arg0;
    }
    else
    {
        p=LD_get_front(ready);
        do
        {
            int temp = (arg0-p->pro.arrival_time) / p->pro.burst_time;
            if(p->pro.arrival_time <= arg0 && p->pro.runned_time!=p->pro.burst_time && temp > max_w)
            {
                max_w = temp;
                q=p;
            }
            p=p->next;
        }while(p!=ready->next);
        q->pro.start_time=arg0;
        q->pro.finished_time=q->pro.start_time + q->pro.burst_time;
        q->pro.runned_time=q->pro.burst_time;
        q->pro.T=q->pro.finished_time - q->pro.arrival_time;
        q->pro.w=q->pro.T / q->pro.burst_time;
        return q->pro.finished_time;
    }
}

void RR(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished)
{
    PCB1 p=LD_get_front(ready);
    process pro;
    int q,current_time = p->pro.arrival_time;//当前时间初始化;
    cout<<"时间片大小:";
    cin>>q;
    do
    {
        p->pro.start_time = current_time;
        current_time = current_time + q;
        p=p->next;
    }while(p!=ready->next);
    p=LD_get_front(ready);
    current_time=p->pro.arrival_time;//当前时间初始化
    while(all_process_finished(ready)==false)
    {
        p=LD_get_front(ready);
        if(p->pro.finished_time==MAX_SIZE)
        {
            if(p->pro.burst_time - p->pro.runned_time < q)
            {
                p->pro.runned_time = p->pro.runned_time + (p->pro.burst_time - p->pro.runned_time);
                current_time = current_time + (p->pro.burst_time - p->pro.runned_time);
                p->pro.finished_time = current_time;
            }
            else
            {
                p->pro.runned_time = p->pro.runned_time + q;
                current_time = current_time + q;
                if(p->pro.runned_time==p->pro.burst_time)
                {
                    p->pro.finished_time=current_time;
                }
                else
                {
                    LD_chudui(ready,pro);
                    LD_rudui(ready,pro);
                }
            }
        }
        else
        {
            LD_chudui(ready,pro);
            LD_rudui(ready,pro);
        }
    }
    p=LD_get_front(ready);
    do
    {
        p->pro.T=p->pro.finished_time-p->pro.arrival_time;
        p->pro.w=p->pro.T/p->pro.burst_time;
        p=p->next;
    }while(p!=ready->next);
    p=LD_get_front(ready);
    _T=0;
    _w=0;
    do
    {
        _T=_T+p->pro.T;
        _w=_w+p->pro.w;
        p=p->next;
    }while(p!=ready->next);
    _T=_T/LD_length(ready);
    _w=_w/LD_length(ready);
    process_sort(ready,run,block,finished);
}

void MFQ(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished)                           //进程调度算法 - MFQ
{
    PCB1 ready_1=NULL,ready_2=NULL,ready_3=NULL;
    PCB *p=LD_get_front(ready),*p1=NULL,*p2=NULL,*p3=NULL;
    process pro=p->pro;
    int q1,q2,q3,current_time = p->pro.arrival_time;//当前时间初始化;
    cout<<"输入1级队列 2级队列 3级队列时间片大小:";//时间片大小递增
    cin>>q1>>q2>>q3;
    do
    {
        p->pro.start_time=current_time;
        current_time = current_time + q1;
        p=p->next;
    }while(p!=ready->next);
    p=LD_get_front(ready);
    current_time=p->pro.arrival_time;//当前时间初始化
    while(all_process_finished(ready)==false)
    {
        if(LD_empty(ready)==false)
        {
            p=LD_get_front(ready);
            if(p->pro.finished_time!=MAX_SIZE)
            {
                LD_chudui(ready,pro);
                LD_rudui(ready,pro);
            }
            else
            {
                LD_chudui(ready,pro);
                LD_rudui(ready_1,pro);
            }
        }
        if(LD_empty(ready_1)==true)
        {
            if(LD_empty(ready_2)==true)
            {
                p3=LD_get_front(ready_3);
                if(p3->pro.burst_time - p3->pro.runned_time < q3)
                {
                    p3->pro.runned_time = p3->pro.runned_time + (p3->pro.burst_time - p3->pro.runned_time);
                    current_time = current_time + (p3->pro.burst_time - p3->pro.runned_time);
                    p3->pro.finished_time = current_time;
                    LD_chudui(ready_3,pro);
                    LD_rudui(ready,pro);
                }
                else
                {
                    p3->pro.runned_time = p3->pro.runned_time + q3;
                    current_time = current_time + q3;
                    if(p3->pro.runned_time==p3->pro.burst_time)
                    {
                        p3->pro.finished_time=current_time;
                        LD_chudui(ready_3,pro);
                        LD_rudui(ready,pro);
                    }
                    else
                    {
                        LD_chudui(ready_3,pro);
                        LD_rudui(ready_3,pro);
                    }
                }
            }
            else
            {
                p2 = LD_get_front(ready_2);
                if(p2->pro.burst_time - p2->pro.runned_time < q2)
                {
                    p2->pro.runned_time = p2->pro.runned_time + (p2->pro.burst_time - p2->pro.runned_time);
                    current_time = current_time + (p2->pro.burst_time - p2->pro.runned_time);
                    p2->pro.finished_time=current_time;
                    LD_chudui(ready_2,pro);
                    LD_rudui(ready,pro);
                }
                else
                {
                    p2->pro.runned_time = p2->pro.runned_time + q2;
                    current_time = current_time + q2;
                    if(p2->pro.runned_time==p2->pro.burst_time)
                    {
                        p2->pro.finished_time=current_time;
                        LD_chudui(ready_2,pro);
                        LD_rudui(ready,pro);
                    }
                    else
                    {
                        LD_chudui(ready_2,pro);
                        LD_rudui(ready_3,pro);
                    }
                }
            }
        }
        else
        {
            p1=LD_get_front(ready_1);
            if(p1->pro.burst_time - p1->pro.runned_time < q1)
            {
                p1->pro.runned_time = p1->pro.runned_time + (p->pro.burst_time - p->pro.runned_time);
                current_time = current_time + (p1->pro.burst_time - p1->pro.runned_time);
                p1->pro.finished_time=current_time;
                LD_chudui(ready_1,pro);
                LD_rudui(ready,pro);
            }
            else
            {
                p1->pro.runned_time = p1->pro.runned_time + q1;
                current_time = current_time + q1;
                if(p1->pro.runned_time==p1->pro.burst_time)
                {
                    p1->pro.finished_time = current_time;
                    LD_chudui(ready_1,pro);
                    LD_rudui(ready,pro);
                }
                else
                {
                    LD_chudui(ready_1,pro);
                    LD_rudui(ready_2,pro);
                }
            }
        }
    }
    p=LD_get_front(ready);
    do
    {
        p->pro.T=p->pro.finished_time-p->pro.arrival_time;
        p->pro.w=p->pro.T/p->pro.burst_time;
        p=p->next;
    }while(p!=ready->next);
    p=LD_get_front(ready);
    _T=0;
    _w=0;
    do
    {
        _T=_T+p->pro.T;
        _w=_w+p->pro.w;
        p=p->next;
    }while(p!=ready->next);
    _T=_T/LD_length(ready);
    _w=_w/LD_length(ready);
    process_sort(ready,run,block,finished);
}

void Auto(PCB1 &ready,PCB1 &run)//自动调度
{
    process pro;
    if(LD_empty(run)==true && LD_empty(ready)==false)
    {
        LD_chudui(ready,pro);
        LD_rudui(run,pro);
    }
}

bool all_process_finished(PCB1 &arg0)
{
    /*函数功能:判断是不是所有进程均运行完毕*/
    if(arg0==NULL)
    {
        return false;
    }
    PCB1 p=LD_get_front(arg0);
    do
    {
        if(p->pro.runned_time!=p->pro.burst_time)
        {
            return false;
        }
        p=p->next;
    }while(p!=arg0->next);
    return true;
}

void process_sort(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished)//把进程按到达时间排序
{
    int i=0,j=0,n=LD_length(ready);
    PCB *head=ready->next,*p,*p1;
    if(ready==NULL || ready==ready->next)
    {

    }
    else
    {
        for(i=0;i<n-1;i++)
        {
            head=ready->next;
            for(j=0;j<n-i-1;j++)
            {
                p=head;
                p1=head->next;
                if(p->pro.arrival_time > p1->pro.arrival_time)
                {
                    process pro = p->pro;
                    p->pro = p1->pro;
                    p1->pro = pro;
                }
                head=head->next;
            }
        }
    }
}
void process_situation(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished)
{
    PCB *p=ready->next;
    cout<<"----------------------------------------------------"<<endl;
    cout<<setw(12)<<"进程名"<<"|";
    do
    {
        cout<<p->pro.name<<"|";
        p=p->next;
    }while(p!=ready->next);
    cout<<endl;
    p=ready->next;
    cout<<setw(12)<<"到达时刻"<<"|";
    do
    {
        cout<<setw(p->pro.name.size())<<p->pro.arrival_time<<"|";
        p=p->next;
    }while(p!=ready->next);
    cout<<endl;
    p=ready->next;
    cout<<setw(12)<<"运行时间"<<"|";
    do
    {
        cout<<setw(p->pro.name.size())<<p->pro.burst_time<<"|";
        p=p->next;
    }while(p!=ready->next);
    cout<<endl;
    p=ready->next;
    cout<<setw(12)<<"开始时刻"<<"|";
    do
    {
        cout<<setw(p->pro.name.size())<<p->pro.start_time<<"|";
        p=p->next;
    }while(p!=ready->next);
    cout<<endl;
    p=ready->next;
    cout<<setw(12)<<"完成时刻"<<"|";
    do
    {
        cout<<setw(p->pro.name.size())<<p->pro.finished_time<<"|";
        p=p->next;
    }while(p!=ready->next);
    cout<<endl;
    p=ready->next;
    cout<<setw(12)<<"周转时间"<<"|";
    do
    {
        cout<<setw(p->pro.name.size())<<p->pro.T<<"|";
        p=p->next;
    }while(p!=ready->next);
    cout<<"所有进程平均周转时间:"<<_T<<endl;
    p=ready->next;
    cout<<setw(12)<<"带权周转时间"<<"|";
    do
    {
        cout<<setw(p->pro.name.size())<<p->pro.w<<"|";
        p=p->next;
    }while(p!=ready->next);
    cout<<"所有进程平均带权周转时间:"<<_w<<endl;
    cout<<"----------------------------------------------------"<<endl;
}
void process_situation_time(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished)//查看某一时刻的进程情况
{
    int b,c,time,n=LD_length(ready);
    PCB *p=NULL;
    process pro;
    cout<<"执行的进程调度算法:"<<endl;
    cout<<"(1)FCFS / SPF / PSA / HRRN"<<endl;
    cout<<"(2)RR"<<endl;
    cout<<"(3)Auto"<<endl;
    do
    {
        cin>>b;
        if(b<1||b>3)
        {
            cout<<"(输入有误)(1-3)";
            c=1;
            getchar();
        }
        else
        {
            c=0;
        }
    }while(c==1);
    switch(b)
    {
        case 1:
            cout<<"时刻:";//选择时刻
            cin>>time;
            p=LD_get_front(ready);
            for(int i=0;i<n;i++)
            {
                if(p->pro.start_time<=time && p->pro.finished_time>time)
                {
                    pro=p->pro;
                    LD_rudui(run,pro);
                    delete_PCB(ready,pro);
                }
                if(p->pro.finished_time<=time)
                {
                    pro=p->pro;
                    LD_rudui(finished,pro);
                    delete_PCB(ready,pro);
                }
                p=p->next;
            }
            break;
        case 2:
            cout<<"时刻:";//选择时刻
            cin>>time;
            p=LD_get_front(ready);
            do
            {
                p->pro.runned_time=0;
                p=p->next;
            }while(p!=ready->next);
            while(time!=-1)
            {
                if(LD_empty(ready)==false)
                {
                    if(LD_empty(run)==false)
                    {
                        if(pro.runned_time==pro.burst_time)
                        {
                            LD_chudui(run,pro);
                            LD_rudui(finished,pro);
                        }
                        else
                        {
                            LD_chudui(run,pro);
                            LD_rudui(block,pro);
                        }
                    }
                    LD_chudui(ready,pro);
                    pro.runned_time = pro.runned_time + 1;
                    LD_rudui(run,pro);
                }
                else
                {
                    if(LD_empty(run)==false)
                    {
                        if(pro.runned_time==pro.burst_time)
                        {
                            LD_chudui(run,pro);
                            LD_rudui(finished,pro);
                        }
                        else
                        {
                            LD_chudui(run,pro);
                            LD_rudui(block,pro);
                        }
                    }
                    if(LD_empty(block)==false)
                    {
                        LD_chudui(block,pro);
                        pro.runned_time = pro.runned_time + 1;
                        LD_rudui(run,pro);
                    }
                }
                time = time - 1;
            }
            break;
        case 3:
            Auto(ready,run);
            break;
    }
}
void Copy(PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,PCB1 &ready_,PCB1 &run_,PCB1 &block_,PCB1 &finished_)//生成副本
{
    ready_=NULL;
    run_=NULL;
    block_=NULL;
    finished_=NULL;
    PCB *p;
    process pro;
    if(ready==NULL)
    {

    }
    else
    {
        p=ready->next;
        do
        {
            pro=p->pro;
            LD_rudui(ready_,pro);
            p=p->next;//指针后移
        }while(p!=ready->next);
    }
    if(run==NULL)
    {

    }
    else
    {
        p=run->next;
        do
        {
            pro=p->pro;
            LD_rudui(run_,pro);
            p=p->next;//指针后移
        }while(p!=run->next);
    }
    if(block==NULL)
    {

    }
    else
    {
        p=block->next;
        do
        {
            pro=p->pro;
            LD_rudui(block_,pro);
            p=p->next;//指针后移
        }while(p!=block->next);
    }
    if(finished==NULL)
    {

    }
    else
    {
        p=finished->next;
        do
        {
            pro=p->pro;
            LD_rudui(finished_,pro);
            p=p->next;//指针后移
        }while(p!=finished->next);
    }
}
void free_memory_init(Free_Memory_i1 &head)//构造一个空链表head
{
    head=new Free_Memory_i;
    head->next=NULL;
}
void free_memory_create(Free_Memory_i1 &head,free_memory_i &arg0)
{
    Free_Memory_i *temp_head,*New;//*temp_head是尾指针
    temp_head=head;//尾指针初始化,指向头结点

    Free_Memory_i *p=NULL,*q=NULL;
    Free_Memory_i *p_pre=NULL,*q_pre=NULL;

    if(temp_head->next==NULL)//如果只有头结点
    {
        New = new Free_Memory_i;
        New->fmi=arg0;
        New->next=temp_head->next;
        temp_head->next=New;
    }
    else
    {
        while(temp_head!=NULL && temp_head->next!=NULL)
        {
            if(temp_head->next->fmi.begin_address + temp_head->next->fmi.size == arg0.begin_address)//如果上空
            {
                p=temp_head->next;//p存上
                p_pre=temp_head;
            }
            if(temp_head->next->fmi.begin_address == arg0.begin_address + arg0.size)//如果下空
            {
                q=temp_head->next;//q存下
                q_pre=temp_head;
            }
            temp_head=temp_head->next;//指针后移
        }
        if(p==NULL && q==NULL)//如果上占下占
        {
            temp_head=head;//尾指针初始化,指向头结点
            New=new Free_Memory_i;
            New->fmi=arg0;
            New->next=temp_head->next;
            temp_head->next=New;
        }
        if(p!=NULL && q==NULL)//如果上空下占
        {
            p->fmi.size=p->fmi.size + arg0.size;
        }
        if(p==NULL && q!=NULL)//如果上占下空
        {
            q->fmi.begin_address=arg0.begin_address;
            q->fmi.size=arg0.size+q->fmi.size;
        }
        if(p!=NULL && q!=NULL)//如果上空下空
        {
            p->fmi.size=p->fmi.size + arg0.size + q->fmi.size;
            q_pre->next=q->next;
            delete q;
        }
    }
}
void free_memory_display(Free_Memory_i1 &head)//显示链表中所有结点的数据
{
    Free_Memory_i *temp_head;temp_head=head;
    cout<<"剩余内存:(总内存空间起始地址:"<<begin_address<<",大小:"<<size<<")"<<endl;
    while(temp_head!=NULL && temp_head->next!=NULL)
    {
        cout<<"起始地址:"<<temp_head->next->fmi.begin_address<<","<<"大小:"<<temp_head->next->fmi.size<<endl;
        temp_head=temp_head->next;//指针后移
    }
    if(temp_head==NULL)
    {
        cout<<""<<endl;
    }
}
Node1 Node_belong_to(Node1 &arg0,string &arg1)
{
    Node1 n=arg0->next;
    do
    {
        if(n->name==arg1)
        {
            return n;
        }
        n=n->next;
    }while(n!=arg0->next);
    return NULL;
}
void delete_Node(Node1 &arg0,string &arg1)
{
    Node1 n=arg0->next,n_pre=arg0;
    do
    {
        if(n->name==arg1)
        {
            n_pre->next=n->next;
            delete n;
            break;
        }
        n=n->next;
        n_pre=n_pre->next;
    }while(n!=arg0->next);
}
void IO_hardware_init(Node1 &CHCTs,Node1 &COCTs,Node1 &DCTs)//按无头结点来的
{
    Node *n=new Node;
    n->name=SDTs[0];//键盘
    n->parent=NULL;
    n->process=NULL;
    n->state=0;//空闲
    n->type='I';//键盘是输入设备
    n->waitinglist=NULL;
    n->next=n;
    DCTs=n;/*        */
    n=new Node;
    n->name=SDTs[1];//鼠标
    n->parent=NULL;
    n->process=NULL;
    n->state=0;//
    n->type='I';//鼠标是输入设备
    n->waitinglist=NULL;
    n->next=DCTs->next;
    DCTs->next=n;
    DCTs=n;/*        */
    n=new Node;
    n->name=SDTs[2];//显示器
    n->parent=NULL;
    n->process=NULL;
    n->state=0;//
    n->type='O';//显示器是输出设备
    n->waitinglist=NULL;
    n->next=DCTs->next;
    DCTs->next=n;
    DCTs=n;/*        */
    n=new Node;
    n->name=SDTs[3];//打印机
    n->parent=NULL;
    n->process=NULL;
    n->state=0;//
    n->type='O';//打印机是输出设备
    n->waitinglist=NULL;
    n->next=DCTs->next;
    DCTs->next=n;
    DCTs=n;/*        */
    n=new Node;
    n->name="控制器1";
    n->parent=NULL;
    n->process=NULL;
    n->state=0;
    n->waitinglist=NULL;
    n->next=n;
    COCTs=n;/*        */
    n=new Node;
    n->name="控制器2";
    n->parent=NULL;
    n->process=NULL;
    n->state=0;
    n->waitinglist=NULL;
    n->next=COCTs->next;
    COCTs->next=n;
    COCTs=n;/*        */
    n=new Node;
    n->name="控制器3";
    n->parent=NULL;
    n->process=NULL;
    n->state=0;
    n->waitinglist=NULL;
    n->next=COCTs->next;
    COCTs->next=n;
    COCTs=n;/*        */
    n=new Node;
    n->name="通道1";
    n->parent=NULL;
    n->process=NULL;
    n->state=0;
    n->waitinglist=NULL;
    n->next=n;
    CHCTs=n;/*        */
    n=new Node;
    n->name="通道2";
    n->parent=NULL;
    n->process=NULL;
    n->state=0;
    n->waitinglist=NULL;
    n->next=CHCTs->next;
    CHCTs->next=n;
    CHCTs=n;/*        */
    /*-----------------------*/
    DCTs->next->parent=COCTs->next;//键盘的父结点为控制器1
    DCTs->next->next->parent=COCTs->next;//鼠标的父结点为控制器1
    DCTs->next->next->next->parent=COCTs->next->next;//显示器的父结点为控制器2
    DCTs->parent=COCTs;//打印机的父结点为控制器3
    COCTs->next->parent=CHCTs->next;//控制器1的父结点为通道1
    COCTs->next->next->parent=CHCTs;//控制器2的父结点为通道2
    COCTs->parent=CHCTs;//控制器3的父结点为通道2
}
void IO_hardware_display(Node1 &CHCTs,Node1 &COCTs,Node1 &DCTs)
{
    Node *n=CHCTs->next;
    do
    {
        cout<<n->name<<" ";
        if(n->state==1)
        {
            cout<<"占用";
        }
        else
        {
            cout<<"空闲";
        }
        cout<<" 正在占用"<<n->name<<"的进程:";
        if(n->process==NULL)
        {
            cout<<" ";
        }
        else
        {
            cout<<n->process->pro.name<<" ";
        }
        cout<<"等待"<<n->name<<"的进程:";
        if(n->waitinglist==NULL)
        {

        }
        else
        {
            PCB *p=n->waitinglist->next;
            do
            {
                cout<<p->pro.name<<" ";
                p=p->next;
            }while(p!=n->waitinglist->next);
        }
        cout<<endl;
        Node *n1=COCTs->next;
        do
        {
            if(n1->parent->name==n->name)
            {
                cout<<setw(n->name.size())<<" "<<n1->name<<" ";
                if(n1->state==1)
                {
                    cout<<"占用";
                }
                else
                {
                    cout<<"空闲";
                }
                cout<<" 正在占用"<<n1->name<<"的进程:";
                if(n1->process==NULL)
                {
                    cout<<" ";
                }
                else
                {
                    cout<<n1->process->pro.name<<" ";
                }
                cout<<"等待"<<n1->name<<"的进程:";
                if(n1->waitinglist==NULL)
                {

                }
                else
                {
                    PCB *p=n1->waitinglist->next;
                    do
                    {
                        cout<<p->pro.name<<" ";
                        p=p->next;
                    }while(p!=n1->waitinglist->next);
                }
                cout<<endl;
                Node1 n2=DCTs->next;
                do
                {
                    int length=n->name.size()+n1->name.size();
                    if(n2->parent->name==n1->name)
                    {
                        cout<<setw(length)<<" "<<n2->name<<" ";
                        if(n2->state==1)
                        {
                            cout<<"占用";
                        }
                        else
                        {
                            cout<<"空闲";
                        }
                        cout<<" 正在占用"<<n2->name<<"的进程:";
                        if(n2->process==NULL)
                        {
                            cout<<" ";
                        }
                        else
                        {
                            cout<<n2->process->pro.name<<" ";
                        }
                        cout<<"等待"<<n2->name<<"的进程:";
                        if(n2->waitinglist==NULL)
                        {

                        }
                        else
                        {
                            PCB *p=n2->waitinglist->next;
                            do
                            {
                                cout<<p->pro.name<<" ";
                                p=p->next;
                            }while(p!=n2->waitinglist->next);
                        }
                        cout<<endl;
                    }
                    n2=n2->next;
                }while(n2!=DCTs->next);
            }
            n1=n1->next;
        }while(n1!=COCTs->next);
        n=n->next;//指针后移
        cout<<endl;
    }while(n!=CHCTs->next);
}
void help()
{
    cout<<"/*命令*/"<<endl;
    cout<<"C/c:创建一个进程"<<endl;
    cout<<"R/r:运行执行态进程"<<endl;
    cout<<"B/b:阻塞(将正在执行的程序阻塞,即插入阻塞队列尾部)"<<endl;
    cout<<"E/e:终止结束正在运行的进程"<<endl;
    cout<<"T/t:时间片到(将运行的进程装入就绪队列尾部,将下一个自动调度过来)"<<endl;
    cout<<"W/w:唤醒(将阻塞队列中的一个进程调度到就绪队列上,即阻塞队列头到就绪队列尾)"<<endl;
    cout<<"v:查看四个进程队列的情况"<<endl;
    cout<<"V:查看进程情况"<<endl;
    cout<<"s:查看剩余内存"<<endl;
    cout<<"D/d:为当前执行态的进程分配设备"<<endl;
    cout<<"F/f:为当前阻塞态的进程释放设备"<<endl;
    cout<<"G/g:新增设备"<<endl;
    cout<<"K/k:删除设备"<<endl;
    cout<<"I/i:新增控制器"<<endl;
    cout<<"L/l:删除控制器"<<endl;
    cout<<"J/j:新增通道"<<endl;
    cout<<"M/m:删除通道"<<endl;
    cout<<"N/n:查看I/O硬件情况"<<endl;
    cout<<"H/h:帮助"<<endl;
    cout<<"Q/q:退出"<<endl;
}
void menu(Node1 &CHCTs,Node1 &COCTs,Node1 &DCTs,PCB1 &ready,PCB1 &run,PCB1 &block,PCB1 &finished,Free_Memory_i1 &free_memory)
{
    char a;
    cout<<">";
    cin>>a;
    if(a=='C' || a=='c')
    {
        int i;
        process pro;
        cout<<"名:";
        cin>>pro.name;
        cout<<"所占内存空间大小(进程实际大小)(这个进程占有多少字节)(十进制):";//实验2的int型全局变量process_size
        cin>>pro.size;
        cout<<"给这个进程多少块:";
        cin>>pro.give_block;//仅在这give_block块里的页状态位为1//实验2的int型全局变量give_block
        cout<<"该进程到达时刻:";//递增
        cin>>pro.arrival_time;//递增
        cout<<"该进程所需服务时间:";
        cin>>pro.burst_time;
        cout<<"该进程的优先级:";
        cin>>pro.priority;
        pro.page_table_length = pro.size/block_size + 1;
        pro.page_table_FIFO=new page_i[pro.page_table_length];//页表
        pro.page_table_LRU=new page_i[pro.page_table_length];//页表
        pro.page_table_OPT=new page_i[pro.page_table_length];//页表
        PCB_init(pro);
        pro.FIFO=NULL;
        pro.LRU=NULL;
        pro.OPT=NULL;
        LD_init_(pro.FIFO);
        LD_init_(pro.LRU);
        LD_init_(pro.OPT);
        Free_Memory_i *temp_head=free_memory;
        Free_Memory_i *min_size,*min_size_pre;
        int d,flag=0;
        while(temp_head!=NULL && temp_head->next!=NULL)
        {
            if(temp_head->next->fmi.size > pro.size)
            {
                d=temp_head->next->fmi.size - pro.size;
                min_size=temp_head->next;
                min_size_pre=temp_head;
                flag=1;
                break;
            }
            temp_head=temp_head->next;//指针后移
        }
        while(temp_head->next!=NULL)
        {
            if(temp_head->next->fmi.size > pro.size  &&  temp_head->next->fmi.size - pro.size < d)
            {
                d=temp_head->fmi.size - pro.size;
                min_size=temp_head->next;
                min_size_pre=temp_head;
            }
            temp_head=temp_head->next;//指针后移
        }
        if(min_size->fmi.size <= 2+pro.size)
        {
            pro.begin_address=min_size->fmi.begin_address;
            pro.size=min_size->fmi.size;
            min_size_pre->next=min_size->next;//
            delete min_size;
            cout<<"你已成功创建了一个进程(名:"<<pro.name<<" 所占内存空间大小:"<<pro.size<<")"<<endl;
        }
        else
        {
            pro.begin_address=min_size->fmi.begin_address;
            free_memory_i temp=min_size->fmi;
            temp.begin_address=min_size->fmi.begin_address+pro.size;
            temp.size=min_size->fmi.size-pro.size;
            min_size_pre->next=min_size->next;//
            delete min_size;
            free_memory_create(free_memory,temp);//
            cout<<"你已成功创建了一个进程(名:"<<pro.name<<" 所占内存空间大小:"<<pro.size<<")"<<endl;
        }
        if(flag==0)
        {
            cout<<"进程创建失败(内存空间不足)"<<endl;
        }
        LD_rudui(ready,pro);
    }
    else if(a=='R' || a=='r')
    {
        run_process(run);//实验2
    }
    else if(a=='B' || a=='b')
    {
        if(LD_empty(run)==true)
        {
            cout<<"当前没有正在运行的进程"<<endl;
        }
        else
        {
            process pro;
            LD_chudui(run,pro);
            LD_rudui(block,pro);
            cout<<"名为"<<pro.name<<"的进程已被阻塞"<<endl;
        }
    }
    else if(a=='E' || a=='e')
    {
        if(LD_empty(run)==true)
        {
            cout<<"当前没有正在运行的进程"<<endl;
        }
        else
        {
            process pro;
            free_memory_i fri;
            LD_chudui(run,pro);
            fri.begin_address=pro.begin_address;
            fri.size=pro.size;
            free_memory_create(free_memory,fri);
            LD_init(run);
            cout<<"名为"<<pro.name<<"的进程已终止运行"<<endl;
        }
    }
    else if(a=='T' || a=='t')
    {
        if(LD_empty(run)==true)
        {
            cout<<"当前没有正在运行的进程"<<endl;
        }
        else
        {
            process pro;
            LD_chudui(run,pro);
            LD_rudui(ready,pro);
            cout<<"名为"<<pro.name<<"的进程已暂停运行"<<endl;
            LD_chudui(ready,pro);
            LD_rudui(run,pro);
        }
    }
    else if(a=='W' || a=='w')
    {
        if(LD_empty(block)==true)
        {
            cout<<"当前没有被阻塞的进程"<<endl;
        }
        else
        {
            process pro;
            LD_chudui(block,pro);
            LD_rudui(ready,pro);
            cout<<"名为"<<pro.name<<"的进程已被唤醒"<<endl;
        }
    }
    else if(a=='v')
    {
        PCB1 ready_=NULL,run_=NULL,block_=NULL,finished_=NULL;
        Copy(ready,run,block,finished,ready_,run_,block_,finished_);
        process_situation_time(ready,run,block,finished);
        cout<<"就绪态进程:";LD_display(ready);
        cout<<"执行态进程:";LD_display(run);
        cout<<"阻塞态进程:";LD_display(block);
        cout<<"已运行结束进程:";LD_display(finished);
        Copy(ready_,run_,block_,finished_,ready,run,block,finished);//回归时刻为0的时刻
    }
    else if(a=='V')
    {
        PCB1 ready_=NULL,run_=NULL,block_=NULL,finished_=NULL;
        Copy(ready,run,block,finished,ready_,run_,block_,finished_);
        process_situation(ready,run,block,finished);
        Copy(ready_,run_,block_,finished_,ready,run,block,finished);//回归时刻为0的时刻
    }
    else if(a=='s')
    {
        free_memory_display(free_memory);
    }
    else if(a=='D' || a=='d')
    {
        if(LD_empty(run)==true)
        {
            cout<<"当前无执行态进程"<<endl;
        }
        else
        {
            string str;
            process pro=run->pro;
            cout<<"为"<<pro.name<<"分配设备:"<<endl;
            cout<<"输入设备名:";
            cin>>str;
            Node *n=Node_belong_to(DCTs,str);
            if(n==NULL)
            {
                cout<<"该设备不存在"<<endl;
            }
            else
            {
                if(n->state==0)//若该设备空闲
                {
                    n->process=run;
                    n->state=1;
                    if(n->parent->state==0)
                    {
                        n->parent->process=run;
                        n->parent->state=1;
                        if(n->parent->parent->state==0)
                        {
                            n->parent->parent->process=run;
                            n->parent->parent->state=1;
                            LD_init(run);
                            LD_rudui(block,pro);
                            cout<<"已为"<<pro.name<<"分配"<<str<<","<<pro.name<<"现已从执行态转为阻塞态"<<endl;
                        }
                        else
                        {
                            if(n->parent->parent->waitinglist==NULL)
                            {
                                n->waitinglist->next=run;
                                n->parent->parent->waitinglist=run;
                            }
                            else
                            {
                                run->next=n->parent->parent->waitinglist->next;
                                n->parent->parent->waitinglist->next=run;
                                n->parent->parent->waitinglist=run;
                            }
                            LD_init(run);
                            LD_rudui(block,pro);
                            cout<<"为"<<pro.name<<"分配"<<str<<"失败("<<n->parent->parent->name<<"现为占用状态),"<<pro.name<<"现已从执行态转为阻塞态"<<endl;
                        }
                    }
                    else
                    {
                        if(n->parent->waitinglist==NULL)
                        {
                            run->next=run;
                            n->parent->waitinglist=run;
                        }
                        else
                        {
                            run->next=n->parent->waitinglist->next;
                            n->parent->waitinglist->next=run;
                            n->parent->waitinglist=run;
                        }
                        if(n->parent->parent->waitinglist==NULL)
                        {
                            run->next=run;
                            n->parent->parent->waitinglist=run;
                        }
                        else
                        {
                            run->next=n->parent->parent->waitinglist->next;
                            n->parent->parent->waitinglist->next=run;
                            n->parent->parent->waitinglist=run;
                        }
                        LD_init(run);
                        LD_rudui(block,pro);
                        cout<<"为"<<pro.name<<"分配"<<str<<"失败("<<n->parent->name<<"现为占用状态),"<<pro.name<<"现已从执行态转为阻塞态"<<endl;
                    }
                }
                else//若该设备占用(不可能出现设备占,其爸爸和爷爷空的情况)
                {
                    if(n->waitinglist==NULL)//如果链队为空
                    {
                        run->next=run;
                        n->waitinglist=run;
                    }
                    else//如果链队不为空
                    {
                        run->next=n->waitinglist->next;
                        n->waitinglist->next=run;
                        n->waitinglist=run;
                    }
                    if(n->parent->waitinglist==NULL)
                    {
                        run->next=run;
                        n->parent->waitinglist=run;
                    }
                    else
                    {
                        run->next=n->parent->waitinglist->next;
                        n->parent->waitinglist->next=run;
                        n->parent->waitinglist=run;
                    }
                    if(n->parent->parent->waitinglist==NULL)
                    {
                        run->next=run;
                        n->parent->parent->waitinglist=run;
                    }
                    else
                    {
                        run->next=n->parent->parent->waitinglist->next;
                        n->parent->parent->waitinglist->next=run;
                        n->parent->parent->waitinglist=run;
                    }
                    LD_init(run);
                    LD_rudui(block,pro);
                    cout<<"为"<<pro.name<<"分配"<<str<<"失败("<<n->name<<"现为占用状态),"<<pro.name<<"现已从执行态转为阻塞态"<<endl;
                }
            }
        }
    }
    else if(a=='F' || a=='f')//只能释放分配成功的
    {
        if(LD_empty(block)==true)
        {
            cout<<"当前无阻塞态进程"<<endl;
        }
        else
        {
            string str;
            process pro;
            cout<<"要释放的设备:";cin>>str;
            Node *n=Node_belong_to(DCTs,str);
            if(n==NULL || n->state==0)
            {
                cout<<"该设备不存在或未被占用"<<endl;
            }
            else
            {
                pro=n->process->pro;
                if(n->waitinglist!=NULL)
                {
                    PCB *p=n->waitinglist->next;
                    n->process=p;
                    if(n->waitinglist->next==n->waitinglist)
                    {
                        n->waitinglist=NULL;
                    }
                    else
                    {
                        n->waitinglist->next=p->next;
                        delete p;
                    }
                }
                else
                {
                    n->process=NULL;
                    n->state=0;
                    cout<<str<<"已释放"<<endl;
                }
                if(n->parent->process->pro.name==pro.name)
                {
                    if(n->parent->waitinglist!=NULL)
                    {
                        PCB *p=n->parent->waitinglist->next;
                        n->parent->process=p;
                        if(n->parent->waitinglist->next==n->parent->waitinglist)
                        {
                            n->parent->waitinglist=NULL;
                        }
                        else
                        {
                            n->parent->waitinglist->next=p->next;
                            delete p;
                        }
                    }
                    else
                    {
                        n->parent->process=NULL;
                        n->parent->state=0;
                    }
                }
                if(n->parent->parent->process->pro.name==pro.name)
                {
                    if(n->parent->parent->waitinglist!=NULL)
                    {
                        PCB *no=n->parent->parent->waitinglist->next;
                        n->parent->parent->process=no;
                        if(n->parent->parent->waitinglist->next==n->parent->parent->waitinglist)
                        {
                            n->parent->parent->waitinglist=NULL;
                        }
                        else
                        {
                            n->parent->parent->waitinglist->next=no->next;
                            delete no;
                        }
                    }
                    else
                    {
                        n->parent->parent->process=NULL;
                        n->parent->parent->state=0;
                    }
                }
                if(n->parent->waitinglist==NULL)
                {

                }
                else
                {
                    PCB *p=n->parent->waitinglist->next,*p_pre=n->parent->waitinglist;
                    if(n->parent->waitinglist->pro.name==pro.name)
                    {
                        delete n->parent->waitinglist;
                        n->parent->waitinglist=NULL;
                    }
                    else
                    {
                        while(p->pro.name!=n->parent->waitinglist->pro.name)
                        {
                            if(p->pro.name==pro.name)
                            {
                                p_pre->next=p->next;
                                delete p;
                                break;
                            }
                            p=p->next;
                            p_pre=p_pre->next;
                        }
                    }
                }
                if(n->parent->parent->waitinglist==NULL)
                {

                }
                else
                {
                    PCB *p=n->parent->parent->waitinglist->next,*p_pre=n->parent->parent->waitinglist;
                    if(n->parent->parent->waitinglist->pro.name==pro.name)
                    {
                        delete n->parent->parent->waitinglist;
                        n->parent->parent->waitinglist=NULL;
                    }
                    else
                    {
                        while(p->pro.name!=n->parent->parent->waitinglist->pro.name)
                        {
                            if(p->pro.name==pro.name)
                            {
                                p_pre->next=p->next;
                                delete p;
                                break;
                            }
                            p=p->next;
                            p_pre=p_pre->next;
                        }
                    }
                }
                delete_PCB(block,pro);
                LD_rudui(ready,pro);
            }
        }
    }
    else if(a=='G' || a=='g')
    {
        Node *n=new Node;
        string str;
        cout<<"新设备名:";cin>>n->name;
        if(Node_belong_to(DCTs,n->name)!=NULL)
        {
            cout<<"该设备已存在"<<endl;
            delete n;
        }
        else
        {
            cout<<"所属的控制器:";cin>>str;
            if(Node_belong_to(COCTs,str)!=NULL)
            {
                cout<<"设备类型:(I or O)";
                cin>>n->type;
                n->parent=Node_belong_to(COCTs,str);
                n->process=NULL;
                n->state=0;
                n->waitinglist=NULL;
                n->next=DCTs->next;
                DCTs->next=n;
                DCTs=n;
                cout<<"新增设备成功"<<endl;
            }
            else
            {
                cout<<"新增设备失败(该控制器不存在)"<<endl;
                delete n;
            }
        }
    }
    else if(a=='K' || a=='k')
    {
        string str;
        process pro;
        cout<<"需要删除的设备名:";cin>>str;
        Node *n=Node_belong_to(DCTs,str);
        if(n==NULL)
        {
            cout<<"删除失败(该设备不存在)"<<endl;
        }
        else if(str==SDTs[0] || str==SDTs[1] || str==SDTs[2] || str==SDTs[3])
        {
            cout<<"删除失败(系统设备不可删)"<<endl;
        }
        else if(n->process!=NULL || n->waitinglist!=NULL)
        {
            cout<<"删除失败(存在占用或等待该设备的进程)"<<endl;
        }
        else
        {
            delete_Node(DCTs,str);
            cout<<str<<"已从你的计算机上移除"<<endl;
        }
    }
    else if(a=='I' || a=='i')
    {
        Node *n=new Node;
        string str;
        cout<<"新控制器名:";cin>>n->name;
        if(Node_belong_to(COCTs,n->name)!=NULL)
        {
            cout<<"该控制器已存在"<<endl;
            delete n;
        }
        else
        {
            cout<<"所属的通道:";cin>>str;
            if(Node_belong_to(CHCTs,str)!=NULL)
            {
                n->parent=Node_belong_to(CHCTs,str);
                n->process=NULL;
                n->state=0;
                n->waitinglist=NULL;
                n->next=COCTs->next;
                COCTs->next=n;
                COCTs=n;
                cout<<"新增控制器成功"<<endl;
            }
            else
            {
                cout<<"新增控制器失败(该通道不存在)"<<endl;
                delete n;
            }
        }
    }
    else if(a=='L' || a=='l')
    {
        string str;
        process pro;
        cout<<"需要删除的控制器名:";cin>>str;
        Node *n=Node_belong_to(COCTs,str);
        if(n==NULL)
        {
            cout<<"删除失败(该控制器不存在)"<<endl;
        }
        else if(str=="控制器1" || str=="控制器2")
        {
            cout<<"删除失败(系统控制器不可删)"<<endl;
        }
        else if(n->process!=NULL || n->waitinglist!=NULL)
        {
            cout<<"删除失败(存在占用或等待该控制器的进程)"<<endl;
        }
        else
        {
            delete_Node(COCTs,str);
            cout<<str<<"已从你的计算机上移除"<<endl;
        }
    }
    else if(a=='J' || a=='j')
    {
        Node *n=new Node;
        cout<<"新通道名:";cin>>n->name;
        if(Node_belong_to(CHCTs,n->name)!=NULL)
        {
            cout<<"该通道已存在"<<endl;
            delete n;
        }
        else
        {
            n->parent=NULL;
            n->process=NULL;
            n->state=0;
            n->waitinglist=NULL;
            n->next=CHCTs->next;
            CHCTs->next=n;
            CHCTs=n;
            cout<<"新增通道成功"<<endl;
        }
    }
    else if(a=='M' || a=='m')
    {
        string str;
        process pro;
        cout<<"需要删除的通道名:";cin>>str;
        Node *n=Node_belong_to(CHCTs,str);
        if(n==NULL)
        {
            cout<<"删除失败(该通道不存在)"<<endl;
        }
        else if(str=="通道1" || str=="通道2")
        {
            cout<<"删除失败(系统通道不可删)"<<endl;
        }
        else if(n->process!=NULL || n->waitinglist!=NULL)
        {
            cout<<"删除失败(存在占用或等待该通道的进程)"<<endl;
        }
        else
        {
            delete_Node(CHCTs,str);
            cout<<str<<"已从你的计算机上移除"<<endl;
        }
    }
    else if(a=='N' || a=='n')
    {
        IO_hardware_display(CHCTs,COCTs,DCTs);
    }
    else if(a=='H' || a=='h')
    {
        help();
    }
    else if(a=='Q' || a=='q')
    {
        exit(0);
    }
    else
    {
        cout<<"错误的命令"<<endl;
    }
    choose_scheduling_algorithm(ready,run,block,finished);
    menu(CHCTs,COCTs,DCTs,ready,run,block,finished,free_memory);
}
main()
{
    Node1 CHCTs=NULL,COCTs=NULL,DCTs=NULL;//通道链表(存所有通道),控制器链表(存所有控制器),设备链表(存所有I/O设备)
    PCB1 ready=NULL,run=NULL,block=NULL,finished=NULL;//就绪队列,执行队列,阻塞队列,已运行结束队列(就绪态,执行态,阻塞态进程都在内存中)
    Free_Memory_i1 fm=NULL;//所有空闲的内存空间
    IO_hardware_init(CHCTs,COCTs,DCTs);
    free_memory_init(fm);
    cout<<"内存按固定大小分成块"<<endl;
    cout<<"块的大小(1块占多少字节)(十进制):";
    cin>>block_size;//输入1024
    cout<<"--------------------------------------"<<endl;
    cout<<"开辟一个新内存空间"<<endl;
    free_memory_i fmi;
    cout<<"起始块号:";
    cin>>fmi.begin_address;
    begin_address=fmi.begin_address;
    fmi.begin_address=fmi.begin_address*block_size;
    cout<<"占多少块:";
    cin>>fmi.size;
    size=fmi.size;
    bitmap_init();
    fmi.size=fmi.size*block_size;
    free_memory_create(fm,fmi);
    cout<<"已成功开辟一个新内存空间"<<endl;
    bitmap_display();//内存位示图显示
    LD_init(ready);
    LD_init(run);
    LD_init(block);
    LD_init(finished);
    menu(CHCTs,COCTs,DCTs,ready,run,block,finished,fm);
}
