#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <ctime>

using namespace std;

char arr[20][20];
int check1[20][20];
int check2[20][20];
int check3[20][20];
int check4[20][20];

int Y[4]={1, 0, -1, 0};
int X[4]={0, 1, 0, -1};

int add_points(int x, int y, int sum);
int up(int x, int y, int point);
int down(int x, int y, int point);
int left(int x, int y, int point);
int right(int x, int y, int point);
bool valid(int x, int y);
string direction(int M, int x, int y, int point);
string cmp(int a, int b, int c, int d, int x, int y);

struct node{
    int i;
    int j;
    int point;
};

clock_t start;
clock_t stop;
double duration;

queue<struct node> q1;
queue<struct node> q2;
queue<struct node> q3;
queue<struct node> q4;

int Round, M, N;

int up(int x, int y, int point)
{
    struct node now;
    now.i=x;
    now.j=y;
    now.point = add_points(x, y, point);
    q1.push(now);

    int max = 0;

    struct node tmp;
    while(!q1.empty())
    {
        tmp = q1.front();
        //cout<<"UP x= "<<tmp.i<<" y= "<<tmp.j<<" point= "<<tmp.point<< " " <<arr[tmp.i][tmp.j] <<endl;
        check1[tmp.i][tmp.j] = 1;
        q1.pop();

        if(tmp.point > max)
            max = tmp.point;

        stop = clock();
        duration = (double(stop) - double(start)) / CLOCKS_PER_SEC;
        if(duration >= 0.9)
            return max;

        for(int k = 0; k < 4; k++)
        {
            if(check1[tmp.i+X[k]][tmp.j+Y[k]] == 1 || !valid(tmp.i+X[k], tmp.j+Y[k]))
                continue;

            struct node to;
            to.i = tmp.i + X[k];
            to.j = tmp.j + Y[k];
            to.point = add_points(tmp.i+X[k], tmp.j+Y[k], tmp.point);
            q1.push(to);

        }

    }

    return max;
}

int down(int x, int y, int point)
{
    struct node now;
    now.i=x;
    now.j=y;
    now.point = add_points(x, y, point);
    q2.push(now);

    int max = 0;

    struct node tmp;

    //cerr << "1" << endl;
    while(!q2.empty())
    {
        tmp = q2.front();
        //cout<<"DOWN x= "<<tmp.i<<" y= "<<tmp.j<<" point= "<<tmp.point<< " " <<arr[tmp.i][tmp.j] <<endl;
        check2[tmp.i][tmp.j] = 1;
        q2.pop();

        if(tmp.point > max)
            max = tmp.point;

        stop = clock();
        duration = (double(stop) - double(start)) / CLOCKS_PER_SEC;
        //cout << duration << endl;
        if(duration >= 0.9)
            return max;


        for(int k = 0; k < 4; ++k)
        {
            if(check2[tmp.i+X[k]][tmp.j+Y[k]] == 1 || !valid(tmp.i+X[k], tmp.j+Y[k]))
                continue;

            struct node to;
            to.i = tmp.i + X[k];
            to.j = tmp.j + Y[k];
            to.point = add_points(tmp.i+X[k], tmp.j+Y[k], tmp.point);
            q2.push(to);

        }

    }

    return max;
}

int left(int x, int y, int point)
{
    struct node now;
    now.i=x;
    now.j=y;
    now.point = add_points(x, y, point);
    q3.push(now);

    int max = 0;

    struct node tmp;
    while(!q3.empty())
    {
        tmp = q3.front();
        //cout<<"LEFT x= "<<tmp.i<<" y= "<<tmp.j<<" point= "<<tmp.point<< " " <<arr[tmp.i][tmp.j] <<endl;
        check3[tmp.i][tmp.j] = 1;
        q3.pop();

        if(tmp.point > max)
            max = tmp.point;

        stop = clock();
        duration = (double(stop) - double(start)) / CLOCKS_PER_SEC;
        if(duration >= 0.9)
            return max;


        for(int k = 0; k < 4; k++)
        {
            if(check3[tmp.i+X[k]][tmp.j+Y[k]] == 1 || !valid(tmp.i+X[k], tmp.j+Y[k]))
                continue;

            struct node to;
            to.i = tmp.i + X[k];
            to.j = tmp.j + Y[k];
            to.point = add_points(tmp.i+X[k], tmp.j+Y[k], tmp.point);
            q3.push(to);

        }

    }

    return max;
}

