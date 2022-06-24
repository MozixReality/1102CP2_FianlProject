#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

char map[21][21]={};
int M=0,N=0,Round=0;
int arr[4]={0};

bool valid(int x,int y)
{
    if( x>=0 && x<M && y>=0 && y<N && map[x][y]!='x' && map[x][y]!='A' && map[x][y]!='B' )
        return 1;
    else
        return 0;
}

int count_grade(int x, int y, int score1)
{
    int ans=score1;
    if(map[x][y]=='m')
        ans+=1;
    else if(map[x][y]=='n')
        ans-=1;
    else if(map[x][y]=='s' && ans!=0)
        ans*=2;
    else if(map[x][y]=='t' && ans!=0)
        ans/=2;
    return ans;
}

void close(int ax,int ay, int bx, int by, char me)
{
    if(me=='A')
    {
        if( ax>bx && ax-bx!=1)
            arr[0]=1;
        if( ay>by && ay-by!=1)
            arr[1]=1;
        if( ax<bx && ax-bx!=-1)
            arr[2]=1;
        if( ay<by && ay-by!=-1)
            arr[3]=1;
    }
    else
    {
        if( bx>ax && bx-ax!=1)
            arr[0]=1;
        if( by>ay && by-ay!=1)
            arr[1]=1;
        if( bx<ax && bx-ax!=-1)
            arr[2]=1;
        if( by<ay && by-ay!=-1)
            arr[3]=1;
    }
    return;
}


int process0(int x,int y, int score2)
{
    int i,tmp,grade1=0,max=INT_MIN;
    int dirx[4]={-1,0,1,0}; 
    int diry[4]={0,-1,0,1};
    for(i=0;i<4;i++)
    {
        if( valid(dirx[i]+x,diry[i]+y) )
            grade1=count_grade(x+dirx[i], y+diry[i], score2);
        if(grade1>max)
        {
            max=grade1;
            tmp=i;
        }
        else if(max==grade1)
            tmp=5;
    }
    return tmp;

}
int process1(int x, int y, int score2)
{
    int i;
    int grade1[4]={0};
    int dirx[4]={-1,0,1,0};  
    int diry[4]={0,-1,0,1};
    for(i=0;i<4;i++)
    {
        if( valid(dirx[i]+x,diry[i]+y) )
            grade1[i]=count_grade(x+dirx[i], y+diry[i], score2);
    }
    return *grade1;
}

int processA(int x, int y, int *grade1)
{
    int i,tmp,max=INT_MIN;
    int grade2=0;
    int dirx[9]={-1,-2,-1,0,1,2,1,0,-1};
    int diry[9]={1,0,-1,-2,-1,0,1,2,1};
    tmp=6;
    for(i=0;i<3;++i)
    {
        if( arr[0]==1 && valid( (x-1),y) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[0]);
            if(grade2>max);
            {
                max=grade2;
                tmp=0;
            }
        }
    }
    for(i=2;i<5;++i)
    {
        if( arr[1]==1 && valid(x,(y-1)) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[1]);
            if(grade2>max)
            {
                max=grade2;
                tmp=1;
            }
        }
    }
    for(i=4;i<7;++i)
    {
        if( arr[2]==1 && valid((x+1),y) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[2]);
            if(grade2>max)
            {
                max=grade2;
                tmp=2;
            }
        }
    }
    for(i=6;i<9;++i)
    {
        if( arr[3]==1 && valid(x,(y+1)) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[3]);
            if(grade2>max)
            {
                max=grade2;
                tmp=3;
            }
        }
    }
    return tmp;
}

int process2(int x, int y, int *grade1)
{
    int i,tmp,max=INT_MIN;
    int grade2=0;
    int dirx[9]={-1,-2,-1,0,1,2,1,0,-1};
    int diry[9]={1,0,-1,-2,-1,0,1,2,1};
    for(i=0;i<3;++i)
    {
        if( valid( (x-1),y) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[0]);
            if(grade2>max);
            {
                max=grade2;
                tmp=0;
            }
        }
    }
    for(i=2;i<5;++i)
    {
        if( valid(x,(y-1)) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[1]);
            if(grade2>max)
            {
                max=grade2;
                tmp=1;
            }
        }
    }
    for(i=4;i<7;++i)
    {
        if( valid((x+1),y) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[2]);
            if(grade2>max)
            {
                max=grade2;
                tmp=2;
            }
        }
    }
    for(i=6;i<9;++i)
    {
        if( valid(x,(y+1)) && valid(dirx[i]+x,diry[i]+y) )
        {
            grade2=count_grade(x+dirx[i],y+diry[i],grade1[3]);
            if(grade2>max)
            {
                max=grade2;
                tmp=3;
            }
        }
    }
    return tmp;
}


int main(void)
{
    int scoreA,scoreB,i,j,ans=0,ax,ay,bx,by;
    int score1[4]={0};
    char role;
    scanf("%d\n",&Round);
    scanf("%d %d\n",&M,&N);
    for(i=0;i<M;++i)
    {
        for(j=0;j<N;++j)
            scanf("%c%*c",&map[i][j]);    
    }
    scanf("%d\n",&scoreA);
    scanf("%d\n",&scoreB);
    scanf("%c",&role);
    for(i=0;i<M;++i)
    {
        for(j=0;j<N;++j)
        {
            if(map[i][j]== 'A')
            {
                ax=i;
                ay=j;
            }
            if(map[i][j]== 'B')
            {
                bx=i;
                by=j;
            }
        }
    }

    if(role=='A')
    {
        close(ax,ay,bx,by,'A');
        *score1=process1(ax,ay,scoreA);
        ans=processA(ax,ay,score1);
        if(ans==6)
        {
            ans=process0(ax,ay,scoreA);
            if(ans==5)
                ans=process2(ax,ay,score1);
        }
    }
    else if(role=='B')
    {
        close(ax,ay,bx,by,'B');
        *score1=process1(bx,by,scoreB);
        ans=processA(bx,by,score1);
        if(ans==6)
        {
            ans=process0(bx,by,scoreB);
            if(ans==5)
                ans=process2(bx,by,score1);
        }
    }
    switch(ans)
    {
        case 0:
            printf("UP\n");
            break;
        case 1:
            printf("LEFT\n");
            break;
        case 2:
            printf("DOWN\n");
            break;
        default: printf("RIGHT\n");            
    }
    return 0;
}
