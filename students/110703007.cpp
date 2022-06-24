#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

#define F first
#define S second

int myPoint;
int yourPoint;

struct point{
    int x;
    int y;

};//宣告point

struct point me;
struct point you;

int Round, M, N;
char map[20][20]={};

char meID;
char youID;

int routeA[20][20]={};
float pointA[20][20]={};

float cpA[20][20] = {};

vector<struct point> starPt;
vector<struct point> mushPt;
vector<struct point> toxicPt;

enum Direction { LEFT,
                 UP,
                 RIGHT,
                 DOWN };

int routeB[20][20]={};
float pointB[20][20]={};

bool valid(int x, int y){
    return (
        x >= 0 && x < M && y >=0 && y < N &&
        map[x][y] != 'x' &&
        map[x][y] != 'A' && map[x][y] != 'B'
    );
}

int route[20][20] = {};

bool direction_valid(int x, int y, int newx, int newy){
    return (
        x >= 0 && x < M && y >=0 && y < N &&
        newx >= 0 && newx < M && newy >=0 && newy < N &&
        routeA[x][y]>routeA[newx][newy] && routeA[newx][newy]>=0
    );
}

int find_direction(int x, int y){
    int dx[4] = {0,-1,0,1};//{左,上,右,下}
    int dy[4] = {-1,0,1,0};

    queue<int>valid_x;
    queue<int>valid_y;

    valid_x.push(x);
    valid_y.push(y);

    int len;
    float maxpt;

    while(!valid_x.empty()){
        len = valid_x.size();

        int flag = 0;

        int nx,ny;

        for(int i=0 ; i<len ; ++i){
            nx = valid_x.front();
            ny = valid_y.front();

            //cout<<"("<<nx<<" , "<<ny<<")"<<endl;

            maxpt = -9999;


            for(int j=0 ; j<4 ; j++){
                int cx = nx+dx[j];
                int cy = ny+dy[j];

                if(map[cx][cy] == meID && routeA[nx][ny] == 1){
                    flag = 1;
                }

                if(pointA[cx][cy]>maxpt&&direction_valid(nx,ny,cx,cy)){
                    maxpt = pointA[cx][cy];

                }
            }

            //cout<<"flag = "<<flag<<endl;
            //cout<<"maxpt = "<<maxpt<<endl;

            if(flag == 1){
                break;
            }

            for(int j=0 ; j<4 ; j++){
                int cx = nx+dx[j];
                int cy = ny+dy[j];

                if(direction_valid(nx,ny,cx,cy)&&pointA[cx][cy] == maxpt){
                    valid_x.push(cx);
                    valid_y.push(cy);

                }
            }
            valid_x.pop();
            valid_y.pop();
        }

        if(flag == 1){
            break;
        }

    }

    int dirx = valid_x.front();
    int diry = valid_y.front();

    for(int i=0 ; i<4 ; i++){
        //cout<<"dirx: "<<dirx<<" , "<<"diry: "<<diry<<endl;
        if(me.x+dx[i]==dirx && me.y+dy[i]==diry){
            return i;
        }
    }

}

float points[20][20] = {0};

