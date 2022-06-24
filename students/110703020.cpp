//為count做改良

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char arr[30][30] = {0};
int wallwarming[30][30] = {0};
int starcount = -1;
int wall_distance = 0;
int wall_opponent_distance = 0;
int wallx = 0;
int wally = 0;
double max_percentage = -999.0;
int mypoint = 0;
int opponentpoint = 0;

clock_t start_t, finish_t;
double total_t = 0;
int maxpoint = 0;
int way = 1;
int remarki = 0;
int remarkj = 0;
int COUNT = 999;
char opponent;
int opponentx, opponenty, myx, myy;
int findopponentway = -1;
int opponent_starcount = 0;
int opponent_starcount_distance = 0;
void opponent_find_star(char arr[30][30], int opponentmap[30][30], int wallwarming[30][30], int x, int y, int m, int n, int count)
{
    if (arr[x][y] == 's' || arr[x][y] == 'm')
    {
        count++;
    }
    if (wallwarming[x][y] == -3)
    {
        opponent_starcount_distance = opponentmap[x][y];
        opponent_starcount = count;
        return;
    }
    else if (wallwarming[x][y] == 0)
    {
        return;
    }
    if (x - 1 >= 0 && (opponentmap[x - 1][y] == opponentmap[x][y] + 1))
    {
        opponent_find_star(arr, opponentmap, wallwarming, x - 1, y, m, n, count);
    }

    if (x + 1 < m && (opponentmap[x + 1][y] == opponentmap[x][y] + 1))
    {
        opponent_find_star(arr, opponentmap, wallwarming, x + 1, y, m, n, count);
    }
    if (y - 1 >= 0 && (opponentmap[x][y - 1] == opponentmap[x][y] + 1))
    {
        opponent_find_star(arr, opponentmap, wallwarming, x, y - 1, m, n, count);
    }
    if (y + 1 < n && (opponentmap[x][y + 1] == opponentmap[x][y] + 1))
    {
        opponent_find_star(arr, opponentmap, wallwarming, x, y + 1, m, n, count);
    }
}

void find_star(char arr[30][30], int myBFSmap[30][30], int wallwarming[30][30], int x, int y, int m, int n, int count)
{
    if (arr[x][y] == 's' || arr[x][y] == 'm')
    {
        count++;
    }
    if (wallwarming[x][y] == -3)
    {
        starcount = count;
        return;
    }
    else if (wallwarming[x][y] == 0)
    {
        return;
    }
    if (x - 1 >= 0 && (myBFSmap[x - 1][y] == myBFSmap[x][y] + 1))
    {
        find_star(arr, myBFSmap, wallwarming, x - 1, y, m, n, count);
    }

    if (x + 1 < m && (myBFSmap[x + 1][y] == myBFSmap[x][y] + 1))
    {
        find_star(arr, myBFSmap, wallwarming, x + 1, y, m, n, count);
    }
    if (y - 1 >= 0 && (myBFSmap[x][y - 1] == myBFSmap[x][y] + 1))
    {
        find_star(arr, myBFSmap, wallwarming, x, y - 1, m, n, count);
    }
    if (y + 1 < n && (myBFSmap[x][y + 1] == myBFSmap[x][y] + 1))
    {
        find_star(arr, myBFSmap, wallwarming, x, y + 1, m, n, count);
    }
}

void countwall_distance(int myBFSmap[30][30], int x, int y, int m, int n)
{
    // printf("%d %d\n", x, y);
    if (wallwarming[x][y] == 0)
    {
        wallx = x;
        wally = y;
        wall_distance = myBFSmap[x][y] - 1;
        return;
    }

    if (x - 1 >= 0 && (myBFSmap[x - 1][y] == myBFSmap[x][y] + 1))
    {
        countwall_distance(myBFSmap, x - 1, y, m, n);
    }

    if (x + 1 < m && (myBFSmap[x + 1][y] == myBFSmap[x][y] + 1))
    {
        countwall_distance(myBFSmap, x + 1, y, m, n);
    }
    if (y - 1 >= 0 && (myBFSmap[x][y - 1] == myBFSmap[x][y] + 1))
    {
        countwall_distance(myBFSmap, x, y - 1, m, n);
    }
    if (y + 1 < n && (myBFSmap[x][y + 1] == myBFSmap[x][y] + 1))
    {
        countwall_distance(myBFSmap, x, y + 1, m, n);
    }
}

