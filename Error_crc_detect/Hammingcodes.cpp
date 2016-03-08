#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int data[100];
	int send[100]={0};
	int no,i=1;
	int n;
	cout<<"enter data(bit by bit -1 to terminate)"<<endl;
	do
	{
		cin>>n;
		if(n!=-1)
		data[i++]=n;
	}while(n!=-1);
	no=i-1;
	int r=log((double)no)/(log((double)2));
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