void BFS(int startX, int startY ){
    queue<int> x;
    queue<int> y;

    for(int i=0 ; i<20 ; ++i){
        for(int j=0 ; j<20 ; j++){
            route[i][j] = 9999;
            points[i][j] = -9999;
        }
    }

    x.push(startX);
    y.push(startY);
    route[startX][startY] = 0;
    points[startX][startY] = myPoint;

    int dx[4] = {0,-1,0,1};
    int dy[4] = {-1,0,1,0};

    int nx,ny;
    int len;

    //cout<<endl;

    while(!x.empty()){
        len = x.size();

        char me = map[startX][startY];

        for(int i=0 ; i<len ; ++i){
            nx = x.front();
            ny = y.front();


            //這個地方是他標路徑的過程
            //--------------------
            /*
            for(int i=0;i<M;i++){
                for(int j=0;j<N;j++){
                    if(route[i][j]>=0&&route[i][j]<10){
                        cout<<" ";
                    }
                    cout<<route[i][j]<<" ";
                }cout<<endl;
            }

            cout<<endl;
            */
            //--------------------

            for(int j=0 ; j<4 ; ++j ){
                int cx = nx+dx[j];
                int cy = ny+dy[j];

                if(map[cx][cy]==me){
                    continue;
                }else if(valid(cx,cy)){
                    if(route[cx][cy]>route[nx][ny]+1){
                        route[cx][cy] = route[nx][ny]+1;
                        x.push(cx);
                        y.push(cy);

                        if(map[cx][cy] == '.'){
                            points[cx][cy] = points[nx][ny];
                        }else if(map[cx][cy] == 'm'){
                            points[cx][cy] = points[nx][ny]+1;
                        }else if(map[cx][cy] == 'n'){
                            points[cx][cy] = points[nx][ny]-1;
                        }else if(map[cx][cy] == 't'){
                            points[cx][cy] = points[nx][ny] - int(points[nx][ny]) + int(points[nx][ny])/2;
                        }else if(map[cx][cy] == 's'){
                            points[cx][cy] = points[nx][ny] + int(points[nx][ny]+0.6);
                        }else if(map[cx][cy] == 'b'){
                            points[cx][cy] = points[nx][ny] -0.6;
                        }

                    }else if(route[cx][cy]>route[nx][ny]){
                        float temp;
                        if(map[cx][cy] == '.'){
                            points[cx][cy] = points[nx][ny];
                        }else if(map[cx][cy] == 'm'){
                            temp = points[nx][ny]+1;
                        }else if(map[cx][cy] == 'n'){
                            temp = points[nx][ny]-1;
                        }else if(map[cx][cy] == 't'){
                            temp = points[nx][ny] - int(points[nx][ny]) + int(points[nx][ny])/2;
                        }else if(map[cx][cy] == 's'){
                            temp = points[nx][ny] + int(points[nx][ny]+0.6);
                        }else if(map[cx][cy] == 'b'){
                            temp = points[nx][ny] -0.6;
                        }
                        if(temp>points[cx][cy]){
                            points[cx][cy] = temp;
                        }
                    }
                }else{
                    if((map[cx][cy]=='A'||map[cx][cy]=='B')&&map[cx][cy]!=me){
                        route[cx][cy] = -2;
                        points[cx][cy] = points[nx][ny];
                    }else{
                        route[cx][cy] = -1;
                    }

                }
            }
            x.pop();
            y.pop();

            //cout<<endl;
        }//cout<<endl;

    }
}