void findB(int myBFSmap[30][30], int x, int y, int m, int n, int distance)
{ //!! x上下 y左右
    if (arr[x][y] == 't' || arr[x][y] == 'n' || arr[x][y] == 'b')
    {
        return;
    }

    if (distance == 1)
    {
        if (x - 1 >= 0 && (myBFSmap[x - 1][y] == 0))
        {
            findopponentway = 4;
            return;
        }
        if (x + 1 < m && (myBFSmap[x + 1][y] == 0))
        {
            findopponentway = 3;
            return;
        }
        if (y - 1 >= 0 && (myBFSmap[x][y - 1] == 0))
        {
            findopponentway = 1;
            return;
        }
        if (y + 1 < n && (myBFSmap[x][y + 1] == 0))
        {
            findopponentway = 2;
            return;
        }
    }

    if (x - 1 >= 0 && (myBFSmap[x - 1][y] == distance - 1) && myBFSmap[x - 1][y] != -1)
    {
        findB(myBFSmap, x - 1, y, m, n, distance - 1);
    }
    if (x + 1 < m && (myBFSmap[x + 1][y] == distance - 1) && myBFSmap[x + 1][y] != -1)
    {
        findB(myBFSmap, x + 1, y, m, n, distance - 1);
    }
    if (y - 1 >= 0 && (myBFSmap[x][y - 1] == distance - 1) && myBFSmap[x][y - 1] != -1)
    {
        findB(myBFSmap, x, y - 1, m, n, distance - 1);
    }
    if (y + 1 < n && (myBFSmap[x][y + 1] == distance - 1) && myBFSmap[x][y + 1] != -1)
    {
        findB(myBFSmap, x, y + 1, m, n, distance - 1);
    }
}

void wallwarmingfill(int wallwarming[30][30], int x, int y, int m, int n);

void wallwarmingfill(int wallwarming[30][30], int x, int y, int m, int n)
{
    int flag = 0;
    if (wallwarming[x][y] == -3)
    {
        flag = 1;
    }
    if (flag == 0)
    {
        int count = 4;
        if (x - 1 < 0 || wallwarming[x - 1][y] != 0)
        {
            count--;
        }
        if (x + 1 >= m || wallwarming[x + 1][y] != 0)
        {
            count--;
        }
        if (y - 1 < 0 || wallwarming[x][y - 1] != 0)
        {
            count--;
        }
        if (y + 1 >= n || wallwarming[x][y + 1] != 0)
        {
            count--;
        }
        if (count >= 2)
        {
            return;
        }

        wallwarming[x][y] = -2;
    }

    if (x - 1 >= 0 && (wallwarming[x - 1][y] == 0))
    {
        wallwarmingfill(wallwarming, x - 1, y, m, n);
    }
    if (x + 1 < m && (wallwarming[x + 1][y] == 0))
    {
        wallwarmingfill(wallwarming, x + 1, y, m, n);
    }
    if (y - 1 >= 0 && (wallwarming[x][y - 1] == 0))
    {
        wallwarmingfill(wallwarming, x, y - 1, m, n);
    }
    if (y + 1 < n && (wallwarming[x][y + 1] == 0))
    {
        wallwarmingfill(wallwarming, x, y + 1, m, n);
    }
}

void complete_search1(char arr[30][30], int x, int y, int m, int n, int count, int check, int point)
{

    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    if ((double)total_t > 0.3)
    {
        return;
    }
    // printf("%f %f %f %d\n", (double)start_t, (double)finish_t, (double)total_t, testnumber);

    // //printf("%d %d %d %d\n", x, y, m, n);
    if (arr[x][y] == 'x' || arr[x][y] == opponent)
    {
        return;
    }
    // //printf("%d\n", direction);
    if (arr[x][y] == 'b')
    {
        count += 3;
    }
    else if (arr[x][y] == 'm')
    {
        point += 1;
    }
    else if (arr[x][y] == 'n')
    {
        point -= 1;
    }
    else if (arr[x][y] == 's')
    {
        point *= 2;
    }
    else if (arr[x][y] == 't')
    {
        point /= 2;
    }

    if (count >= 20)
    {
        return;
    }

    double p = (double)(point - mypoint) / count;
    if (p > max_percentage)
    {
        max_percentage = p;
        maxpoint = point;
        way = 1;
        remarki = x;
        remarkj = y;
        COUNT = count;
    }

    if (check != 2)
    {
        if (x + 1 < m && x >= 0 && y < n && y >= 0)
        {
            complete_search1(arr, x + 1, y, m, n, count + 1, 1, point);
        }
    }
    if (check != 1)
    {
        if (x < m && x - 1 >= 0 && y < n && y >= 0)
        {
            complete_search1(arr, x - 1, y, m, n, count + 1, 2, point);
        }
    }
    if (check != 4)
    {
        if (x < m && x >= 0 && y + 1 < n && y >= 0)
        {
            complete_search1(arr, x, y + 1, m, n, count + 1, 3, point);
        }
    }
    if (check != 3)
    {
        if (x < m && x >= 0 && y < n && y - 1 >= 0)
        {
            complete_search1(arr, x, y - 1, m, n, count + 1, 4, point);
        }
    }
}

