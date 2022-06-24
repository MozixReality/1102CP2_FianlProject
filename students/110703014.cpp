#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

int dx[] = {0,-1,1,0,0},dy[] = {0,0,0,-1,1};
char grid[20][20];
char mv[5][10] = {"","UP","DOWN","LEFT","RIGHT"};
enum Action{INIT, UP, DOWN, LEFT, RIGHT};
int front = 0,rear = 0,i,j,k,move = 0, n , m ;
int qx[21*21] = {}, qy[21*21] = {}, qp[21*21] = {}, qact[21][21] = {},qs[21][21] = {},r = rand();
int visited[21][21];

bool ENQUEUE(int x,int y,int front,int act){
 if(visited[x][y] > 0)
         return false;
 qx[rear] = x;
 qy[rear] = y;
 qp[rear++] = front;
 qact[x][y] = act;
 visited[x][y] = 1;
 return true;
}

int valid(int x,int y){
        return (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] != 'x' && grid[x][y] != 'B' && grid[x][y] != 'A' );
}

void find_the_best(int px,int py,int max_x,int max_y) {
        int i,j,tempx = max_x,tempy = max_y,flag = 0;

        if(px == max_x && py == max_y){
                for(i = 1 ; i <= 4 ;++i){
                        if(grid[px + dx[i]][py + dy[i]] == '.' || ((qs[px][py] == 0 || qs[px][py] == -1 ) && grid[px + dx[i]][py + dy[i]] == 't')){
                                printf("%s\n",mv[i]);
                                flag = 1;
                                break;
                                return;
                        }
                }
                if(flag == 0){
                        if(valid(px,py + 1))
                                printf("RIGHT\n");
                        else if(valid(px,py - 1))
                                printf("LEFT\n");
                        else if(valid(px - 1,py))
                                printf("UP\n");
                        else if(valid(px + 1,py))
                                printf("DOWN\n");
                }
        }

        while(1){

            if((max_x - dx[qact[tempx][tempy]] == px) && (max_y - dy[qact[tempx][tempy]] == py))
                break;
            max_x -= dx[qact[tempx][tempy]];
            max_y -= dy[qact[tempx][tempy]];
            tempx = max_x;
            tempy = max_y;

        }



        switch(qact[max_x][max_y]) {
              case 1:
                  printf("%s\n",mv[1]);
                  break;
              case 2:
                  printf("%s\n",mv[2]);
                  break;
              case 3:
                  printf("%s\n",mv[3]);
                  break;
              case 4:
                  printf("%s\n",mv[4]);
                  break;
              default:

                  break;
        }

}

bool BFS(int px,int py,int score,char player) {

int max_x = px, max_y = py, max_score = score, x = px, y = py, i, step = 0,flag = 0;

memset(visited,0,sizeof(visited));

ENQUEUE(px,py,-1,INIT);
qs[px][py] = score;

for(;front < rear ; ++front) {

    if(step++ >= 20) {
       break;
    }

    for(i = 1; i <= 4; ++i){

        x = qx[front] + dx[i];
        y = qy[front] + dy[i];

        if(x < 0 || y < 0 || x >= n || y >= m )
                continue;
        if((grid[x][y] == 'A' && player == 'B') || (player == 'A' && grid[x][y] == 'B')){
            step += 19;
            qs[x][y] = qs[qx[front]][qy[front]] - 512;
            continue;
        }

        if(grid[x][y] == 'x')
            continue;

        switch(grid[x][y]){
            case '.':
                qs[x][y] = qs[qx[front]][qy[front]];
                break;
            case 'm':
                grid[x][y] = '.';
                qs[x][y] = qs[qx[front]][qy[front]] + 1;
                break;
            case 'n':
                grid[x][y] = '.';
                qs[x][y] = qs[qx[front]][qy[front]] - 1;
                break;
            case 's':
                grid[x][y] = '.';
                qs[x][y] = qs[qx[front]][qy[front]] * 2 ;
                break;
            case 't':
                grid[x][y] = '.';
                qs[x][y] = qs[qx[front]][qy[front]] / 2;
                break;
            case 'b':
                grid[x][y] = '.';
                qs[x][y] = qs[qx[front]][qy[front]];
                break;
        }

        ENQUEUE(x,y,front,i);

        max_score = max(max_score,qs[x][y]);

        if(max_score == qs[x][y]){
            max_x = x;
            max_y = y;
        }

    }
}
find_the_best(px,py,max_x,max_y);
return false;
}


int main(void){
int i ,j ,t ,scoreA ,scoreB;
scanf("%d\n",&t);
scanf("%d %d\n",&n,&m);
char player;

for(i = 0 ; i < n ; ++i)
    for(j = 0 ; j < m ; ++j){
        scanf("%c",&grid[i][j]);
        getchar();
    }

scanf("%d",&scoreA);
scanf("%d",&scoreB);
getchar();
scanf("%c",&player);
int pi,pj,max = -20000;

for(i = 0 ; i < n ;++i){
    for(j = 0 ; j < m ;++j){
        if(grid[i][j] == player){
            pi = i, pj = j;
            break;
        }
    }
}

BFS(pi,pj,((player == 'A') ? scoreA : scoreB),player);

return 0;
}
