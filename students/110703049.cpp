#include<stdio.h>
#include<stdbool.h>

typedef struct position position;

struct position{
        int x;
        int y;
        int there_score;
        int dir;
        int step;
};

char arr[20][20];
int M,N;

bool valid(int x,int y);
int find(int start_x,int start_y,int start_score);

int main(){
        /*input*/
        int tern;
        scanf("%d\n%d %d\n", &tern,&M,&N);
        int A,B;
        char role, NoUse;
        for(int i=0;i<M;++i){
                for(int j=0;j<M;++j){
                        scanf("%c%c", &arr[i][j],&NoUse);
                }
        }
        scanf("%d\n%d\n%c", &A,&B,&role);
        int start_x, start_y;
        for(int i=0;i<M;++i){
                for(int j=0;j<M;++j){
                        if(arr[i][j]==role){
                                start_x=i;
                                start_y=j;
                        }
                }
        }

        int temp_score;
        if(role=='A')
                temp_score=A;
        if(role=='B')
                temp_score=B;

        int ans=find(start_x,start_y,temp_score);

        if(ans==1)
                printf("DOWN\n");

        if(ans==2)
                printf("UP\n");

        if(ans==3)
                printf("LEFT\n");

        if(ans==4)
                printf("RIGHT\n");

        return 0;
}

int find(int start_x, int start_y, int start_score){

        int dx[]={1,-1,0,0};
        int dy[]={0,0,-1,1};

        position q[500];
        q[0].x=start_x;
        q[0].y=start_y;
        q[0].there_score=start_score;
        q[0].dir=0;
        q[0].step=0;

        int now_x;
        int now_y;
        int now_score;
        int now_dir;
        int now_step;/*depth*/
        int tmp_x;
        int tmp_y;

        int max=-1000;
        int direction;

        int vis[M][M];
        for(int i=0;i<M;++i){
                for(int j=0;j<M;++j){
                        if(i==start_x && j==start_y)
                                vis[i][j]=1;
                        else
                                vis[i][j]=0;
                }
        }

        int j=1;
        for(int i=0;i<j;++i){
                now_x=q[i].x;
                now_y=q[i].y;
                now_score=q[i].there_score;
                now_dir=q[i].dir;
                now_step=q[i].step;/*the middle*/

                for(int t=0;t<4;++t){
                        tmp_x=now_x+dx[t];
                        tmp_y=now_y+dy[t];

                        if(valid(tmp_x,tmp_y) && now_step<20 && vis[tmp_x][tmp_y]==0){
                                vis[tmp_x][tmp_y]=1;
                                q[j].x=tmp_x;
                                q[j].y=tmp_y;
                                q[j].step=now_step+1;
                                if(i==0)
                                        q[j].dir=t+1;
                                else
                                        q[j].dir=now_dir;

                                if(arr[tmp_x][tmp_y]=='m')
                                        q[j].there_score=now_score+1;

                                if(arr[tmp_x][tmp_y]=='n')
                                        q[j].there_score=now_score-1;

                                if(arr[tmp_x][tmp_y]=='s')
                                        q[j].there_score=now_score*2;

                                if(arr[tmp_x][tmp_y]=='t')
                                        q[j].there_score=now_score/2;

                                if(arr[tmp_x][tmp_y]=='.')
                                        q[j].there_score=now_score;

                                if(arr[tmp_x][tmp_y]=='b'){
                                        q[j].there_score=now_score;
                                        q[j].step=now_step+4;
                                }

                                if(q[j].there_score>max){
                                        max=q[j].there_score;
                                        direction=q[j].dir;
                                }
                                ++j;
                        }
                }
        }
        return direction;
}

bool valid(int x,int y){
        if(x>=0 && x<M && y>=0 && y<M && arr[x][y]!='x' && arr[x][y]!='A' && arr[x][y]!='B')
                return 1;
        else return 0;
}