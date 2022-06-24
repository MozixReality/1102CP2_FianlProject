#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <time.h>
#include <algorithm>

using namespace std;

int Round, M, N;

struct Map
{
    char objection;
    int route;
    int DeadEnd;
};

struct Object
{
    char obj;
    int x;
    int y;
    int distance;
};

Map map[20][20] = {};
int direction = 0;

int routeA[20][20] = {};
int routeB[20][20] = {};

int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, 1, -1, 0};

bool valid(int x, int y)
{
    return (
        x >= 0 && x < M && y >=0 && y < N &&
        map[x][y].objection != 'x' &&
        map[x][y].objection != 'A' && map[x][y].objection != 'B'
    );
}

bool valid2(int x, int y)
{
    return (
        x >= 0 && x < M && y >=0 && y < N &&
        map[x][y].objection != 'x'
    );
}

void BFS(int startX, int startY )
{
    queue<int> x;
    queue<int> y;

    for(int i = 0; i < 20; ++i)
    {
        for(int j = 0; j < 20; ++j)
            map[i][j].route = 9999;
    }

    x.push(startX);
    y.push(startY);
    map[startX][startY].route = 0;

    int nx, ny;
    int len;

    cout << endl;

    while(!x.empty())
    {
        len = x.size();
        
        char me = map[startX][startY].objection;

        for(int i = 0; i < len; ++i)
        {
            nx = x.front();
            ny = y.front();

            for(int j = 0; j < 4; ++j)
            {
                int cx = nx + dx[j];
                int cy = ny + dy[j];

                if(map[cx][cy].objection == me)
                    continue;
                else if(valid(cx, cy))
                {
                    if(map[cx][cy].route > map[nx][ny].route + 1)
                    {
                        map[cx][cy].route = map[nx][ny].route + 1;
                        x.push(cx);
                        y.push(cy);
                    }
                }
                else
                {
                    if((map[cx][cy].objection == 'A' || map[cx][cy].objection == 'B') && map[cx][cy].objection != me)
                        map[cx][cy].route = -2;
                    else
                        map[cx][cy].route = -1;
                }
            }
            x.pop();
            y.pop();

            //cout << endl;
        }
        //cout << endl;
    }
}

void FindDeadEnd(int m, int n)
{
    queue<int> x;
    queue<int> y;
    
    ///找出地圖上初始的死路
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if(map[i][j].objection == 'x')
                map[i][j].DeadEnd = -1;
            else
            {
                int num = 0;
                for (int z = 0; z < 4; ++z)
                    num += valid2(i+dx[z], j+dy[z]);
                
                if(num == 1)
                {
                    map[i][j].DeadEnd = -2;
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
                    map[i][j].DeadEnd = 0;
            }
        }
    }

    int nx, ny;

    ///判斷初始死路延伸出來的位置是否為死路的延伸
    while (!x.empty())
    {
        for (int i = 0; i < x.size(); )
        {
            nx = x.front();
            ny = y.front();

            int num = 0, cx, cy;
            for (int j = 0; j < 4; ++j)
                num += valid2(nx + dx[j], ny + dy[j]);

            if(num == 2)
            {
                map[nx][ny].DeadEnd = -2;

                for (int z = 0; z < 4; ++z)
                {
                    cx = nx + dx[z];
                    cy = ny + dy[z];
                    if(valid2(cx, cy) == 1 && map[cx][cy].DeadEnd != -2)
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

bool mycompare(Object s1, Object s2){
   return s1.distance < s2.distance;
}

int main(void)
{
    for(int i = 0; i < 20; ++i)
    {
        for(int j = 0; j < 20; ++j)
        {
            routeA[i][j] = 9999;
            routeB[i][j] = 9999;
        }
    }

    char me, you;
    int A, B, meX, meY, youX, youY;

    //輸入
    cin >> Round >> M >> N;
    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            cin >> map[i][j].objection;
            if(map[i][j].objection == 'A')
            {
                meX = i;
                meY = j;
            }
            else if(map[i][j].objection == 'B')
            {
                youX = i;
                youY = j;
            }
        }
    }
    cin >> A >> B >> me;
    
    //double START,END; START = clock();  //計時開始
    
    if(me == 'A')
        you = 'B';
    else    //AB互換swap
    {
        you = 'A';
        int temp;

        temp = meX;
        meX = youX;
        youX = temp;

        temp = meY;
        meY = youY;
        youY = temp;
    }
    
    //用BFS找自己路徑圖
    BFS(meX, meY);

    /*cout << "Route: " << endl;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
            routeA[i][j] = map[i][j].route;
    }

    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(routeA[i][j] < 10 && routeA[i][j] >= 0)
                cout << " " << routeA[i][j] << " ";
            else   
                cout << routeA[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "DeadEnd: " <<endl;*/
    
    //用FindDeadEnd找死路
    FindDeadEnd(M, N);

    /*for(int i = 0; i < M; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                if(map[i][j].DeadEnd < 10 && map[i][j].DeadEnd >= 0)
                    cout << " " << map[i][j].DeadEnd << " ";
                else   
                    cout << map[i][j].DeadEnd << " ";
            }
            cout << endl;
        }

    cout << endl;*/

    Object point[M*N];
    
    int a = 0;
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (map[i][j].objection == 'm'||map[i][j].objection == 's')
            {
                point[a].obj = map[i][j].objection;
                point[a].x = i;
                point[a].y = j;
                point[a].distance = map[i][j].route;
                ++a;
            }
        }
    }
    
    if(sizeof(point)/sizeof(Object) == 1)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (valid(meX+dx[j], meY+dy[j]) == 1 && map[meX+dx[j]][meY+dy[j]].DeadEnd != -2)
            {                    
                if(j == 0)
                    direction = 1;
                else if(j == 1)
                    direction = 2;
                else if(j == 2)
                    direction = 3;
                else
                    direction = 4;
                goto here;
                    
            }
        }
    }
    
    sort(point, point+a, mycompare);
    
    for (int i = 0; i < a; ++i)
    {
        if(i <= 10)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (valid(meX+dx[j], meY+dy[j]) == 1 && map[meX+dx[j]][meY+dy[j]].DeadEnd != -2)
                {
                    BFS(meX+dx[j], meY+dy[j]);
                    if(point[i].distance - map[point[i].x][point[i].y].route == 1)
                    {
                        if(j == 0)
                            direction = 1;
                        else if(j == 1)
                            direction = 2;
                        else if(j == 2)
                            direction = 3;
                        else
                            direction = 4;

                        goto here;
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < 4; ++j)
            {
                if (valid(meX+dx[j], meY+dy[j]) == 1 && map[meX+dx[j]][meY+dy[j]].DeadEnd != -2)
                {                    
                    if(j == 0)
                        direction = 1;
                    else if(j == 1)
                        direction = 2;
                    else if(j == 2)
                        direction = 3;
                    else
                        direction = 4;
                    goto here;
                    
                }
            }
        }     
    }
    
    here:;

    if(direction == 1)
        cout << "DOWN" << endl;
    else if(direction == 2)
        cout << "RIGHT" << endl;
    else if(direction == 3)
        cout << "LEFT" << endl;
    else
        cout << "UP" << endl;
    
    /*for (int i = 0; i < a; ++i)
        cout << point[i].obj << " (" << point[i].x << ", " << point[i].y << ") " << point[i].distance << endl;
    cout << endl;*/

    //END = clock();
    //cout << "Time used: " << (END - START) / CLOCKS_PER_SEC << "s" << endl;     //計時結束同時輸出時間

    //return 0;
}