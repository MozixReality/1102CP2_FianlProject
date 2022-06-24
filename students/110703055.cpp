#include<iostream>
#include<string>
#include<queue>
#include<ctime>
#include<algorithm>
#define MIN -100000
using namespace std;

/*
    b : stop 3 rounds
    m : +1 points
    n : -1 points
    s : points*2
    t : points/2(小數點捨去)
    x : wall
    . : no items
*/

string direction(int M,int x,int y,int point);
int up(int x,int y,int point);
int down(int x,int y,int point);
int left(int x,int y,int point);
int right(int x,int y,int point);
int AddPoints(int x, int y, int point);
bool valid(int x, int y);
string cmp (int u,int d,int l,int r,int x,int y);

char map[20][20];
int M,N;
int T;
char b,m,n,s,t,x;

struct dir{
    int u;
    int d;
    int l;
    int r;
};

/*方便記錄位置與分數在同一變數中*/
struct details{
    int x;
    int y;
    int point;
};

string direction(int M,int x,int y,int point){
    struct dir Sum;
    Sum.d=MIN;
    Sum.l=MIN;
    Sum.r=MIN;
    Sum.u=MIN;
    if(x!=0&&map[x-1][y]!='x'&&map[x-1][y]!='A'&&map[x-1][y]!='B'){
//        cerr<<"a"<<endl;
        Sum.u=up(x-1,y,point);
    }
    if(x!=M-1&&map[x+1][y]!='x'&&map[x+1][y]!='A'&&map[x+1][y]!='B'){
//        cerr<<"b"<<endl;
        Sum.d=down(x+1,y,point);
    }
    if(y!=0&&map[x][y-1]!='x'&&map[x][y-1]!='A'&&map[x][y-1]!='B'){
//        cerr<<"c"<<endl;
        Sum.l=left(x,y-1,point);
    }
    if(y!=M-1&&map[x][y+1]!='x'&&map[x][y+1]!='A'&&map[x][y+1]!='B'){
//        cerr<<"d"<<endl;
        Sum.r=right(x,y+1,point);
    }
    //cout<<Sum.u<<" "<<Sum.d<<" "<<Sum.l<<" "<<Sum.r<<endl;
    return cmp(Sum.u,Sum.d,Sum.l,Sum.r,x,y);
}

int Y[4]={1, 0, -1, 0};
int X[4]={0, 1, 0, -1};

queue<struct details> q_up;
queue<struct details> q_down;
queue<struct details> q_right;
queue<struct details> q_left;

int CheckIfWalked_up[20][20]={0};
int CheckIfWalked_down[20][20]={0};
int CheckIfWalked_right[20][20]={0};
int CheckIfWalked_left[20][20]={0};

clock_t Begin,End;
double dur;

/*計算分數*/
int up(int x,int y,int point){
    struct details now;
    int total_point=0;
    now.x=x;
    now.y=y;
    now.point=AddPoints(now.x,now.y,point);
    q_up.push(now);
    struct details tmp;
    while(!q_up.empty()){
        tmp=q_up.front();
        q_up.pop();
        if(tmp.point>total_point){
            total_point=tmp.point;
        }
        End=clock();
        dur=double(End - Begin)/CLOCKS_PER_SEC;
        if(dur>0.9){
            return total_point;
        }
        CheckIfWalked_up[tmp.x][tmp.y]=1;
        for(int i=0;i<4;i++){
            if(CheckIfWalked_up[tmp.x+X[i]][tmp.y+Y[i]]==0&&valid(tmp.x+X[i],tmp.y+Y[i])){
                struct details next_step;
                next_step.x=tmp.x+X[i];
                next_step.y=tmp.y+Y[i];
                next_step.point=AddPoints(next_step.x,next_step.y,tmp.point);
                q_up.push(next_step);
            }
        }
    }
    return total_point;
}

int down(int x,int y,int point){
    struct details now;
    int total_point=0;
    now.x=x;
    now.y=y;
    now.point=AddPoints(now.x,now.y,point);
    q_down.push(now);
    struct details tmp;
    while(!q_down.empty()){
        tmp=q_down.front();
        //cout<<tmp.x<<' '<<tmp.y<<' '<<tmp.point<<endl;
        q_down.pop();
        if(tmp.point>total_point){
            total_point=tmp.point;
        }
        End=clock();
        dur=double(End - Begin)/CLOCKS_PER_SEC;
        if(dur>0.9){
            return total_point;
        }
        CheckIfWalked_down[tmp.x][tmp.y]=1;
        for(int i=0;i<4;i++){
            //cout<<valid(tmp.x+X[i],tmp.y+Y[i])<<endl;
            if(CheckIfWalked_down[tmp.x+X[i]][tmp.y+Y[i]]==0&&valid(tmp.x+X[i],tmp.y+Y[i])){
                struct details next_step;
                next_step.x=tmp.x+X[i];
                next_step.y=tmp.y+Y[i];
                next_step.point=AddPoints(next_step.x,next_step.y,tmp.point);
                q_down.push(next_step);
            }
        }
    }
    return total_point;
}

