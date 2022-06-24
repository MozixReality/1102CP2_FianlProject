#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <vector>
#include <time.h>
using namespace std;
//____________________________________________________________________________________

typedef struct point{
    int x;
    int y;
}pt;//宣告point

//_____________________________________________________________________________________(宣告)

int M,N,dis;
float myPoint;
char Me;
char map[20][20]={};//地圖
int route[20][20]={0};//路徑圖
int DeadEnd[20][20] = {};//block graph
int dx[4] = {1,0,-1,0};//direction
int dy[4] = {0,1,0,-1};
//_____________________________________________________________________________________(valid)

bool valid(int x, int y){
    return (
        x >= 0 && x < M && y >=0 && y < N && 
        map[x][y] != 'x' && 
        map[x][y] != 'A' && map[x][y] != 'B'
    );
}//確認是否合法

bool valid2(int x, int y)
{
    return (
        x >= 0 && x < M && y >=0 && y < N &&
        map[x][y] != 'x'
    );
}

bool valid3(int x1,int y1, int x2, int y2){//x1,y1是下一個位子;x2,y2是敵人座標
    int k,l;
    k=(-1-DeadEnd[x1][y1])*2;
    l=route[x2][y2];
    return l>=k;
}

bool proper(int x, int y){
    return( map[x][y]=='.'|| map[x][y]=='m' || map[x][y]=='s' );
}//確認該點至少不被扣分

//_____________________________________________________________________________________(BFS+point)

void BFS(int startX, int startY )
{
    queue<int> x;
    queue<int> y;

    for(int i = 0; i < 20; ++i)
    {
        for(int j = 0; j < 20; ++j)
            route[i][j] = 9999;
    }

    x.push(startX);
    y.push(startY);
    route[startX][startY] = 0;

    int nx, ny;
    int len;

    while(!x.empty())
    {
        len = x.size();
        
        char me = map[startX][startY];

        for(int i = 0; i < len; ++i)
        {
            nx = x.front();
            ny = y.front();

            for(int j = 0; j < 4; ++j)
            {
                int cx = nx + dx[j];
                int cy = ny + dy[j];

                if(map[cx][cy] == me)
                    continue;
                else if(valid(cx, cy))
                {
                    if(route[cx][cy] > route[nx][ny] + 1)
                    {
                        route[cx][cy] = route[nx][ny] + 1;
                        x.push(cx);
                        y.push(cy);
                    }
                }
                else
                {
                    if((map[cx][cy] == 'A' || map[cx][cy] == 'B') && map[cx][cy] != me)
                        route[cx][cy] = -2;
                    else
                        route[cx][cy] = -1;
                }
            }
            x.pop();
            y.pop();
        }
    }
}


//___________________________________________________________________________________________________(block)

void Findblock(void)
{
    queue<int> x;
    queue<int> y;
    int num = 0,round=0;
    ///找出地圖上初始的死路
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if(map[i][j] == 'x')
                DeadEnd[i][j] = -1;
            else
            {
                num = 0;
                for (int z = 0; z < 4; ++z)
                    num += valid2(i+dx[z], j+dy[z]);
                
                if(num == 1)
                {
                    DeadEnd[i][j] = -2;
                    for (int z = 0; z < 4; ++z)
                    {
                        if(valid2(i+dx[z], j+dy[z]) == 1)
                        {
                            x.push(i+dx[z]);
                            y.push(j+dy[z]);
                        }        
                    }
                }
                else
                    DeadEnd[i][j] = 0;
            }
        }
    }
    int nx, ny;
    int cx, cy,h;
    ///判斷初始死路延伸出來的位置是否為死路的延伸
    while (!x.empty())
    {   
        for (int i = 0; i < x.size(); )
        {
            nx = x.front();
            ny = y.front();
            num = 0;
            
            for (int j = 0; j < 4; ++j){
                num += valid2(nx + dx[j], ny + dy[j]);
                if(DeadEnd[nx + dx[j]][ny + dy[j]]<-1){
                    h=j;
                }
            }
            if(num == 2)
            {
                DeadEnd[nx][ny] = DeadEnd[nx + dx[h]][ny + dy[h]]-1;

                for (int z = 0; z < 4; ++z)
                {
                    cx = nx + dx[z];
                    cy = ny + dy[z];
                    if(valid2(cx, cy) == 1 && DeadEnd[cx][cy] >= 0)
                    {
                        x.push(cx);
                        y.push(cy);
                    }        
                }
            }
            x.pop();
            y.pop();
        }
    }
}

//___________________________________________________________________________________________________(main)

