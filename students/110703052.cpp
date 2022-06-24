#include<stdio.h>
#include<stdbool.h>

bool pass[21][21] = {false};
int path;
int M,N;
int movement(int round, int map[21][21], int x, int y, int scoreA,int path, int count, int ans, int *max){

        switch (map[x][y]){
                case -7:
                        round += 3;
                        break;
                case 3:
                        count++;
                        scoreA++;
                        break;
                case -3:
                        count--;
                        scoreA--;
                        break;
                case 10:
                        count += scoreA;
                        scoreA *= 2;
                        break;
                case -10:
                        count -= scoreA / 2;
                        scoreA /= 2;
                        break;
        }
        bool flag=false;
        if( x-1 >= 0 && map[x-1][y] != -1 && map[x-1][y] != -100 && map[x-1][y] != 100 && !pass[x-1][y]){//up
                pass[x][y] = true;
                flag = true;
                if(round == 0)
                        path = 0;
                ans=movement(round + 1, map, x-1, y,scoreA, path, count, ans, max);
                pass[x][y] = false;

        }
        if( x+1 <= M-1 && map[x+1][y] != -1 && map[x+1][y] != -100 && map[x+1][y] != 100 && !pass[x+1][y]){//down
                pass[x][y] = true;
                flag = true;
                if(round == 0)
                        path = 1;
                ans=movement(round + 1, map, x+1, y,scoreA, path, count, ans, max);
                pass[x][y] = false;
        }
        if( y-1 >= 0 && map[x][y-1] != -1 && map[x][y-1] != -100  && map[x][y-1] != 100 && !pass[x][y-1]){//left
                pass[x][y] = true;
                flag = true;
                if(round == 0)
                        path = 2;
                ans=movement(round + 1, map, x, y-1,scoreA, path, count, ans, max);
                pass[x][y] = false;
        }
        if( y+1 <= M-1 && map[x][y+1] != -1 && map[x][y+1] != -100  && map[x][y+1] != 100 && !pass[x][y+1]){//right
                pass[x][y] = true;
                flag = true;
                if(round == 0)
                        path = 3;
                ans=movement(round + 1, map, x, y+1, scoreA,path, count, ans, max);
                pass[x][y] = false;
        }
        if(!flag){
                long long cp = count *100 / round;
                if(cp < *max){

                        return ans;
                }
                *max = cp;
                ans = path;
        }
        return ans;
}
void tran(char str[21][21], int arr[21][21], int x, int y)
{
        if (str[x][y] == '.'){
                arr[x][y] = 0;
        }
        else if (str[x][y] == 'b'){
                arr[x][y] = -7;
        }
        else if (str[x][y] == 'm'){
                arr[x][y] = 3;
        }
        else if (str[x][y] == 'n'){
                arr[x][y] = -3;
        }
        else if (str[x][y] == 's'){
                arr[x][y] = 10;
        }
        else if (str[x][y] == 't'){
                arr[x][y] = -10;
        }
        else if (str[x][y] == 'x'){
                arr[x][y] = -1;
                pass[x][y] = true;
        }
        else if (str[x][y] == 'A'){
                arr[x][y] = 100;
        }
        else if (str[x][y] == 'B'){
                arr[x][y] = -100;
        }
}
int main(){
        int T;
        scanf("%d",&T);
        scanf("%d%d", &M, &N);
        int Ax , Ay, Bx, By;
        char a[21][21];
        int b[21][21];
        for(int i = 0; i < M; i++){
                for(int j = 0; j < N; j++){
                        char trash[10];
                        scanf("%s",trash);
                        a[i][j]=trash[0];
                        if(a[i][j] == 'A'){
                                Ax = i;   Ay = j;
                        }
                        if(a[i][j] == 'B'){
                                Bx = i;   By = j;
                        }

                        tran(a, b, i, j);
                }
        }
        int P, Q;
        char C[10];
        int x, y;
        int score;
        scanf("%d", &P);
        scanf("%d", &Q);
        scanf("%s", C);
        if (C[0] == 'A'){
                x = Ax;   y = Ay;
                score = P;
        }
        else{
                x = Bx;   y = By;
                score = Q;
        }
        int max = -2000000;
        int result = movement(0, b, x, y, score,-1, 0, 0, &max);
        if(result == 0)
                printf("UP\n");
        if(result == 1)
                printf("DOWN\n");
        if(result == 2)
                printf("LEFT\n");
        if(result == 3)
                printf("RIGHT\n");

}