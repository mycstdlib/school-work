#include<iostream>
 
using namespace std;

int main()
{
	int won[31][31]={};
	int man[31][31]={};
	int tr[31]={};//���Գɹ������ţ�
	int fa[31]={};//Ů�Գɹ������ţ�
	int N=0,l=0;//�������ݣ�
	cin>>N;
	for(int i=0;i<N;i++)
	{
	   for(int j=0;j<N;j++)
		   {cin>>man[i][j];}
	   //cout<<endl;
	}
	for(int i=0;i<N;i++)
	{
	   for(int j=0;j<N;j++)
		   {cin>>won[i][j];}
	   //cout<<endl;
	}//�������룻
	while(l!=N)//�����Ѿ������l;
	{
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
			{
				if(man[i][j]!=0 && !tr[i])
				{
					int x1=0;
					x1=man[i][j]-1;
					if(fa[x1]==0)
					{
						l++;
						tr[i]=man[i][j];
						fa[x1]=i+1;
						j=N;
					}
					else
					{
						int news=0,old=0;
						for(int f=0;f<N;f++)
							{
								if(won[x1][f]==i+1)
							    {news=f;}
							    else{}
							    if(won[x1][f]==fa[x1])
								{old=f;}
								else{}
						    }
						if(news<old)
						{
							int w=(fa[x1])-1;
							tr[w]=0;
							fa[x1]=i+1;
							tr[i]=man[i][j];
							j=N;
						}
						else{man[i][j]=0;}
					}
				}
			}
		
	}
	//i+1;is the real number;
	
	for(int i=0;i<N;i++)
	{cout<<tr[i]<<" ";} cout<<endl;
	//system("pause");
  return 0;
}
