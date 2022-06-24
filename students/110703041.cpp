#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int T,M,N,maxx,f;
char arr[20][21];
int prr[20][20]={0};

int max(int a,int b)
{
	if(a>b)
		return a;
	else return b;
}

void setZero()
{
	maxx=0;
	for(int i=0;i<M;++i)
	{
		for(int j=0;j<N;++j)
			prr[i][j]=0;
	}
}

void move(int c,int R,int X,int Y)
{
	if(X>=0 && X<M && Y>=0 && Y<N && R<T && prr[X][Y]>=0)
	{
		int temp;
		if(arr[X][Y]=='x' || arr[X][Y]=='A'||arr[X][Y]=='B')
			maxx=max(maxx,c);
		else if(arr[X][Y]=='.')
			temp=c;
		else if(arr[X][Y]=='m')
			temp=c+1;
		else if(arr[X][Y]=='s')
			temp=c*2;
		else if(arr[X][Y]=='n')
			temp=c-1;
		else if(arr[X][Y]=='t')
			temp=c/2;
		else if(arr[X][Y]=='b')
			R=R+3;;
		prr[X][Y]=-1;
		
		if(arr[X][Y]!='x'|| arr[X][Y]=='A'||arr[X][Y]=='B')
		{
			move(temp,R+1,X+1,Y);
			move(temp,R+1,X-1,Y);
			move(temp,R+1,X,Y+1);
			move(temp,R+1,X,Y-1);
		}
	}
	else if(X>=0 && X<M && Y>=0 && Y<N && R==T && prr[X][Y]>=0)
	{
		if(arr[X][Y]=='x'||arr[X][Y]=='.'||arr[X][Y]=='b'||arr[X][Y]=='A'||arr[X][Y]=='B')
			maxx=max(maxx,c);
		else if(arr[X][Y]=='m')
			maxx=max(maxx,c+1);
		else if(arr[X][Y]=='s')
			maxx=max(maxx,c*2);
		else if(arr[X][Y]=='n')
			maxx=max(maxx,c-1);
		else if(arr[X][Y]=='t')
			maxx=max(maxx,c/2);
	}
}

void random(int g,int x,int y)
{
	if(g==0)
	{
		if(x<0 || x>=M || y-1<0 || y-1>=N||arr[x][y-1]=='x'||arr[x][y-1]=='A'||arr[x][y-1]=='B')
			random((g+1)%4,x,y);
		else
			f=0;
	}
	else if (g==1)
	{
		if(x<0 || x>=M || y+1<0 || y+1>=N||arr[x][y+1]=='x'||arr[x][y+1]=='A'||arr[x][y+1]=='B')
			random((g+1)%4,x,y);
		else
			f=1;
	}
	else if (g==2)
	{
		if(x-1<0 || x-1>=M || y<0 || y>=N||arr[x-1][y]=='x'||arr[x-1][y]=='A'||arr[x-1][y]=='B')
			random((g+1)%4,x,y);
		else
			f=2;
	}
	else if (g==3)
	{
		if(x+1<0 || x+1>=M || y<0 || y>=N||arr[x+1][y]=='x'||arr[x+1][y]=='A'||arr[x+1][y]=='B')
			random((g+1)%4,x,y);
		else 
			f=3;
	}
}

int main(void) 
{
	//讀入
	scanf("%d\n%d\n%d\n",&T,&M,&N);
	
	for(int i=0;i<M;++i)
	{
		for(int j=0;j<N;++j)
			scanf("%c\n",&arr[i][j]);
	}
	
	int Asc,Bsc;
	scanf("%d\n%d\n",&Asc,&Bsc);
	
	char me[2];
	scanf("%s",me);
	
	int x,y;
	for(int i=0;i<M;++i)
	{
		for(int j=0;j<N;++j)
		{
			if(arr[i][j]==me[0])
			{
				x=i;
				y=j;
			}
		}
	}
	//
	
	int z,l=-10000,r=-10000,u=-10000,d=-10000,C,ran,fn;
	unsigned seed = (unsigned)time(NULL);
    srand(seed);
	char ans[4][10]={"LEFT","RIGHT","UP","DOWN"};
	
	if(me[0]=='A')
	{
		C=Asc;
		T=(T/2)+1;
	}
	else if(me[0]=='B')
	{
		C=Bsc;
		T=T/2;
	}
	
	//回數
	T=T%7;
	if(T==0)
		T=T+7;
	T=8-T;
	//
	
	z=1;
	if(x>=0 && x<M && y-1>=0 && y-1<N && arr[x][y-1]!='x' && arr[x][y-1]!='A' && arr[x][y-1]!='B')
	{
		setZero();
		prr[x][y]=-1;
		move(C,z,x,y-1);
		l=maxx;
	}
	if(x>=0 && x<M && y+1>=0 && y+1<N && arr[x][y+1]!='x' && arr[x][y+1]!='A' && arr[x][y+1]!='B')
	{
		setZero();
		prr[x][y]=-1;
		move(C,z,x,y+1);
		r=maxx;
	}
	if(x-1>=0 && x-1<M && y>=0 && y<N && arr[x-1][y]!='x' && arr[x-1][y]!='A' && arr[x-1][y]!='B')
	{
		setZero();
		prr[x][y]=-1;
		move(C,z,x-1,y);
		u=maxx;
	}
	if(x+1>=0 && x+1<M && y>=0 && y<N && arr[x+1][y]!='x' && arr[x+1][y]!='A' && arr[x+1][y]!='B')
	{
		setZero();
		prr[x][y]=-1;
		move(C,z,x+1,y);
		d=maxx;
	}
	
	if(r>l && r>u && r>d)
		printf("%s\n",ans[1]);
	else if(l>r && l>u && l>d)
		printf("%s\n",ans[0]);
	else if(u>r && u>l && u>d)
		printf("%s\n",ans[2]);
	else if(d>r && d>l && d>u)
		printf("%s\n",ans[3]);
	
	//如果有相同
	else
	{
		if(arr[x][y-1]=='m'||arr[x][y-1]=='s')
			printf("%s\n",ans[0]);
		else if(arr[x][y+1]=='m'||arr[x][y+1]=='s')
			printf("%s\n",ans[1]);
		else if(arr[x-1][y]=='m'||arr[x-1][y]=='s')
			printf("%s\n",ans[2]);
		else if(arr[x+1][y]=='m'||arr[x+1][y]=='s')
			printf("%s\n",ans[3]);
		else
		{
			ran=rand()%4;
			random(ran,x,y);
			printf("%s\n",ans[f]);
		}
	}
	
	return 0;
}

