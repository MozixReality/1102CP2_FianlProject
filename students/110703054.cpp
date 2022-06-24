#include <stdio.h>
#include <stdlib.h>

typedef struct{
        int x;
        int y;
        int point;
        int dir;
        int step;
}state;

int bfs(int round,int n_row,int c_col,int score_A,int score_B,char role,char** table);

int main(){
        int ax,ay,bx,by,round, n_row, n_col, score_A, score_B;
        char role;
        char** table;
        scanf("%d\n", &round);
        scanf("%d %d\n", &n_row, &n_col);

        table = (char**) malloc(n_row * sizeof(char*));

        for(int i = 0 ; i < n_row ; i++){
                table[i] = (char*) malloc(n_col * sizeof(char));
        }

        for(int i = 0 ; i < n_row ; i++){
                for(int j = 0 ; j < n_col ; j++){
                        scanf("%c%*c", &table[i][j]);
                        if(table[i][j]=='A')
                        {
                                ax=i;
                                ay=j;
                        }
                        if(table[i][j]=='B')
                        {
                                bx=i;
                                by=j;
                        }

                }
        }
        scanf("%d\n", &score_A);
        scanf("%d\n", &score_B);
        scanf("%c", &role);

        int ret;
        ret=bfs( round, n_row, n_col, score_A, score_B, role,table);
        if(ret==0)
                printf("RIGHT\n");
        if(ret==1)
                printf("DOWN\n");
        if(ret==2)
                printf("LEFT\n");
        if(ret==3)
                printf("UP\n");
        return 0;
}
int bfs(int round,int n_row,int n_col,int score_A,int score_B,char role,char** table)
{
        int dx[]={0,1,0,-1};
        int dy[]={1,0,-1,0};
        int max=-1000,maxdir=-1,ax,ay,bx,by;
        int check[n_row][n_col];
        state queue[200000];
        for(int i = 0 ; i < n_row ; i++){
                for(int j = 0 ; j < n_col ; j++){
                        check[i][j]==0;
                }
        }
        for(int i = 0 ; i < n_row ; i++){
                for(int j = 0 ; j < n_col ; j++){
                        if(table[i][j]=='A')
                        {
                                ax=i;
                                ay=j;
                        }
                        if(table[i][j]=='B')
                        {
                                bx=i;
                                by=j;
                        }
                }
        }
        if(role=='A')
        {
                queue[0].x=ax;
                queue[0].y=ay;
                queue[0].point=score_A;
                queue[0].step=0;
                int front=0,rear=1,tx,ty;
                for(;front<rear;++front)
                {
                        if(queue[front].step==9)
                                break;
                        for(int i=0;i<4;++i)
                        {
                                tx=queue[front].x +dx[i];
                                ty=queue[front].y +dy[i];
                                if(tx<0||tx>=n_row||ty<0||ty>=n_col||table[tx][ty]=='x'||(tx==bx&&ty==by))
                                        continue;
                                else{
                                        if(check[tx][ty]==0)
                                        {
                                                if(maxdir==-1)
                                                {
                                                        maxdir=i;
                                                }
                                                if(front==0)
                                                        queue[rear].dir=i;
                                                else
                                                        queue[rear].dir=queue[front].dir;

                                                check[tx][ty]==1;
                                                queue[rear].x=tx;
                                                queue[rear].y=ty;
                                                if(table[tx][ty] == 'm')
                                                        queue[rear].point = queue[front].point+1;
                                                if(table[tx][ty] == 'n')
                                                        queue[rear].point = queue[front].point-1;
                                                if(table[tx][ty] == 's')
                                                        queue[rear].point = queue[front].point*2;
                                                if(table[tx][ty] == 't')
                                                        queue[rear].point = queue[front].point/2;
                                                if(queue[rear].point>max)
                                                {
                                                        max=queue[rear].point;
                                                        maxdir=queue[rear].dir;
                                                }
                                                queue[rear].step=1+queue[front].step ;
                                                ++rear;
                                        }
                                }
                        }
                }
        }
        else
        {
                queue[0].x=bx;
                queue[0].y=by;
                queue[0].point=score_B;
                queue[0].step=0;
                int front=0,rear=1,tx,ty;
                for(;front<rear;++front)
                {
                        if(queue[front].step==9)
                                break;
                        for(int i=0;i<4;++i)
                        {
                                int tx=queue[front].x+dx[i];
                                int ty=queue[front].y+dy[i];
                                if(tx<0||tx>=n_row||ty<0||ty>=n_col||table[tx][ty]=='x'||(tx==ax&&ty==ay))
                                        continue;
                                else{
                                        if(check[tx][ty]==0)
                                        {
                                                if(maxdir==-1)
                                                {
                                                        maxdir=i;
                                                }
                                                if(front==0)
                                                        queue[rear].dir=i;
                                                else
                                                        queue[rear].dir=queue[front].dir;

                                                check[tx][ty]==1;
                                                queue[rear].x=tx;
                                                queue[rear].y=ty;
                                                if(table[tx][ty] == 'm')
                                                        queue[rear].point = queue[front].point+1;
                                                if(table[tx][ty] == 'n')
                                                        queue[rear].point = queue[front].point-1;
                                                if(table[tx][ty] == 's')
                                                        queue[rear].point = queue[front].point*2;
                                                if(table[tx][ty] == 't')
                                                        queue[rear].point = queue[front].point/2;
                                                if(queue[rear].point>max)
                                                {
                                                        max=queue[rear].point;
                                                        maxdir=queue[rear].dir;
                                                }
                                                queue[rear].step=1+queue[front].step ;
                                                ++rear;
                                        }
                                }
                        }

                }
        }
        return maxdir;
}