#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

int M, N;
int countu = 0, countd = 0, countr = 0, countl = 0;
char map[20][20];
int check[20][20];
int checku[20][20];
int checkd[20][20];
int checkr[20][20];
int checkl[20][20];
int list[1000][2];
int list2[1000][2];
int stepx[4] = {-1, 1, 0, 0};
int stepy[4] = {0, 0, -1, 1};
char step[4][6] = {"UP", "DOWN", "LEFT", "RIGHT"};

bool valid(int x, int y)
{
    return (x >= 0 && x < M && y >= 0 && y < N && map[x][y] != 'x' && map[x][y] != 'A' && map[x][y] != 'B' && map[x][y] != 'b');
}

int addpoints(int nx, int ny, int tmpscore)
{
    if (map[nx][ny] == 'm')
    {
        tmpscore++;
    }
    if (map[nx][ny] == 'n')
    {
        tmpscore--;
    }
    if (map[nx][ny] == 't')
    {
        tmpscore /= 2;
    }
    if (map[nx][ny] == 's')
    {
        tmpscore *= 2;
    }
    return tmpscore;
}

bool judgesame(int sumup, int sumdown, int sumleft, int sumright)
{
    return ((sumup == sumdown && sumdown != INT_MIN) || (sumup == sumleft && sumleft != INT_MIN) || (sumup == sumright && sumright != INT_MIN) || (sumdown == sumleft && sumleft != INT_MIN) || (sumdown == sumright && sumright != INT_MIN) || (sumleft == sumright && sumright != INT_MIN));
}

int stepbfs(int x, int y)
{
    int checkstep[20][20];
    int finalstep[20][20];
    for (int m = 0; m < M; m++)
    {
        for (int n = 0; n < M; n++)
        {
            checkstep[m][n] = 0;
            finalstep[m][n] = 0;
        }
    }
    int curx, cury;
    int nx, ny;
    int count = 0;
    list2[0][0] = x;
    list2[0][1] = y;
    for (int i = 0, j = 1; i < j; i++)
    {
        curx = list2[i][0];
        cury = list2[i][1];
        if (map[curx][cury] == 'm' || map[curx][cury] == 's')
        {
            return finalstep[curx][cury];
        }
        for (int k = 0; k < 4; k++)
        {
            nx = curx + stepx[k];
            ny = cury + stepy[k];
            if (checkstep[nx][ny] == 0 && valid(nx, ny))
            {
                checkstep[nx][ny] = 1;
                finalstep[nx][ny] = finalstep[curx][cury] + 1;
                list2[j][0] = nx;
                list2[j][1] = ny;
                j++;
            }
        }
    }
    return 0;
}

int bfs(int x, int y, int score, int (*checka)[20])
{
    int curx, cury;
    int nx, ny;
    int maxpoint = 0;
    int tmpscore;
    list[0][0] = x;
    list[0][1] = y;
    tmpscore = score;
    for (int i = 0, j = 1; i < j; i++)
    {
        curx = list[i][0];
        cury = list[i][1];
        for (int k = 0; k < 4; k++)
        {
            nx = curx + stepx[k];
            ny = cury + stepy[k];
            if (checka[nx][ny] == 0 && valid(nx, ny))
            {
                checka[nx][ny] = 1;
                tmpscore = addpoints(nx, ny, tmpscore);
                list[j][0] = nx;
                list[j][1] = ny;
                maxpoint = max(maxpoint, tmpscore);
                j++;
            }
        }
    }
    return maxpoint;
}

void direction(int x, int y, int curscore)
{
    int sumup, sumdown, sumleft, sumright;
    int ans;
    if (valid(x - 1, y) && check[x - 1][y] == 0)
    {
        sumup = bfs(x - 1, y, addpoints(x - 1, y, curscore), checku);
    }
    else
        sumup = INT_MIN;
    if (valid(x + 1, y) && check[x + 1][y] == 0)
    {
        sumdown = bfs(x + 1, y, addpoints(x + 1, y, curscore), checkd);
    }
    else
        sumdown = INT_MIN;

    if (valid(x, y - 1) && check[x][y - 1] == 0)
    {

        sumleft = bfs(x, y - 1, addpoints(x, y - 1, curscore), checkl);
    }
    else
        sumleft = INT_MIN;

    if (valid(x, y + 1) && check[x][y + 1] == 0)
    {
        sumright = bfs(x, y + 1, addpoints(x, y + 1, curscore), checkr);
    }
    else
        sumright = INT_MIN;

    ans = sumup;
    ans = max(ans, sumdown);
    ans = max(ans, sumleft);
    ans = max(ans, sumright);
    int stepcountu, stepcountd, stepcountl, stepcountr;
    int ans2;
    if (judgesame(sumup, sumdown, sumleft, sumright))
    {
        if (valid(x - 1, y) && sumup != INT_MIN)
        {
            stepcountu = stepbfs(x - 1, y);
        }
        else
            stepcountu = INT_MAX;
        if (valid(x + 1, y) && sumdown != INT_MIN)
        {
            stepcountd = stepbfs(x + 1, y);
        }
        else
            stepcountd = INT_MAX;
        if (valid(x, y - 1) && sumleft != INT_MIN)
        {
            stepcountl = stepbfs(x, y - 1);
        }
        else
            stepcountl = INT_MAX;
        if (valid(x, y + 1) && sumright != INT_MIN)
        {
            stepcountr = stepbfs(x, y + 1);
        }
        else
            stepcountr = INT_MAX;
        ans2 = stepcountu;
        ans2 = min(ans2, stepcountd);
        ans2 = min(ans2, stepcountl);
        ans2 = min(ans2, stepcountr);
        if (ans2 == stepcountu)
        {
            printf("UP\n");
        }
        else if (ans2 == stepcountd)
        {
            printf("DOWN\n");
        }
        else if (ans2 == stepcountl)
        {
            printf("LEFT\n");
        }
        else if (ans2 == stepcountr)
        {
            printf("RIGHT\n");
        }
    }
    else
    {
        if (ans == sumright)
        {
            printf("RIGHT\n");
        }
        else if (ans == sumleft)
        {
            printf("LEFT\n");
        }
        else if (ans == sumup)
        {
            printf("UP\n");
        }
        else if (ans == sumdown)
        {
            printf("DOWN\n");
        }
    }
}
char tmp[100];
int main()
{
    int T, P, Q;
    int curx, cury, curscore;
    char C;
    scanf("%d%d%d", &T, &M, &N);
    getchar();
    for (int i = 0; i < M; i++)
    {
        scanf("%[^\n]", tmp);
        getchar();
        int count=0;
        for(int j=0;j<strlen(tmp);j++)
        {
            if(tmp[j]!=' ')
            {
                map[i][count]=tmp[j];
                count++;
            }

        }
    }
    scanf("%d%d %c", &P, &Q, &C);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            check[i][j] = 0;
            checku[i][j] = 0;
            checkd[i][j] = 0;
            checkl[i][j] = 0;
            checkr[i][j] = 0;
            if (C == 'A' && map[i][j] == 'A')
            {
                curx = i;
                cury = j;
                curscore = P;
                //      check[i][j]=1;
            }
            if (C == 'B' && map[i][j] == 'B')
            {
                curx = i;
                cury = j;
                curscore = Q;
                //      check[i][j]=1;
            }
            if (map[i][j] == 'x')
            {
                check[i][j] = 1;
            }
        }
    }
    direction(curx, cury, curscore);
}