#include <iostream>
#include <cmath>
using namespace std;
int *left1;
int remsize;
int remainder1;
void div(int input,int n,int poly,int m)
{
	cout<<input<<endl;
	cout<<n<<endl;
	cout<<poly<<endl;
	int j=1;
	int div;
	int temp;
	//int ptr=end+1;
	int begin=n-1;
	int last=begin;
	temp=input;
	temp=(temp >> (n-m));
	cout<<"input"<<temp<<endl;
	for(int i=1;i<=m;i++)
	{
//			int pos=last;
//			if(input&(1<<pos))
//			left1[i]=1;
//			else
//			left1[i]=0;
//			cout<<left1[i]<<" ";
			last--;
	}
	cout<<endl;
	do
	{
		int pos=m-1;
			if(temp & (1<<pos))
			div=1;
			else
			div=0;
			cout<<"quotient is "<<div<<endl;
			if(div==1)
			{
			remainder1=temp^poly;
			}
			else
			{
				remainder1=temp^(0);
			}
			cout<<"remainder is"<<remainder1<<endl;
			if(last>=0)
			{
					int pos=last;
			if(input & (1<<pos))
			remainder1 =(remainder1 << 1)|1;
			else
			remainder1 =(remainder1 << 1)|0;
			}
		cout<<"remainder is"<<remainder1<<endl;
		temp=remainder1;
		cout<<"input"<<temp<<endl;
			last--;
	}while(last>=-1);
}
int main()
{
	int input;
	cout<<"enter a no";
	cin>>input;
	int a=input;
    int counter = 0;
    while(a) {
        counter ++;
        a >>= 1;
 }
 

	int n;
	int i=1;

	int deg;
	cout<<"enter degree of polynomial"<<endl;
	cin>>deg;
	remsize=deg;
	int poly[100];
	int j=1;
	for(int i=deg;i>=0;i--)
	{
		cout<<"enter coefficient of x^"<<i<<endl;
		cin>>n;
		if(n==0)
		poly[j++]=0;
		else
		poly[j++]=1;
	}
	input=input << (deg);
	int poly_num=0;
	int num=deg+1;
	for(int i=deg+1;i>=1;i--)
	{
		int no=pow(2,(num-i));
		poly_num+=no*poly[i];
	}
	cout<<poly_num<<endl;
	div(input,counter+deg,poly_num,deg+1);
	input=input>>(deg) ;
	input=(input<<(deg))|(remainder1);
	cout<<"final input"<<input<<endl;
	


	do
	{
		cout<<"enter position no to change data(0 to n-1) or -1 if data not be changed"<<endl;
		cin>>n;
		if(n!=-1)
		{
		
			if(input &(1<<n))
			input &= ~(1 << n);
			else
			input |= (1 << n);
			
		}
	}while(n!=-1);
	div(input,counter+deg,poly_num,deg+1);	
	
	if(remainder1==0)
	cout<<"no error"<<endl;
	else
	cout<<"error occured"<<endl;
}
