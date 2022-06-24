#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void print(int dir)
{
    if(dir==0)printf("UP");
    if(dir==1)printf("DOWN");
    if(dir==2)printf("LEFT");
    if(dir==3)printf("RIGHT");
}
int pointcounting(int point,int a,char playerr)//
{
    if(a==1)++point;
    if(a==-1)--point;
    if(a==2)point=point*2;
    if(a==-3)point=point/2;
    if(a==-4)point=-48763;//WALL
    if(playerr=='A'&&a==20)point=-48763;
    if(playerr=='B'&&a==10)point=-48763;
    
    return point;
}

int apt,bpt;
char player;
/*        num
A player  10
B player  20
. nothing 0
b bomb    -2
m +1      1
n -1      -1
s *2      2
t /2      -3
x wall    -4
*/
int main()
{
    
    int ifprint=0;//0ai¢DUAU¡LS?e¢DX
    int turn,sizex,sizey;
    scanf("%d",&turn);
    
    scanf("%d %d",&sizex,&sizey);
    int map[sizex][sizey];
    int timesb=0,timesm=0,timesn=0,timess=0,timest=0;//
    int Aplayerx,Aplayery,Bplayerx,Bplayery;
    
    for(int i=0;i<sizey;++i)//map[x][y]==map[j][i]
    {
        scanf("\n");
        for(int j=0;j<sizex;++j)
        {
            char ch;
            scanf("%c",&ch);
            if(j<sizex-1)scanf(" ");
            if(ch=='A'){map[j][i]=10;Aplayerx=j;Aplayery=i;}
            if(ch=='B'){map[j][i]=20;Bplayerx=j;Bplayery=i;}
            if(ch=='.')map[j][i]=0;
            if(ch=='b'){map[j][i]=-2;++timesb;}
            if(ch=='m'){map[j][i]=1;++timesm;}
            if(ch=='n'){map[j][i]=-1;++timesn;}
            if(ch=='s'){map[j][i]=2;++timess;}
            if(ch=='t'){map[j][i]=-3;++timest;}
            if(ch=='x'){map[j][i]=-4;}
            
        }
        
    }
    /*for(int i=0;i<sizey;++i)
    {
        for(int j=0;j<sizex;++j)
        {
        printf("%d ",map[j][i]);
        }
        printf("\n");
    }*/
    scanf("%d\n%d\n%c",&apt,&bpt,&player);
    //printf("%d %d %c",apt,bpt,player);
    //printf("%d %d %d %d",Aplayerx,Aplayery,Bplayerx,Bplayery);
    int startx,starty;
    if(player=='A'){startx=Aplayerx;starty=Aplayery;}
    if(player=='B'){startx=Bplayerx;starty=Bplayery;}
    
    int pointcount;
        if(player=='A')pointcount=apt;
        if(player=='B')pointcount=bpt;
    //printf("%d %d",startx,starty);
    
    /////
    if(turn<sizex)
    {
        int turn0=turn;
        
        int time2=1;//time2
        int b=sizex-turn0;//
        for(int a=turn0;a<sizex;++a)
        {
            time2=time2*2;
        }
        ///
        int curmax=pointcount;
        int point2=pointcount;
        int direct;
        if(startx+starty<sizex-1)//
        {
            for(int i=0;i<time2;++i)
            {
                int curx=startx;
                int cury=starty;
                int point1=point2;//point1
                int i2=i;
                for(int j=0;j<b;++j)
                {
                    int k=i2%2;
                    i2=i2/2;
                    if(k==0)
                    {
                        ++curx;
                        point1=pointcounting(point1,map[curx][cury],player);
                        if(map[curx][cury]==-2)
                        {
                            j=j+3;
                            i2=i2/8;
                        }
                    }
                    if(k==1)
                    {
                        ++cury;
                        point1=pointcounting(point1,map[curx][cury],player);
                        if(map[curx][cury]==-2)
                        {
                            j=j+3;
                            i2=i2/8;
                        }
                    }
                }
                if(point1>pointcount)
                {
                    pointcount=point1;
                    direct=i%2;//direction
                    
                }
            }
            //
            if(direct==0){printf("RIGHT ");ifprint=1;}
            if(direct==1){printf("DOWN ");ifprint=1;}
            //
        }
        //////////////////////////////////////////////////////////
        if(startx+starty>=sizex)//
        {
            
            for(int i=0;i<time2;++i)
            {
                int curx=startx;
                int cury=starty;
                int point1=point2;//point1
                int i2=i;
                for(int j=0;j<b;++j)
                {
                    int k=i2%2;
                    i2=i2/2;
                    if(k==0)
                    {
                        --curx;
                        point1=pointcounting(point1,map[curx][cury],player);
                        if(map[curx][cury]==-2)
                        {
                            j=j+3;
                            i2=i2/8;
                        }
                    }
                    if(k==1)
                    {
                        --cury;
                        point1=pointcounting(point1,map[curx][cury],player);
                        if(map[curx][cury]==-2)
                        {
                            j=j+3;
                            i2=i2/8;
                        }
                    }
                }
                if(point1>pointcount)
                {
                    pointcount=point1;
                    direct=i%2;//direction
                    
                }
            }
            //
            if(direct==0){printf("LEFT ");ifprint=1;}
            if(direct==1){printf("UP ");ifprint=1;}
            //
            
        }
        
    }
    /////
    
    
    
    ///////
    if(ifprint==0)
    {
        int curmax=pointcount;
        int point2=pointcount;
        int direct=4;
        for(int i=0;i<256;++i)
            {
                int curx=startx;
                int cury=starty;
                int point1=point2;//point1
                int i2=i;
                int k[4];
                int step1curx,step1cury,step2curx,step2cury,step3curx,step3cury,step4curx,step4cury;
                
                for(int j=0;j<4;++j)
                {
                    int ifdo=0;//ifdo checking invalid move
                    k[j]=i2%4;
                    i2=i2/4;
                    if(k[j]==0&&curx+1<sizex)
                    {
                        ++curx;
                        point1=pointcounting(point1,map[curx][cury],player);
                        ifdo=1;
                    }
                    if(k[j]==1&&cury+1<sizex)
                    {
                        ++cury;
                        point1=pointcounting(point1,map[curx][cury],player);
                        ifdo=1;
                    }
                    if(k[j]==2&&curx-1>=0)
                    {
                        --curx;
                        point1=pointcounting(point1,map[curx][cury],player);
                        ifdo=1;
                    }
                    if(k[j]==3&&cury-1>=0)
                    {
                        --cury;
                        point1=pointcounting(point1,map[curx][cury],player);
                        ifdo=1;
                    }
                    if(ifdo==0||point1==-48763)
                    {
                        point1=-87;
                        break;
                    }
                    if(j==0)
                    {
                        step1curx=curx;
                        step1cury=cury;
                    }
                    if(j==1)
                    {
                        step2curx=curx;
                        step2cury=cury;
                    }
                    if(j==2)
                    {
                        step3curx=curx;
                        step3cury=cury;
                    }
                    if(j==3)
                    {
                        step4curx=curx;
                        step4cury=cury;
                    }
                }
                //
                if((step1curx==step3curx&&step1cury==step3cury) )
				{
				    if(map[step3curx][step3cury]==1)--point1; 
				    if(map[step3curx][step3cury]==-1)++point1; 
				    if(map[step3curx][step3cury]==2)point1=point1/2; 
				    if(map[step3curx][step3cury]==-3)point1=point1*2; 
				    if(map[step3curx][step3cury]==-4)point1=-48763; 
				    
                } 
                if((step2curx==step4curx&&step2cury==step4cury) )
				{
				    if(map[step4curx][step4cury]==1)--point1; 
				    if(map[step4curx][step4cury]==-1)++point1; 
				    if(map[step4curx][step4cury]==2)point1=point1/2; 
				    if(map[step4curx][step4cury]==-3)point1=point1*2; 
				    if(map[step4curx][step4cury]==-4)point1=-48763; 
				    
                } 
                //
                if(point1>curmax)
                {
                    curmax=point1;
                    direct=i%4;//direction
                    
                }
                
            }
        if(direct==0){printf("RIGHT ");ifprint=1;}
        if(direct==1){printf("DOWN ");ifprint=1;}
        if(direct==2){printf("LEFT ");ifprint=1;}
        if(direct==3){printf("UP ");ifprint=1;}
    }
    
    if(ifprint==0)
    {
        if(startx+1<sizex&&map[startx+1][starty]==2){printf("RIGHT ");ifprint=1;}
        else if(starty+1<sizex&&map[startx][starty+1]==2){printf("DOWN ");ifprint=1;}
        else if(startx-1>0&&map[startx-1][starty]==2){printf("LEFT ");ifprint=1;}
        else if(starty-1>0&&map[startx][starty-1]==2){printf("UP ");ifprint=1;}
        else if(startx+1<sizex&&map[startx+1][starty]==1){printf("RIGHT ");ifprint=1;}
        else if(starty+1<sizex&&map[startx][starty+1]==1){printf("DOWN ");ifprint=1;}
        else if(startx-1>0&&map[startx-1][starty]==1){printf("LEFT ");ifprint=1;}
        else if(starty-1>0&&map[startx][starty-1]==1){printf("UP ");ifprint=1;}
        
    }
    
    if(ifprint==0)//
    {
    	srand(time(NULL));
        int random=rand()%8;
        if(random==0)
        {
            if(startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
            else if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
            else if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
        }
        if(random==1)
        {
            if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
            else if(startx>0&&startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            else if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
        }
        if(random==2)
        {
            if(startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            else if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
            else if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
        }
        if(random==3)
        {
            if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
            else if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
            else if(startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
        }
        if(random==4)
        {
            if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
            else if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
            else if(startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            
        }
        if(random==5)
        {
            if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
            else if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
            else if(startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            
        }
        if(random==6)
        {
            if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
            else if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
            else if(startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            
        }
        if(random==7)
        {
            if(starty<sizex-1&&map[startx][starty+1]>=0&&map[startx][starty+1]<10){printf("DOWN ");ifprint=1;}
            else if(startx<sizex-1&&map[startx+1][starty]>=0&&map[startx+1][starty]<10){printf("RIGHT ");ifprint=1;}
            else if(starty>0&&map[startx][starty-1]>=0&&map[startx][starty-1]<10){printf("UP ");ifprint=1;}
            else if(startx>0&&map[startx-1][starty]>=0&&map[startx-1][starty]<10){printf("LEFT ");ifprint=1;}
            
        }
    }
    if(ifprint==0)
    {
    	if(map[startx][starty+1]!=-4&&map[startx][starty+1]!=10&&map[startx][starty+1]!=20){printf("DOWN ");ifprint=1;}
    	if(map[startx][starty-1]!=-4&&map[startx][starty-1]!=10&&map[startx][starty-1]!=20){printf("UP ");ifprint=1;}
    	if(map[startx+1][starty]!=-4&&map[startx+1][starty]!=10&&map[startx+1][starty]!=20){printf("RIGHT ");ifprint=1;}
    	if(map[startx-1][starty]!=-4&&map[startx-1][starty]!=10&&map[startx-1][starty]!=20){printf("LEFT ");ifprint=1;}
    	
	}
    return 0;
}