int main(void){
    int A, B;

    cin >> Round >> M >> N;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin >> map[i][j];
            if(map[i][j] == 'A'){
                me.x = i;
                me.y = j;
            }else if(map[i][j] == 'B'){
                you.x = i;
                you.y = j;
            }else if(map[i][j] == 'm'){
                struct point temp;
                temp.x = i;
                temp.y = j;
                mushPt.push_back(temp);

            }else if(map[i][j] == 's'){
                struct point temp;
                temp.x = i;
                temp.y = j;
                starPt.push_back(temp);

            }else if(map[i][j] == 't'){
                struct point temp;
                temp.x = i;
                temp.y = j;
                toxicPt.push_back(temp);

            }
        }
    }

    cin >> myPoint >> yourPoint >> meID;

    if(meID == 'A'){
        youID = 'B';
    }
    else{
        youID = 'A';
        swap(me.x,you.x);
        swap(me.y,you.y);
        swap(myPoint,yourPoint);
    }

    ///自己的路徑圖
    BFS(me.x,me.y);

    for(int i=0 ; i<M ; ++i){
        for(int j=0 ; j<N ; ++j){
            routeA[i][j] = route[i][j];
            pointA[i][j] = points[i][j];
        }
    }
    ///對手的路徑圖
    BFS(you.x,you.y);

    for(int i=0 ; i<M ; ++i)
        for(int j=0 ; j<N ; ++j)
            routeB[i][j] = route[i][j];
    //cout<<"It is OK"<<endl;

    ///星星座標 bubble sort
    for(int i=0; i<starPt.size() ; ++i){
        for(int j=0 ; j<starPt.size() ; ++j){
            //cout<<"It is OK"<<endl;
            if(routeA[starPt[i].x][starPt[i].y]<routeA[starPt[j].x][starPt[j].y]){
                //cout<<"It is OK"<<endl;
                swap(starPt[i].x,starPt[j].x);
                swap(starPt[i].y,starPt[j].y);
            }
        }
    }

    ///香菇座標 bubble sort
    for(int i=0; i<mushPt.size() ; ++i){
        for(int j=0 ; j<mushPt.size() ; ++j){
            //cout<<"It is OK"<<endl;
            if(routeA[mushPt[i].x][mushPt[i].y]<routeA[mushPt[j].x][mushPt[j].y]){
                //cout<<"It is OK"<<endl;
                swap(mushPt[i].x,mushPt[j].x);
                swap(mushPt[i].y,mushPt[j].y);
            }
        }
    }

    ///劇毒蘑菇座標 bubble sort
    for(int i=0; i<toxicPt.size() ; ++i){
        for(int j=0 ; j<toxicPt.size() ; ++j){
            //cout<<"It is OK"<<endl;
            if(routeA[toxicPt[i].x][toxicPt[i].y]<routeA[toxicPt[j].x][toxicPt[j].y]){
                //cout<<"It is OK"<<endl;
                swap(toxicPt[i].x,toxicPt[j].x);
                swap(toxicPt[i].y,toxicPt[j].y);
            }
        }
    }


    int direction;

    int dx[4] = {0,-1,0,1};//{左,上,右,下}
    int dy[4] = {-1,0,1,0};

    float maxCP = -9999;
    int minRoute = 9999;
    int cpx,cpy;


    for(int i=0 ; i<M ; ++i){
        for(int j=0 ; j<N ; ++j){
            if(valid(i,j)){
                cpA[i][j] = (pointA[i][j]-myPoint) / routeA[i][j];

                if(cpA[i][j]>maxCP && routeA[i][j]<routeB[i][j]){
                    maxCP = cpA[i][j];
                    minRoute = routeA[i][j];
                    cpx = i;
                    cpy = j;
                }else if(cpA[i][j]==maxCP && routeA[i][j]<minRoute && routeA[i][j]<routeB[i][j]){
                    maxCP = cpA[i][j];
                    minRoute = routeA[i][j];
                    cpx = i;
                    cpy = j;
                }
            }else if(i==you.x && j == you.y){
                cpA[i][j] = (pointA[i][j]-myPoint) / routeA[i][j];
            }
        }
    }

    if(myPoint==yourPoint && myPoint>=15 && !mushPt.empty()){
        direction = find_direction(mushPt[0].x,mushPt[0].y);
    }else if(maxCP>0){
        direction = find_direction(cpx,cpy);
    }else if(cpA[you.x][you.y]>=0 && routeA[you.x][you.y]>1){
        direction = find_direction(you.x,you.y);
    }else{
        direction = find_direction(cpx,cpy);
    }

    /*

    if(myPoint>1){
        if(!starPt.empty()){
            for(int i=0 ; i<starPt.size() ; i++){
                if(pointA[starPt[i].x][starPt[i].y]>myPoint){
                    direction = find_direction(starPt[i].x,starPt[i].y);
                    //cout<<direction<<endl;
                    //cout<<endl;
                    break;
                }
            }
        }else if(!mushPt.empty()){
            for(int i=0 ; i<mushPt.size() ; i++){
                if(pointA[mushPt[i].x][mushPt[i].y]>myPoint){
                    direction = find_direction(mushPt[i].x,mushPt[i].y);
                    //cout<<direction<<endl;
                    //cout<<endl;
                    break;
                }
            }
        }else if(pointA[you.x][you.y]>myPoint && routeA[you.x][you.y]>1){
            direction = find_direction(you.x,you.y);
            //cout<<direction<<endl;
            //cout<<endl;

        }else{
            int maxPt = -9999;
            for(int i=0 ; i<4 ; i++){
                if(valid(me.x+dx[i],me.y+dy[i]) && pointA[me.x+dx[i]][me.y+dy[i]]>maxPt){///還要注意防堵
                    maxPt = pointA[me.x+dx[i]][me.y+dy[i]];
                }
            }
            for(int i=0 ; i<4 ; i++){
                if(valid(me.x+dx[i],me.y+dy[i]) && pointA[me.x+dx[i]][me.y+dy[i]]==maxPt){
                    direction = i;
                }
            }

        }
    }if(myPoint>=-2){
        if(!mushPt.empty()){
            for(int i=0 ; i<mushPt.size() ; i++){
                if(pointA[mushPt[i].x][mushPt[i].y]>myPoint){
                    direction = find_direction(mushPt[i].x,mushPt[i].y);
                    //cout<<direction<<endl;
                    //cout<<endl;
                    break;
                }
            }
        }else if(!toxicPt.empty()){
            for(int i=0 ; i<toxicPt.size() ; i++){
                if(pointA[toxicPt[i].x][toxicPt[i].y]>myPoint){
                    direction = find_direction(toxicPt[i].x,toxicPt[i].y);
                    //cout<<direction<<endl;
                    //cout<<endl;
                    break;
                }
            }
        }else if(pointA[you.x][you.y]>myPoint&&routeA[you.x][you.y]>1){
            direction = find_direction(you.x,you.y);
            //cout<<direction<<endl;
            //cout<<endl;

        }else{
            int maxPt = -9999;
            for(int i=0 ; i<4 ; i++){
                if(valid(me.x+dx[i],me.y+dy[i]) && pointA[me.x+dx[i]][me.y+dy[i]]>maxPt){///還要注意防堵
                    maxPt = pointA[me.x+dx[i]][me.y+dy[i]];
                }
            }
            for(int i=0 ; i<4 ; i++){
                if(valid(me.x+dx[i],me.y+dy[i]) && pointA[me.x+dx[i]][me.y+dy[i]]==maxPt){
                    direction = i;
                }
            }

        }
    }if(myPoint<-2){
        if(!toxicPt.empty()){
            for(int i=0 ; i<toxicPt.size() ; i++){
                if(pointA[toxicPt[i].x][toxicPt[i].y]>myPoint){
                    direction = find_direction(toxicPt[i].x,toxicPt[i].y);
                    //cout<<direction<<endl;
                    //cout<<endl;
                    break;
                }
            }
        }else if(!mushPt.empty()){
            for(int i=0 ; i<mushPt.size() ; i++){
                if(pointA[mushPt[i].x][mushPt[i].y]>myPoint){
                    direction = find_direction(mushPt[i].x,mushPt[i].y);
                    //cout<<direction<<endl;
                    //cout<<endl;
                    break;
                }
            }
        }else if(pointA[you.x][you.y]>myPoint&&routeA[you.x][you.y]>1){
            direction = find_direction(you.x,you.y);
            //cout<<direction<<endl;
            //cout<<endl;

        }else{
            int maxPt = -9999;
            for(int i=0 ; i<4 ; i++){
                if(valid(me.x+dx[i],me.y+dy[i]) && pointA[me.x+dx[i]][me.y+dy[i]]>maxPt){///還要注意防堵
                    maxPt = pointA[me.x+dx[i]][me.y+dy[i]];
                }
            }
            for(int i=0 ; i<4 ; i++){
                if(valid(me.x+dx[i],me.y+dy[i]) && pointA[me.x+dx[i]][me.y+dy[i]]==maxPt){
                    direction = i;
                }
            }

        }
    }*/


    if(direction==0){
        cout<<"LEFT"<<endl;
    }else if(direction==1){
        cout<<"UP"<<endl;
    }else if(direction==2){
        cout<<"RIGHT"<<endl;
    }else if(direction==3){
        cout<<"DOWN"<<endl;
    }

}
