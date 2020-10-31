#include<stdio.h>
#include<math.h>
int number(char xx[]);//判断输入数字个数，及是否存在非数字字符
double num[3];//存三角形的三条边
int main()
{
	char xx[1000];
	while(gets(xx))
	{
		printf("\n三角形问题白盒测试,针对主函数做白盒测试\n请输入三个数:\n");
		int res=number(xx);
		if(res==0)
		{
			printf("\n存在非数字，请重新输入");
		}
		else{
			if(res==-1)
				printf("\n不足三个数，请重新输入");
			else if(res==-2) 
				printf("\n超过三个数，请重新输入");
			else{
		
				if((num[0]+num[1]<=num[2])||(num[1]+num[2]<=num[0])||(num[1]+num[2]<=num[0]))//两边只和小于等于第三边
				{
					printf("\n构不成三角形,请重新输入");
				}
				else 
				{
					//计算周长
					printf("\n周长是：%f",num[0]+num[1]+num[2]);
					if((num[0]==num[1])||(num[0]==num[2])||(num[1]==num[2]))
					{
						if(num[0]==num[1]&&num[0]==num[2])
							printf("\t此三角形是等边三角形");
						else 
							printf("\t此三角形是等腰三角形");
					}
					else 
						printf("\t此三角形是普通三角形");
				}
			}
		}
		printf("\n\n\n");
	}
	return 0;
}

int number(char xx[])//具体内容略
{
	int ch;
	int count=0;
	int i=0;
	int increment; 
	double tokenNum;// 声明小数的精度计数器
	while(ch!='\0') {
		tokenNum=0;
		increment=0;          
		ch = xx[i];
		if(ch == ' ')  
			ch=xx[++i];
		else if(ch<='9'&&ch>='0') {
			tokenNum = (double)(ch - '0');     			
			i++;
			ch = xx[i];          
			while(ch<='9'&&ch>='0') {
				tokenNum = tokenNum * 10 + (double)(ch - '0'); 				
				i++;
				ch = xx[i];      
			}	
			
			if(ch == '.') {// 如果是定点实数,34.5
				int tailNum=0;
				ch = xx[++i];
				while(ch<='9'&&ch>='0') {
					tailNum = tailNum * 10 + (ch-'0');
					i++;
					ch = xx[i];
					increment ++;
				}
				tokenNum = tokenNum + (tailNum/(double)pow(10,increment));
			}
			if(ch == 'e' || ch == 'E')// 识别浮点数(带e/E的)
			{
				int tailNum=0;
				ch = xx[++i];
				if(ch == '-')
				{                                // if form is 23E-23
					i++;
					ch = xx[i];
					while(ch<='9'&&ch>='0')
					{
						tailNum = tailNum * 10 + (ch - '0');
						ch = xx[++i];
					}
					tokenNum /= pow(10,tailNum);
				}
				else if(ch == '+')
				{                           // if form is 23E+23
					ch = xx[++i];
					while(ch<='9'&&ch>='0') {
						tailNum = tailNum * 10 + (ch - '0');
						i++;
						ch = xx[i];
					}
					tokenNum *= pow(10,tailNum);
				}
				else if(ch<='9'&&ch>='0')
				{                         // if form is like 23E23
					do {
						tailNum = tailNum * 10 + (ch - '0');
						i++;
						ch = xx[i];
					}while(ch<='9'&&ch>='0');
					tokenNum *= pow(10,tailNum);
				}	
			}
			num[count++]=tokenNum;
			if(count>3)
				return -2;//超过三个数
		}      //end else if   
		else 
			return 0;//存在非数字
	}
	if(count<3)
		return -1;//不足三个数
	else return 1;//符合要求
}



