#include <stdio.h>

char maze[20][20];
int situation[20][20];  //-1代表碰壁不能走, 0代表可以走
int d[8] = {1, 0, -1, 0, 0, 1, 0, -1};
int check[20][20] = {}; //0代表沒走過 走過改成1
int T;

int expansion(int row, int col, int val, int M, int N, int round, int ten_times_after){
    if(check[row][col] == 1)
        return -100000;
    if(row >= M || row < 0 || col >= N || col < 0){
        return -100000;
    }
    if(round >= ten_times_after){
        return val;
    }  
    if(maze[row][col] == 'k')
        return -100000;
    if(situation[row][col] == 0){  
        check[row][col] == 1;
        if(maze[row][col] == '.'){
            int max = -100000;
            for(int i = 0; i < 4; i++){
                int tmp = expansion(row+d[2*i], col+d[2*i+1], val, M, N, round+1, ten_times_after);
                
                if(tmp > max){
                    max = tmp;
                }
            }
            check[row][col] == 0;
            return max;
        }
        else if(maze[row][col] == 'm'){  
            val = val + 1;
            maze[row][col] = '.';
            int max = -100000;
            for(int i = 0; i < 4; i++){
                int tmp = expansion(row+d[2*i], col+d[2*i+1], val, M, N, round+1, ten_times_after);
                if(tmp > max){
                    max = tmp;
                }
            }
            check[row][col] == 0;
            maze[row][col] = 'm';
            return max;
        }
        else if(maze[row][col] == 'b'){
            maze[row][col] = '.';
            int max = -100000;
            for(int i = 0; i < 4; i++){
                int tmp = expansion(row+d[2*i], col+d[2*i+1], val, M, N, round+4, ten_times_after);
                if(tmp > max){
                    max = tmp;
                }
            }
            check[row][col] == 0;
            maze[row][col] = 'b';
            return max;
        }
        else if(maze[row][col] == 'n'){
            val = val - 1;
            maze[row][col] = '.';

            int max = -100000;
            for(int i = 0; i < 4; i++){
                int tmp = expansion(row+d[2*i], col+d[2*i+1], val, M, N, round+1, ten_times_after);
                if(tmp > max){
                    max = tmp;
                }
            }
            check[row][col] == 0;
            maze[row][col] = 'n';
            return max;
        }
        else if(maze[row][col] == 's'){
            val = val * 2;
            maze[row][col] = '.';
            int max = -100000;
            for(int i = 0; i < 4; i++){
                int tmp = expansion(row+d[2*i], col+d[2*i+1], val, M, N, round+1, ten_times_after);
                if(tmp > max){
                    max = tmp;
                }
            }
            check[row][col] == 0;
            maze[row][col] = 's';
            return max;
        }
        else if(maze[row][col] == 't'){
            val = val / 2;
            maze[row][col] = '.';
            int max = -100000;
            for(int i = 0; i < 4; i++){
                int tmp = expansion(row+d[2*i], col+d[2*i+1], val, M, N, round+1, ten_times_after);
                if(tmp > max){
                    max = tmp;
                }
            }
            check[row][col] == 0;
            maze[row][col] = 't';
            return max;
        }
        else return val;
    }
    else if(situation[row][col] == -1){
        return -100000;
    }    
    else return val/(round-T);
}

int abs(int a){
    if(a < 0)
        return -a;
    else return a;
}
int valid(int row, int col, int M, int N){
    if(row<0 || row>=M || col<0 || col>=N)
        return 0;
    if(maze[row][col] == 'x')
        return 0;
    return 1;
}

int main(){
    int M, N, P, Q, row_A, col_A, row_B, col_B, row, col; 
    char C;
    scanf("%d\n%d %d\n", &T, &M, &N);
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N-1; j++){
            scanf("%c ",  &maze[i][j]);
            if(maze[i][j] == 'A')
                row_A = i, col_A = j;
            else if(maze[i][j] == 'B')
                row_B = i, col_B = j;
        }
        scanf("%c\n", &maze[i][N-1]);
        if(maze[i][N-1] == 'A')
            row = i, col = N-1;   //找到A的位置
        else if(maze[i][N-1] == 'B')
                row_B = i, col_B = N-1;
    }
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            if(maze[i][j] == 'x')
                situation[i][j] = -1; //牆壁不能走
            else situation[i][j] = 0; //可以走
        }
    }
    scanf("%d\n%d\n", &P, &Q);
    scanf("%c\n", &C);
    
    if(C == 'A'){
        row = row_A;
        col = col_A;
        maze[row_B][col_B] = 'k';
    }
    else if(C == 'B'){
        row = row_B;
        col = col_B;
        P = Q;
        maze[row_A][col_A] = 'k';
    }
	int value[4] = {};
    if(T > 0 ){
        maze[row][col] = '.';
        if( abs(row_A - row_B) + abs(col_A - col_B) <= 1){
            if(valid(row-2, col, M, N)||valid(row-1, col-1, M, N)||valid(row-1, col+1, M, N)){
                value[0] = expansion(row-1, col, P, M, N, T, T+13);
            }
            else
                value[0] = -100000;
            if(valid(row+2, col, M, N)||valid(row+1, col-1, M, N)||valid(row+1, col+1, M, N)){
                value[1] = expansion(row+1, col, P, M, N, T, T+13);
            }
            else
                value[1] = -100000;
            if(valid(row, col+2, M, N)||valid(row-1, col+1, M, N)||valid(row+1, col+1, M, N)){
                value[2] = expansion(row, col+1, P, M, N, T, T+13);
            }
            else
                value[2] = -100000;
            if(valid(row, col-2, M, N)||valid(row-1, col-1, M, N)||valid(row+1, col-1, M, N)){
                value[3] = expansion(row, col-1, P, M, N, T, T+13);
            }
            else
                value[3] = -100000;
        }
        else{
            value[0] = expansion(row-1, col, P, M, N, T, T+13); //up
            value[1] = expansion(row+1, col, P, M, N, T, T+13); //down
            value[2] = expansion(row, col+1, P, M, N, T, T+13); //right
            value[3] = expansion(row, col-1, P, M, N, T, T+13); //left
        }
    }
    int MAX = value[0];
    for(int i = 1; i <= 3; i++){
        if(MAX < value[i])
            MAX = value[i];
    }  
    //printf("%d", value[2]);
//  printf("%d %d %d %d ", value[0], value[1], value[2], value[3]);
    if(MAX == value[0])
        printf("UP\n");
    else if(MAX == value[1])
        printf("DOWN\n");
    else if(MAX == value[2])
        printf("RIGHT\n");
    else printf("LEFT\n");   
}

