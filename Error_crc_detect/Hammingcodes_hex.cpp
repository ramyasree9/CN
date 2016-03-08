#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
int fill(char ch[],int l,int data[])
{
	int n=1;
	int cur=1;
	for(int i=0;i<l;i++)
	{
		switch(ch[i])
		{
			case '0':
				data[cur]=0;
				data[cur+1]=0;
				data[cur+2]=0;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case '1':
				data[cur]=0;
				data[cur+1]=0;
				data[cur+2]=0;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;
			case '2':
				data[cur]=0;
				data[cur+1]=0;
				data[cur+2]=1;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case '3':
				data[cur]=0;
				data[cur+1]=0;
				data[cur+2]=1;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;	
			case '4':
				data[cur]=0;
				data[cur+1]=1;
				data[cur+2]=0;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case '5':
				data[cur]=0;
				data[cur+1]=1;
				data[cur+2]=0;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;
			case '6':
				data[cur]=0;
				data[cur+1]=1;
				data[cur+2]=1;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case '7':
				data[cur]=0;
				data[cur+1]=1;
				data[cur+2]=1;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;
			case '8':
				data[cur]=1;
				data[cur+1]=0;
				data[cur+2]=0;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case '9':
				data[cur]=1;
				data[cur+1]=0;
				data[cur+2]=0;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;
			case 'A':
				data[cur]=1;
				data[cur+1]=0;
				data[cur+2]=1;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case 'B':
				data[cur]=1;
				data[cur+1]=0;
				data[cur+2]=1;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;
			case 'C':
				data[cur]=1;
				data[cur+1]=1;
				data[cur+2]=0;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case 'D':
				data[cur]=1;
				data[cur+1]=1;
				data[cur+2]=0;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;
			case 'E':
				data[cur]=1;
				data[cur+1]=1;
				data[cur+2]=1;
				data[cur+3]=0;
				cur=cur+4;
				n=cur-1;
				break;
			case 'F':
				data[cur]=1;
				data[cur+1]=1;
				data[cur+2]=1;
				data[cur+3]=1;
				cur=cur+4;
				n=cur-1;
				break;
		}
	}
	return n;
}
int main()
{
	int data[100];
	int send[100]={0};
	int no,i=1;
	int n;
	char ch[100];
	cout<<"enter data"<<endl;
	cin>>ch;
	no=fill(ch,strlen(ch),data);
	
	int r=log((double)no);
	cout<<r<<endl;
	int k=no+r+1;
	while(k>pow(2,r))
	{
		r++;
		k=no+r+1;
	}
	cout<<"final r"<<r<<endl;
	int j=0;
	for(j=1;j<=r;j++)
	{
		int pos=pow(2,j-1);
		send[pos]=-1;
	}
	k=1;
	for(i=1;i<=(no+r);i++)
	{
		if(send[i]!=-1)
		send[i]=data[k++];
	}
	for(i=1;i<=r;i++)
	{
		int c=0;
		int pos=pow(2,i-1);
		cout<<":pos"<<i-1<<endl;
		for(j=1;j<=(no+r);j++)
		{
			
//			if(j&(1<<(i-1))!=0)
			if((j&pos)!=0)
			{
				if(send[j]==1)
				{
					cout<<j<<" ";
					c++;
				}
			}
		}
		if(c%2==0)
		send[pos]=0;
		else
		send[pos]=1;
		cout<<"parity: "<<send[pos]<<endl;
	}
	for(i=1;i<=(no+r);i++)
	cout<<send[i]<<" ";
	cout<<endl;
	int pos;
	cout<<"enter a position to change the bit"<<endl;
	cin>>pos;
	if(send[pos]==1)
	send[pos]=0;
	else
	send[pos]=1;
	int errpos=0;
	for(i=1;i<=r;i++)
	{
		int c=0;
		int pos=pow(2,i-1);
		cout<<":pos"<<i-1<<endl;
		for(j=1;j<=(no+r);j++)
		{
			
//			if(j&(1<<(i-1))!=0)
			if((j&pos)!=0)
			{
				if(send[j]==1)
				{
					cout<<j<<" ";
					c++;
				}
			}
		}
		if(c%2!=0)
		{
			cout<<"error "<<endl;
			errpos+=pos;
		}
		
	}
	cout<<"bit at pos "<<errpos<<" is changed"<<endl;
}