int right(int x, int y, int point)
{
    struct node now;
    now.i=x;
    now.j=y;
    now.point = add_points(x, y, point);
    q4.push(now);

    int max = 0;

    struct node tmp;
    while(!q4.empty())
    {
        tmp = q4.front();
        //cout<<"RIGHT x= "<<tmp.i<<" y= "<<tmp.j<<" point= "<<tmp.point<< " " <<arr[tmp.i][tmp.j] <<endl;
        check4[tmp.i][tmp.j]=1;
        q4.pop();

        if(tmp.point > max)
            max = tmp.point;

        stop = clock();
        duration = (double(stop) - double(start)) / CLOCKS_PER_SEC;
        if(duration >= 0.9)
            return max;


        for(int k = 0; k < 4; k++)
        {
            if(check4[tmp.i+X[k]][tmp.j+Y[k]] == 1 || !valid(tmp.i+X[k], tmp.j+Y[k]))
                continue;

            struct node to;
            to.i = tmp.i + X[k];
            to.j = tmp.j + Y[k];
            to.point = add_points(tmp.i+X[k], tmp.j+Y[k], tmp.point);
            q4.push(to);

        }

    }

    return max;
}


bool valid(int x, int y){
    return (
            x >= 0 && x < M && y >=0 && y < N &&
            arr[x][y] != 'x' && arr[x][y] != 'b' &&
            arr[x][y] != 'A' && arr[x][y] != 'B'
           );
}

string direction(int M, int x, int y, int point)
{
    string ans;

    int sum_up = -1, sum_down = -1, sum_right = -1, sum_left = -1;

    if(x != 0 && arr[x - 1][y] != 'x' && arr[x-1][y] != 'A' && arr[x-1][y] != 'B')
        sum_up = up(x-1, y, point);
    if(x != M - 1 && arr[x+1][y] != 'x' && arr[x+1][y] != 'A' && arr[x+1][y] != 'B'){
        //cout << "EVAN" << endl;
        sum_down = down(x+1, y, point);}
    if(y != M - 1 && arr[x][y+1] != 'x' && arr[x][y+1] != 'A' && arr[x][y+1] != 'B')
        sum_right = right(x, y+1, point);
    if(y != 0 && arr[x][y-1] != 'x' && arr[x][y-1] != 'A' && arr[x][y-1] != 'B')
        sum_left = left(x, y-1, point);

    //cout << "SUM_UP = " << sum_up << endl << "SUM_DOWN = " << sum_down << endl << "SUM_LEFT = " << sum_left << endl << "SUM_RIGHT = " << sum_right << endl;
    return cmp(sum_up, sum_down, sum_left, sum_right, x, y);

}

string cmp(int a, int b, int c, int d, int x, int y)
{
    int max = 0;

    if(a > max)
        max = a;
    if(b > max)
        max = b;
    if(c > max)
        max = c;
    if(d > max)
        max = d;

    if(max == a)
    {
        return "UP";
        //arr[x][y-1] = '.';
    }
    else if(max == b)
    {
        return "DOWN";
        //arr[x][y+1] = '.';
    }
    else if(max == c)
    {
        return "LEFT";
        //arr[x-1][y] = '.';
    }
    else
    {
        return "RIGHT";
        //arr[x+1][y] = '.';
    }



}


int add_points(int x, int y, int sum)
{
    if(arr[x][y] == 'm')
        sum += 1;
    else if(arr[x][y] == 'n')
        sum -= 1;
    else if(arr[x][y] == 's')
        sum *= 2;
    else if(arr[x][y] == 't')
        sum /= 2;
    else 
        sum += 0;

    return sum;

}

int main(){

    int flag = 1;
    int A_points, B_points, A_x, A_y, B_x, B_y, current_x, current_y;
    char current_player;
    char b, m, n, s, t, x;

    start = clock();

    /* b = Bomb (stop 3 rounds);
     * m = Mushroom (+1);
     * n = Toxic Mushroom (-1);
     * s = Star (*2);
     * t = Toxic Star (/2); 
     * x = wall */

    cin >> Round >> M >> N; //Round; Map = M x M;

    for(int i = 0; i < 20; ++i)
        for(int j = 0; j < 20; ++j)
            arr[i][j] = '0';

    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            cin >> arr[i][j];
            if(arr[i][j] == 'A')
            {
                A_x = i;
                A_y = j;
            }
            else if(arr[i][j] == 'B')
            {
                B_x = i;
                B_y = j;
            }
        }
    }

    cin >> A_points >> B_points;

    cin >> current_player;

    int current_points;

    if(current_player == 'A')
    {
        current_x = A_x;
        current_y = A_y;
        current_points = A_points;
    }
    else if(current_player == 'B')
    {
        current_x = B_x;
        current_y = B_y;
        current_points = B_points;
    }

    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j)
            if(arr[i][j] == 'b' || arr[i][j] == 'm' || arr[i][j] == 'n' || arr[i][j] == 's' || arr[i][j] == 't')
                flag = 1;

    if(flag == 0)
        return 0;

    //cout << current_x << " " << current_y << endl;

    cout << direction(M, current_x, current_y, current_points) << endl;

}
