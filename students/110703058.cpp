#include<iostream>
#include<cstdlib>
#include<cstring>
struct node
{
        int i;
        int j;
        int P;
        int D;
};      
int main()
{
        int round;
        scanf("%d",&round);
        int scale,scale1;
        scanf("%d %d\n",&scale,&scale1);
        char **arr;
        arr=(char**)malloc(scale*sizeof(char*));
        for(int i=0;i<scale;i++)
        {
                arr[i]=(char*)malloc(scale*sizeof(char));
        }
        int **step;
        step=(int**)malloc(scale*sizeof(int*));
        for(int i=0;i<scale;i++)
        {
                step[i]=(int*)malloc(scale*sizeof(int));
        }
        int Ax,Ay,Bx,By;
        struct node map[scale][scale];
        for(int i=0;i<scale;i++)
        {
                for(int j=0;j<scale;j++)
                {
                        scanf("%c%*c",&arr[i][j]);
                        map[i][j].P=0;
                        map[i][j].D=0;
                        if(arr[i][j]=='A')
                        {
                                Ax=i;
                                Ay=j;
                                step[i][j]=-1;
                        }
                        else if(arr[i][j]=='B')
                        {
                                Bx=i;
                                By=j;
                                step[i][j]=-1;
                        }
                        else if(arr[i][j]=='x')
                        {
                                step[i][j]=-2;
                        }
                        else
                        {
                                step[i][j]=-3;
                        }
                }
        }
        int Apoint,Bpoint;
        char who;
        scanf("%d\n",&Apoint);
        scanf("%d\n",&Bpoint);
        scanf("%c\n",&who);
        int X[]={1,-1,0,0};
        int Y[]={0,0,1,-1};
        int whox,whoy;
        int sx,sy;
        if(who=='A')
        {
                whox=Ax,sx=Ax;
                whoy=Ay,sy=Ay;
        }
        else if(who=='B')
        {
                whox=Bx,sx=Bx;
                whoy=By,sy=By;
        }
        struct node queue[scale*scale1];
        int rear=0,front=0,check=0;
        queue[rear].i = sx,queue[rear].j = sy;
        rear++;
        step[sx][sy]=0;
        int point=0;
        struct node max;
        for (;front<rear;front++)
        {
                check=0;
                sx = queue[front].i, sy = queue[front].j;
                for(int a=0;a<scale;a++)
                {
                        for(int b=0;b<scale;b++)
                        {
                                if(step[a][b]==-3)
                                        check++;
                        }
                }
                if(check!=0)
                {
                        for (int i=0;i<4;i++)
                        {
                                if(X[i]+sx>=0 && X[i]+sx<scale && Y[i]+sy>=0 && Y[i]+sy<scale && step[X[i]+sx][Y[i]+sy]==-3 && step[X[i]+sx][Y[i]+sy]!=-2 && step[X[i]+sx][Y[i]+sy] != -1)
                                {
                                        step[X[i]+sx][Y[i]+sy] = step[sx][sy] + 1;
                                        
                                        if(sx==whox && sy==whoy)
                                                map[X[i]+sx][Y[i]+sy].D=i+1;
                                        else
                                                map[X[i]+sx][Y[i]+sy].D=map[sx][sy].D;
                                        
                                        if(arr[X[i]+sx][Y[i]+sy]=='m')
                                        {   
                                                map[X[i]+sx][Y[i]+sy].P = map[sx][sy].P+1;
                                        }
                                        else if(arr[X[i]+sx][Y[i]+sy]=='n')
                                        {   
                                                map[X[i]+sx][Y[i]+sy].P = map[sx][sy].P-1;
                                        }
                                        else if(arr[X[i]+sx][Y[i]+sy]=='s')
                                        {   
                                                map[X[i]+sx][Y[i]+sy].P = map[sx][sy].P*2;
                                        }
                                        else if(arr[X[i]+sx][Y[i]+sy]=='t')
                                        {   
                                                map[X[i]+sx][Y[i]+sy].P = map[sx][sy].P/2;
                                        }
                                        else
                                        {   
                                                map[X[i]+sx][Y[i]+sy].P = map[sx][sy].P;
                                        }
                                        if(map[X[i]+sx][Y[i]+sy].P >= point)
                                        {
                                                point=map[X[i]+sx][Y[i]+sy].P;
                                                max.i=X[i]+sx;
                                                max.j=Y[i]+sy;
                                        }
                                        
                                        queue[rear].i = X[i]+sx, queue[rear].j = Y[i]+sy;
                                        rear++;
                                }
                        }
                }
                else
                {
                        break;
                }
        }
        if(map[max.i][max.j].D==2)
                printf("UP\n");
        if(map[max.i][max.j].D==1)
                printf("DOWN\n");
        if(map[max.i][max.j].D==3)
                printf("RIGHT\n");
        if(map[max.i][max.j].D==4)
                printf("LEFT\n");
}