void complete_search2(char arr[30][30], int x, int y, int m, int n, int count, int check, int point)
{

    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    if ((double)total_t > 0.51)
    {
        return;
    }
    // printf("%f %f %f %d\n", (double)start_t, (double)finish_t, (double)total_t, testnumber);

    // //printf("%d %d %d %d\n", x, y, m, n);
    if (arr[x][y] == 'x' || arr[x][y] == opponent)
    {
        return;
    }
    // //printf("%d\n", direction);
    if (arr[x][y] == 'b')
    {
        count += 3;
    }
    else if (arr[x][y] == 'm')
    {
        point += 1;
    }
    else if (arr[x][y] == 'n')
    {
        point -= 1;
    }
    else if (arr[x][y] == 's')
    {
        point *= 2;
    }
    else if (arr[x][y] == 't')
    {
        point /= 2;
    }

    if (count >= 20)
    {
        return;
    }
    double p = (double)(point - mypoint) / count;
    if (p > max_percentage)
    {
        max_percentage = p;
        maxpoint = point;
        way = 2;
        remarki = x;
        remarkj = y;
        COUNT = count;
    }

    if (check != 2)
    {
        if (x + 1 < m && x >= 0 && y < n && y >= 0)
        {
            complete_search2(arr, x + 1, y, m, n, count + 1, 1, point);
        }
    }
    if (check != 1)
    {
        if (x < m && x - 1 >= 0 && y < n && y >= 0)
        {
            complete_search2(arr, x - 1, y, m, n, count + 1, 2, point);
        }
    }
    if (check != 4)
    {
        if (x < m && x >= 0 && y + 1 < n && y >= 0)
        {
            complete_search2(arr, x, y + 1, m, n, count + 1, 3, point);
        }
    }
    if (check != 3)
    {
        if (x < m && x >= 0 && y < n && y - 1 >= 0)
        {
            complete_search2(arr, x, y - 1, m, n, count + 1, 4, point);
        }
    }
}

void complete_search3(char arr[30][30], int x, int y, int m, int n, int count, int check, int point)
{
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    if ((double)total_t > 0.72)
    {
        return;
    }
    // printf("%f %f %f %d\n", (double)start_t, (double)finish_t, (double)total_t, testnumber);

    // //printf("%d %d %d %d\n", x, y, m, n);
    if (arr[x][y] == 'x' || arr[x][y] == opponent)
    {
        return;
    }
    // //printf("%d\n", direction);
    if (arr[x][y] == 'b')
    {
        count += 3;
    }
    else if (arr[x][y] == 'm')
    {
        point += 1;
    }
    else if (arr[x][y] == 'n')
    {
        point -= 1;
    }
    else if (arr[x][y] == 's')
    {
        point *= 2;
    }
    else if (arr[x][y] == 't')
    {
        point /= 2;
    }

    if (count >= 20)
    {
        return;
    }

    double p = (double)(point - mypoint) / count;
    if (p > max_percentage)
    {
        max_percentage = p;
        maxpoint = point;
        way = 3;
        remarki = x;
        remarkj = y;
        COUNT = count;
    }

    if (check != 2)
    {
        if (x + 1 < m && x >= 0 && y < n && y >= 0)
        {
            complete_search3(arr, x + 1, y, m, n, count + 1, 1, point);
        }
    }
    if (check != 1)
    {
        if (x < m && x - 1 >= 0 && y < n && y >= 0)
        {
            complete_search3(arr, x - 1, y, m, n, count + 1, 2, point);
        }
    }
    if (check != 4)
    {
        if (x < m && x >= 0 && y + 1 < n && y >= 0)
        {
            complete_search3(arr, x, y + 1, m, n, count + 1, 3, point);
        }
    }
    if (check != 3)
    {
        if (x < m && x >= 0 && y < n && y - 1 >= 0)
        {
            complete_search3(arr, x, y - 1, m, n, count + 1, 4, point);
        }
    }
}