int left(int x,int y,int point){
    struct details now;
    int total_point=0;
    now.x=x;
    now.y=y;
    now.point=AddPoints(now.x,now.y,point);
    q_left.push(now);
    struct details tmp;
    while(!q_left.empty()){
        tmp=q_left.front();
        q_left.pop();
        if(tmp.point>total_point){
            total_point=tmp.point;
        }
        End=clock();
        dur=double(End - Begin)/CLOCKS_PER_SEC;
        if(dur>0.9){
            return total_point;
        }
        CheckIfWalked_left[tmp.x][tmp.y]=1;
        for(int i=0;i<4;i++){
            if(CheckIfWalked_left[tmp.x+X[i]][tmp.y+Y[i]]==0&&valid(tmp.x+X[i],tmp.y+Y[i])){
                struct details next_step;
                next_step.x=tmp.x+X[i];
                next_step.y=tmp.y+Y[i];
                next_step.point=AddPoints(next_step.x,next_step.y,tmp.point);
                q_left.push(next_step);
            }
        }
    }
    return total_point;
}

int right(int x,int y,int point){
    struct details now;
    int total_point=0;
    now.x=x;
    now.y=y;
    now.point=AddPoints(now.x,now.y,point);
    q_right.push(now);
    struct details tmp;
    while(!q_right.empty()){
        tmp=q_right.front();
        //cout<<tmp.x<<' '<<tmp.y<<' '<<tmp.point<<endl;
        q_right.pop();
        if(tmp.point>total_point){
            total_point=tmp.point;
        }
        End=clock();
        dur=double(End - Begin)/CLOCKS_PER_SEC;
        if(dur>0.9){
            return total_point;
        }
        CheckIfWalked_right[tmp.x][tmp.y]=1;
        for(int i=0;i<4;i++){
            //cout<<valid(tmp.x+X[i],tmp.y+Y[i])<<endl;
            if(CheckIfWalked_right[tmp.x+X[i]][tmp.y+Y[i]]==0&&valid(tmp.x+X[i],tmp.y+Y[i])){
                struct details next_step;
                next_step.x=tmp.x+X[i];
                next_step.y=tmp.y+Y[i];
                next_step.point=AddPoints(next_step.x,next_step.y,tmp.point);
                q_right.push(next_step);
            }
        }
    }
    return total_point;
}

/*計分*/
int AddPoints(int x, int y, int point){
    if(map[x][y]=='m'){
        point+=1;
    }
    else if(map[x][y]=='n'){
        point-=1;
    }
    else if(map[x][y]=='s'){
        point*=2;
    }
    else if(map[x][y]=='t'){
        point/=2;
    }
    else{
        point+=0;
    }
    return point;
}

/*比較上下左右分數何者最優*/
string cmp (int u,int d,int l,int r,int x,int y){
    int total_point=0;
    if(u>total_point){
        total_point=u;
    }
    if(d>total_point){
        total_point=d;
    }
    if(l>total_point){
        total_point=l;
    }
    if(r>total_point){
        total_point=r;
    }
    if(total_point==u){
        return "UP";
    }
    else if(total_point==d){
        return "DOWN";
    }
    else if(total_point==l){
        return "LEFT";
    }
    else{
        return "RIGHT";
    }
}

/*判斷此步是否合法*/
bool valid(int x, int y){
    return (x >= 0 && x < M && y >=0 && y < N &&
    map[x][y] != 'x' && map[x][y] != 'A' && map[x][y] != 'B'&& 
    map[x][y] != 'b');
}

int main(void){
    cin>>T;     //回合數
    cin>>M>>N;  //map大小
    struct details A,B;
    char cur_player;
    Begin=clock(); //計算程式執行時間
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            map[i][j]='0';
        }
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin>>map[i][j];
            if(map[i][j]=='A'){         //記錄Ａ的位置
                A.x=i;
                A.y=j;
            }
            else if(map[i][j]=='B'){    //記錄Ｂ的位置
                B.x=i;
                B.y=j;
            }
        }
    }
    cin>>A.point>>B.point;    // Ａ、Ｂ目前的分數
    cin>>cur_player;    //目前操控玩家
/*  測試輸出地圖
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
*/
    struct details cur;
    if(cur_player=='A'){
        cur=A;
    }
    else if(cur_player=='B'){
        cur=B;
    }
/*  測試輸出合法不合法
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
            cout<<valid(i,j)<<' ';
        puts("");
    }
*/
    cout<<direction(M,cur.x,cur.y,cur.point)<<endl;
}