int main(void){
    pt my,next,dir,enemy;
    int Ascore, Bscore, myscore, T;
    char me,ano;
    int dot_cnt=0,x_cnt=0;
    next.x=-1,next.y=-1;//下個點一開始未被決定
    scanf("%d %d %d", &T, &M, &N);
    for(int i=0; i<M; ++i){
        for(int j=0; j<N; ++j){
            scanf(" %c", &map[i][j]);
        }
    }  
    scanf("%d %d ",&Ascore, &Bscore);
    scanf(" %c",&me);
    if(me=='A') ano='B';
    else ano='A';
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(map[i][j] == me){
                my.x = i;
                my.y = j;
            }
            if(map[i][j] == ano){
                enemy.x =i;
                enemy.y =j;
            }
        }
    }
    srand(time(NULL));
    BFS(my.x,my.y);
    Findblock();
    if(me=='A') myscore=Ascore;
    else myscore=Bscore;
    //____________________________________________________________________
    if(me=='A'){
        for(int i=0; i<4; ++i){
            if(valid( my.x+dx[i] , my.y+dy[i] )){
                if(proper( my.x+dx[i] , my.y+dy[i] )){
                    switch(map[my.x+dx[i]][my.y+dy[i]]){
                        case '.':
                            if( next.x==-1 && next.y==-1 ){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if( map[next.x][next.y]=='.' && rand()%8<3){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            //else if((map[next.x][next.y]=='b' || map[next.x][next.y]=='n' ||map[next.x][next.y]=='t')){
                            //    next.x=my.x+dx[i], next.y=my.y+dy[i];
                            //}
                            ++dot_cnt;
                        break;

                        case 'm':
                            if( next.x==-1 && next.y==-1 ){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if( map[next.x][next.y]!='s' && valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if(myscore<6 && valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                        break;

                        case 's':
                            if( next.x==-1 && next.y==-1 ){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if( map[next.x][next.y]!='m'&& valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if(myscore>5 && valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            } 
                        break;
                    }
                }
                //else if(next.x!=-1 && next.y!=-1) continue;
                else{
                    switch(map[my.x+dx[i]][my.y+dy[i]]){
                        case 'b':
                        if( next.x==-1 && next.y==-1 ){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        else if(valid3(next.x,next.y,enemy.x,enemy.y) && T%7<3&& map[next.x][next.y]!='s'&&map[next.x][next.y]!='m'){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        break;

                        case 'n':
                        if( next.x==-1 && next.y==-1 ){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        else if(valid3(next.x,next.y,enemy.x,enemy.y) && T%7<3&& map[next.x][next.y]!='s'&&map[next.x][next.y]!='m'){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        break;

                        case 't':
                        if( next.x==-1 && next.y==-1 ){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        else if(valid3(next.x,next.y,enemy.x,enemy.y) && T%7<3&& map[next.x][next.y]!='s'&&map[next.x][next.y]!='m'){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        break;
                    }
                }
            }
            else ++x_cnt;
        }
    }
    //____________________________________________________________________
    if(me=='B'){
        for(int i=3; i>=0; --i){
            if(valid( my.x+dx[i] , my.y+dy[i] )){
                if(proper( my.x+dx[i] , my.y+dy[i] )){
                    switch(map[my.x+dx[i]][my.y+dy[i]]){
                        case '.':
                            if( next.x==-1 && next.y==-1 ){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if( map[next.x][next.y]=='.' && rand()%8<3){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                                //else if((map[next.x][next.y]=='b' || map[next.x][next.y]=='n' ||map[next.x][next.y]=='t')){
                                //    next.x=my.x+dx[i], next.y=my.y+dy[i];
                            //}
                            ++dot_cnt;
                        break;

                        case 'm':
                            if( next.x==-1 && next.y==-1 ){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if( map[next.x][next.y]!='s'&& valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if(myscore<6 && valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                        break;
                        case 's':
                            if( next.x==-1 && next.y==-1 ){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if( map[next.x][next.y]!='m' && valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            }
                            else if(myscore>=6 && valid3(next.x,next.y,enemy.x,enemy.y)){
                                next.x=my.x+dx[i], next.y=my.y+dy[i];
                            } 
                        break;
                    }
                }
                //else if(next.x!=-1 && next.y!=-1) continue;
                else{
                    switch(map[my.x+dx[i]][my.y+dy[i]]){
                        case 'b':
                        if( next.x==-1 && next.y==-1 ){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        else if(valid3(next.x,next.y,enemy.x,enemy.y) && T%7<3 && map[next.x][next.y]!='s'&&map[next.x][next.y]!='m'){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        break;
                        case 'n':
                        if( next.x==-1 && next.y==-1 ){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        else if(valid3(next.x,next.y,enemy.x,enemy.y) && T%7<3&& map[next.x][next.y]!='s'&&map[next.x][next.y]!='m'){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        break;

                        case 't':
                        if( next.x==-1 && next.y==-1 ){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        else if(valid3(next.x,next.y,enemy.x,enemy.y) && T%7<3&& map[next.x][next.y]!='s'&&map[next.x][next.y]!='m'){
                            next.x=my.x+dx[i], next.y=my.y+dy[i];
                        }
                        break;
                    }
                }
            }
            else ++x_cnt;
        }
    }
    dir.x=next.x-my.x,dir.y=next.y-my.y;
    if(dir.x==1 && dir.y==0) printf("DOWN\n");
    else if(dir.x==-1 && dir.y==0) printf("UP\n");
    else if(dir.x==0 && dir.y==1) printf("RIGHT\n");
    else if(dir.x==0 && dir.y==-1) printf("LEFT\n");
    return 0;
}