void complete_search4(char arr[30][30], int x, int y, int m, int n, int count, int check, int point)
{

    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    if ((double)total_t > 0.93)
    {
        return;
    }
    // printf("%f %f %f %d\n", (double)start_t, (double)finish_t, (double)total_t, testnumber);

    // //printf("%d %d %d %d\n", x, y, m, n);
    if (arr[x][y] == 'x' || arr[x][y] == opponent)
    {
        return;
    }
    // //printf("%d\n", direction);
    if (arr[x][y] == 'b')
    {
        count += 3;
    }
    else if (arr[x][y] == 'm')
    {
        point += 1;
    }
    else if (arr[x][y] == 'n')
    {
        point -= 1;
    }
    else if (arr[x][y] == 's')
    {
        point *= 2;
    }
    else if (arr[x][y] == 't')
    {
        point /= 2;
    }

    if (count >= 20)
    {
        return;
    }

    double p = (double)(point - mypoint) / count;
    if (p > max_percentage)
    {
        max_percentage = p;
        maxpoint = point;
        way = 4;
        remarki = x;
        remarkj = y;
        COUNT = count;
    }

    if (check != 2)
    {
        if (x + 1 < m && x >= 0 && y < n && y >= 0)
        {
            complete_search4(arr, x + 1, y, m, n, count + 1, 1, point);
        }
    }
    if (check != 1)
    {
        if (x < m && x - 1 >= 0 && y < n && y >= 0)
        {
            complete_search4(arr, x - 1, y, m, n, count + 1, 2, point);
        }
    }
    if (check != 4)
    {
        if (x < m && x >= 0 && y + 1 < n && y >= 0)
        {
            complete_search4(arr, x, y + 1, m, n, count + 1, 3, point);
        }
    }
    if (check != 3)
    {
        if (x < m && x >= 0 && y < n && y - 1 >= 0)
        {
            complete_search4(arr, x, y - 1, m, n, count + 1, 4, point);
        }
    }
}

int main()
{
    start_t = clock();
    int wallwarmingcount = 0;
    int opponentmap[30][30] = {0};
    int opponentstack[10000][2] = {0};
    int opponenttop = 0;
    int round;
    int m;
    int n;
    scanf("%d %d %d", &round, &m, &n);
    int map_m;
    int map_s;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf(" %c", &arr[i][j]);
            if (arr[i][j] == 'm')
            {
                map_m++;
            }
            else if (arr[i][j] == 's')
            {
                map_s++;
            }
        }
    }
    int Apoint;
    int Bpoint;
    char me;
    scanf("%d %d %c", &Apoint, &Bpoint, &me);

    if (me == 'A')
    {
        mypoint = Apoint;
        opponentpoint = Bpoint;
        opponent = 'B';
    }
    if (me == 'B')
    {
        mypoint = Bpoint;
        opponentpoint = Apoint;

        opponent = 'A';
    }

    //做出opponent的map↓
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (arr[i][j] == opponent)
            {
                opponentx = i;
                opponenty = j;
                // opponentmap[i][j] = -1;
                opponentstack[0][0] = i;
                opponentstack[0][1] = j;
            }
            if (arr[i][j] == 'x')
            {
                opponentmap[i][j] = -1;
                wallwarming[i][j] = -1;
            }
        }
    }

    for (int i = 0; i <= opponenttop; i++)
    {
        int a = opponentstack[i][0];
        int b = opponentstack[i][1];
        if (a - 1 >= 0 && opponentmap[a - 1][b] == 0 && ((a - 1) != opponentstack[0][0] || b != opponentstack[0][1]))
        {
            // //printf("%d\n",opponentmap[a - 1][b]);
            opponentmap[a - 1][b] = opponentmap[a][b] + 1;
            opponenttop++;
            opponentstack[opponenttop][0] = a - 1;
            opponentstack[opponenttop][1] = b;
        }
        if (a + 1 < m && opponentmap[a + 1][b] == 0 && ((a + 1) != opponentstack[0][0] || b != opponentstack[0][1]))
        {
            // //printf("%d\n",opponentmap[a + 1][b]);
            opponentmap[a + 1][b] = opponentmap[a][b] + 1;
            opponenttop++;
            opponentstack[opponenttop][0] = a + 1;
            opponentstack[opponenttop][1] = b;
        }
        if (b + 1 < n && opponentmap[a][b + 1] == 0 && ((a) != opponentstack[0][0] || (b + 1) != opponentstack[0][1]))
        {
            // //printf("%d\n",opponentmap[a][b + 1]);
            opponentmap[a][b + 1] = opponentmap[a][b] + 1;
            opponenttop++;
            opponentstack[opponenttop][0] = a;
            opponentstack[opponenttop][1] = b + 1;
        }
        if (b - 1 >= 0 && opponentmap[a][b - 1] == 0 && (a != opponentstack[0][0] || (b - 1) != opponentstack[0][1]))
        {
            // //printf("%d\n",opponentmap[a][b - 1]);
            opponentmap[a][b - 1] = opponentmap[a][b] + 1;
            opponenttop++;
            opponentstack[opponenttop][0] = a;
            opponentstack[opponenttop][1] = b - 1;
        }
    }
    //做出opponent的map↑

    // myBFSMAP製作↓
    int myBFSmap[30][30] = {0};
    int myBFSstack[10000][2] = {0};
    int myBFStop = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (arr[i][j] == me)
            {
                myx = i;
                myy = j;
                // myBFSmap[i][j] = -1;
                myBFSstack[0][0] = i;
                myBFSstack[0][1] = j;
            }
            if (arr[i][j] == 'x')
            {
                myBFSmap[i][j] = -1;
                wallwarming[i][j] = -1;
            }
        }
    }

    for (int i = 0; i <= myBFStop; i++)
    {
        int a = myBFSstack[i][0];
        int b = myBFSstack[i][1];
        if (a - 1 >= 0 && myBFSmap[a - 1][b] == 0 && ((a - 1) != myBFSstack[0][0] || b != myBFSstack[0][1]))
        {
            // printf("%d\n",myBFSmap[a - 1][b]);
            myBFSmap[a - 1][b] = myBFSmap[a][b] + 1;
            myBFStop++;
            myBFSstack[myBFStop][0] = a - 1;
            myBFSstack[myBFStop][1] = b;
        }
        if (a + 1 < m && myBFSmap[a + 1][b] == 0 && ((a + 1) != myBFSstack[0][0] || b != myBFSstack[0][1]))
        {
            // printf("%d\n",myBFSmap[a + 1][b]);
            myBFSmap[a + 1][b] = myBFSmap[a][b] + 1;
            myBFStop++;
            myBFSstack[myBFStop][0] = a + 1;
            myBFSstack[myBFStop][1] = b;
        }
        if (b + 1 < n && myBFSmap[a][b + 1] == 0 && ((a) != myBFSstack[0][0] || (b + 1) != myBFSstack[0][1]))
        {
            // printf("%d\n",myBFSmap[a][b + 1]);
            myBFSmap[a][b + 1] = myBFSmap[a][b] + 1;
            myBFStop++;
            myBFSstack[myBFStop][0] = a;
            myBFSstack[myBFStop][1] = b + 1;
        }
        if (b - 1 >= 0 && myBFSmap[a][b - 1] == 0 && (a != myBFSstack[0][0] || (b - 1) != myBFSstack[0][1]))
        {
            // printf("%d\n",myBFSmap[a][b - 1]);
            myBFSmap[a][b - 1] = myBFSmap[a][b] + 1;
            myBFStop++;
            myBFSstack[myBFStop][0] = a;
            myBFSstack[myBFStop][1] = b - 1;
        }
    }

    // myBFSMAP製作↑

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (wallwarming[i][j] == -2)
            {
                wallwarmingcount++;
            }
        }
    }

    //計算分數能否贏或是牆太多 直接去堵他↓
    int opponentdistance = myBFSmap[opponentx][opponenty]; //!!計算和對手距離
    int temp_mypoint = mypoint;
    for (int i = 0; i < map_m; i++)
    {
        temp_mypoint++;
    }
    for (int i = 0; i < map_s; i++)
    {
        temp_mypoint *= 2;
    }
    if (temp_mypoint < opponentpoint)
    {
        if (opponentdistance != 1)
        {

            // printf("%d %d %d\n",opponentx,opponenty,opponentdistance);
            findB(myBFSmap, opponentx, opponenty, m, n, opponentdistance);
            if (findopponentway == 1)
            {
                printf("RIGHT\n");
                return 0;
            }
            else if (findopponentway == 2)
            {
                printf("LEFT\n");
                return 0;
            }
            else if (findopponentway == 3)
            {
                printf("UP\n");
                return 0;
            }
            else if (findopponentway == 4)
            {
                printf("DOWN\n");
                return 0;
            }
        }
    }
    // 計算能否贏或是牆太多 直接去堵他↑

    /*for (int i = 0; i < m; i++)
   {
       for (int j = 0; j < n; j++)
       {
           //printf("%2d ", wallwarming[i][j]);
       }
       //printf("\n");
   }
   //printf("\n");*/
    //做出堵牆警告↓
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (wallwarming[i][j] == 0)
            {
                int wallwarmingnum = 4;
                if (i - 1 < 0 || wallwarming[i - 1][j] == -1)
                {
                    wallwarmingnum--;
                }
                if (i + 1 >= m || wallwarming[i + 1][j] == -1)
                {
                    wallwarmingnum--;
                }
                if (j - 1 < 0 || wallwarming[i][j - 1] == -1)
                {
                    wallwarmingnum--;
                }
                if (j + 1 >= n || wallwarming[i][j + 1] == -1)
                {
                    wallwarmingnum--;
                }

                if (wallwarmingnum == 1)
                {
                    wallwarming[i][j] = -3;
                }
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (wallwarming[i][j] == -3)
            {
                wallwarmingfill(wallwarming, i, j, m, n);
            }
        }
    }

    //做出堵牆警告↑
    //判斷周圍有沒有非被堵(-2)或牆(-1)的地方↓
    int can_go_out = 0;
    if (myx - 1 >= 0 && wallwarming[myx - 1][myy] == 0)
    {
        can_go_out = 1;
    }
    else if (myx + 1 < m && wallwarming[myx + 1][myy] == 0)
    {
        can_go_out = 1;
    }
    else if (myy - 1 >= 0 && wallwarming[myx][myy - 1] == 0)
    {
        can_go_out = 1;
    }
    else if (myy + 1 < n && wallwarming[myx][myy + 1] == 0)
    {
        can_go_out = 1;
    }

    //判斷周圍有沒有非被堵(-2)或牆(-1)的地方↑
    //堵牆警告做事↓

    //如果發現和對手距離只剩1，那就不要進去-2裡了，直接把路封起來↓
    if (opponentdistance == 1 && can_go_out == 1)
    {
        if (myx - 1 >= 0 && wallwarming[myx - 1][myy] == -2)
        {
            arr[myx - 1][myy] = 'x';
        }
        else if (myx + 1 < m && wallwarming[myx + 1][myy] == -2)
        {
            arr[myx + 1][myy] = 'x';
        }
        else if (myy - 1 >= 0 && wallwarming[myx][myy - 1] == -2)
        {
            arr[myx][myy - 1] = 'x';
        }
        else if (myy + 1 < n && wallwarming[myx][myy + 1] == -2)
        {
            arr[myx][myy + 1] = 'x';
        }
    }
    //如果發現和對手距離只剩1，那就不要進去-2裡了，直接把路封起來↑

    //如果已經在-2裡，看會不會被堵住，會的話就直接出來↓
    //宣告在全域變數↓
    // int wall_distance = 0;
    // int wall_opponent_distance = 0;

    if (wallwarming[myx][myy] == -2)
    {
        countwall_distance(myBFSmap, myx, myy, m, n); //得到wall_distance和wallx,wally 但是 wallx,wally是在o的地方
        wall_opponent_distance = opponentmap[wallx][wally] + 1;
        if ((wall_opponent_distance == wall_distance || wall_opponent_distance - wall_distance == 3) && opponentdistance != 1)
        {
            findB(myBFSmap, opponentx, opponenty, m, n, opponentdistance);
            if (findopponentway == 1)
            {
                printf("RIGHT\n");
                return 0;
            }
            else if (findopponentway == 2)
            {
                printf("LEFT\n");
                return 0;
            }
            else if (findopponentway == 3)
            {
                printf("UP\n");
                return 0;
            }
            else if (findopponentway == 4)
            {
                printf("DOWN\n");
                return 0;
            }
        }
        if (wall_distance > wall_opponent_distance || wall_opponent_distance - wall_distance == 1)
        {
            find_star(arr, myBFSmap, wallwarming, myx, myy, m, n, 0);
            if (starcount == 0 && opponentdistance != 1) //裡面沒東西所以直接出來
            {
                findB(myBFSmap, opponentx, opponenty, m, n, opponentdistance);
                if (findopponentway == 1)
                {
                    printf("RIGHT\n");
                    return 0;
                }
                else if (findopponentway == 2)
                {
                    printf("LEFT\n");
                    return 0;
                }
                else if (findopponentway == 3)
                {
                    printf("UP\n");
                    return 0;
                }
                else if (findopponentway == 4)
                {
                    printf("DOWN\n");
                    return 0;
                }
            }
            else
            {
                arr[wallx][wally] = 'x';
            }
        }
    }

    //如果已經在-2裡，看會不會被堵住，會的話就直接出來↑

    //堵牆警告做事↑

    if (me == 'A')
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (arr[i][j] == me)
                {
                    if (j + 1 < n && arr[i][j + 1] != 'x' && arr[i][j + 1] != 'B')
                    {
                        complete_search1(arr, i, j + 1, m, n, 1, 0, Apoint); //右
                        // printf("7777777");
                    }
                    if (j - 1 >= 0 && arr[i][j - 1] != 'x' && arr[i][j - 1] != 'B')
                    {
                        complete_search2(arr, i, j - 1, m, n, 1, 0, Apoint); //左
                        // printf("7777777");
                    }
                    if (i - 1 >= 0 && arr[i - 1][j] != 'x' && arr[i - 1][j] != 'B')
                    {
                        complete_search3(arr, i - 1, j, m, n, 1, 0, Apoint); //上
                        // printf("7777777");
                    }

                    if (i + 1 < m && arr[i + 1][j] != 'x' && arr[i + 1][j] != 'B')
                    {
                        complete_search4(arr, i + 1, j, m, n, 1, 0, Apoint); //下
                        // printf("7777777");
                    }

                    // //printf("%d %d %d %d", remarki, remarkj, COUNT, maxpoint);
                }
            }
        }
    }
    else if (me == 'B')
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (arr[i][j] == me)
                {
                    if (j + 1 < n && arr[i][j + 1] != 'x' && arr[i][j + 1] != 'A')
                    {
                        complete_search1(arr, i, j + 1, m, n, 1, 0, Bpoint); //右
                    }
                    if (j - 1 >= 0 && arr[i][j - 1] != 'x' && arr[i][j - 1] != 'A')
                    {
                        complete_search2(arr, i, j - 1, m, n, 1, 0, Bpoint); //左
                    }
                    // //printf("%d %d %d %d", remarki, remarkj, COUNT, maxpoint);
                    if (i - 1 >= 0 && arr[i - 1][j] != 'x' && arr[i - 1][j] != 'A')
                    {
                        complete_search3(arr, i - 1, j, m, n, 1, 0, Bpoint); //上
                    }

                    if (i + 1 < m && arr[i + 1][j] != 'x' && arr[i + 1][j] != 'A')
                    {
                        complete_search4(arr, i + 1, j, m, n, 1, 0, Bpoint); //下
                    }
                }
            }
        }
    }

    int flag = 0;
    if (map_s > 0 && opponentdistance!=1)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (arr[i][j] == 's')
                {
                    flag = 1;
                    double p = (double)mypoint / myBFSmap[i][j];
                    if (p > max_percentage)
                    {
                        max_percentage = p;
                        maxpoint = mypoint * 2;
                        remarki = i;
                        remarkj = j;
                        COUNT = myBFSmap[i][j];
                    }
                }
            }
        }
    }
    else if (maxpoint == mypoint && opponentdistance!=1)
    {
        int maxdistance = 999;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (arr[i][j] == 'm')
                {
                    if (myBFSmap[i][j] < maxdistance)
                    {
                        max_percentage=0.2;
                        flag = 1;
                        maxdistance = myBFSmap[i][j];
                        remarki = i;
                        remarkj = j;
                    }
                }
            }
        }
    }

    if (wallwarming[opponentx][opponenty] == -2)
    {
        opponent_find_star(arr, opponentmap, wallwarming, opponentx, opponenty, m, n, 0);
        finish_t = clock();
        total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
        if ((double)total_t > 0.98)
        {
            if (way == 1)
            {
                printf("RIGHT\n");
                return 0;
            }
            else if (way == 2)
            {
                printf("LEFT\n");
                return 0;
            }
            else if (way == 3)
            {
                printf("UP\n");
                return 0;
            }
            else if (way == 4)
            {
                printf("DOWN\n");
                return 0;
            }
        }

        // printf("opponent_starcount:%dopponent_starcount_distance:%d\n",opponent_starcount,opponent_starcount_distance);
        if (opponent_starcount >= 1 && opponent_starcount_distance * 2 - 1 > opponentdistance && max_percentage < 0.5 && opponentdistance <= 10 && opponentdistance!=1)
        {
            // printf("remarki:%d remarkj:%d COUNT:%d maxpoint:%d max_percentage:%f", remarki, remarkj, COUNT, maxpoint, max_percentage);
            findopponentway = -1;
            findB(myBFSmap, opponentx, opponenty, m, n, opponentdistance);
            if (findopponentway == 1)
            {
                printf("RIGHT\n");
                return 0;
            }
            else if (findopponentway == 2)
            {
                printf("LEFT\n");
                return 0;
            }
            else if (findopponentway == 3)
            {
                printf("UP\n");
                return 0;
            }
            else if (findopponentway == 4)
            {
                printf("DOWN\n");
                return 0;
            }
        }
        countwall_distance(myBFSmap, myx, myy, m, n); //得到wall_distance和wallx,wally 但是 wallx,wally是在o的地方
        wall_opponent_distance = opponentmap[wallx][wally] + 1;
        if (((wall_distance - wall_opponent_distance == 1) || (wall_opponent_distance > wall_distance)) && opponentdistance!=1)
        {
            findopponentway = -1;
            findB(myBFSmap, opponentx, opponenty, m, n, opponentdistance);
            if (findopponentway == 1)
            {
                printf("RIGHT\n");
                return 0;
            }
            else if (findopponentway == 2)
            {
                printf("LEFT\n");
                return 0;
            }
            else if (findopponentway == 3)
            {
                printf("UP\n");
                return 0;
            }
            else if (findopponentway == 4)
            {
                printf("DOWN\n");
                return 0;
            }
        }
    }

    if (flag == 1  &&   opponentdistance!=1)
    {
         //printf("remarki:%d remarkj:%d COUNT:%d maxpoint:%d max_percentage:%f", remarki, remarkj, COUNT, maxpoint, max_percentage);
        findB(myBFSmap, remarki, remarkj, m, n, myBFSmap[remarki][remarkj]);
        if (findopponentway == 1)
        {
            printf("RIGHT\n");
            return 0;
        }
        else if (findopponentway == 2)
        {
            printf("LEFT\n");
            return 0;
        }
        else if (findopponentway == 3)
        {
            printf("UP\n");
            return 0;
        }
        else if (findopponentway == 4)
        {
            printf("DOWN\n");
            return 0;
        }
    }
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    // printf("finish:%f %f %f\n", (double)start_t, (double)finish_t, (double)total_t);
    if (way == 1)
    {
        printf("RIGHT\n");
    }
    else if (way == 2)
    {
        printf("LEFT\n");
    }
    else if (way == 3)
    {
        printf("UP\n");
    }
    else if (way == 4)
    {
        printf("DOWN\n");
    }
    // printf("wall_distance:%d\n", wall_distance);
    // printf("wall_opponent_distance:%d\n", wall_opponent_distance);
    // printf("opponentdistance:%d\n", opponentdistance);
    //  printf("can_go_out:%d\n",can_go_out);
    /*for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%2d ", myBFSmap[i][j]);
        }
        printf("\n");
    }*/
    // printf("\n");
    /*for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%2d ", wallwarming[i][j]);
        }
        printf("\n");
    }*/
    // printf("starcount:%d\n", starcount);
    // //printf("opponenttop:%d\n",opponenttop);
   // printf("remarki:%d remarkj:%d COUNT:%d maxpoint:%d max_percentage:%f", remarki, remarkj, COUNT, maxpoint, max_percentage);
    /*for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }*/
    /*//printf("%d\n",round);

    //printf("%d %d\n",m,n);


    //printf("%d %d\n",Apoint,Bpoint);

    //printf("%c\n",me);*/
}