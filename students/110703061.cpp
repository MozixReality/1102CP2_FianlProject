#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include <time.h>
int step, row, col, score_a, score_b, start_x, start_y, ctr_x, ctr_y, now_x, now_y;
char graph[20][20] = {}; 
int queue1[21][2] = {}; 
int queue2[21][2] = {}; 
char me; 
int check[20][20] = {}; 
int steps[20][20] = {}; 
int steps1[20][20] = {}; 
float point[4] = {}; 
float point2[4] = {}; 
int mx[] = {0, 1, 0, -1};
int my[] = {1, 0, -1, 0}; 
int a_x, a_y, b_x, b_y;
int ctr = 0;
float max = -1; 
float arr[4] = {}; 
int num = 0;


float bfs(int sx, int sy){
    float score = 0;
    if(steps[sx][sy] == -1 || sx  < 0 || sx >= col || sy < 0 || sy >= row){
        return -10000;
    }   
    now_x = sx; 
    now_y = sy; 
    //printf("%d %d", now_x, now_y);
    int rear = 0, front = 0;
    queue2[rear][0] = sx, queue2[rear][1] = sy; 
    rear++;
    for(;front < rear; front++){
        sx = queue2[front][0], sy = queue2[front][1];
        for (int i = 0; i < 4; ++i){
            if(sx + mx[i] < 0 || sx + mx[i] >= col || sy + my[i] < 0 || sy + my[i] >= row){
                continue;
            }   
            if(steps1[sx + mx[i]][sy + my[i]] != 0){ 
                continue;
            }   
            if(sx + mx[i] == now_x && sy + my[i] == now_y){
                continue;
            }   
             if(graph[sx + mx[i]][sy + my[i]] == 'x' || graph[sx + mx[i]][sy + my[i]] == 'B'||graph[sx + mx[i]][sy + my[i]] == 'A'
            ||graph[sx + mx[i]][sy + my[i]] == 't'|| graph[sx + mx[i]][sy + my[i]] == 'n'){
                steps1[sx + mx[i]][sy + my[i]] = -1;
                continue;
            }
            if(graph[sx + mx[i]][sy + my[i]] == 'b' ){
                steps1[mx[i] + sx][my[i] + sy] = steps1[sx][sy] + 3;
                queue2[rear][0] = mx[i]+sx, queue2[rear][1] = my[i]+ sy;
                ++rear;
                continue;
            }
            steps1[mx[i]+sx][my[i]+sy] = steps1[sx][sy] + 1;
            queue2[rear][0] = mx[i]+sx, queue2[rear][1] = my[i]+ sy;
            ++rear;
            if(graph[sx + mx[i]][sy + my[i]] == 'm'){
                score += 1/steps1[mx[i]+sx][my[i]+sy];
            }
            if(graph[sx + mx[i]][sy + my[i]] == 's'){
                score += score/steps1[mx[i]+sx][my[i]+sy];
            }
        }
    }
    /*for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%d ", steps1[i][j]);
        }
        printf("\n");
    }*/
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            steps1[i][j] = 0;
        }
    }
    //printf("\n");
    return score;
}

void choose(int start_x, int start_y){
    int rear = 0, front = 0;
    queue1[rear][0] = start_x, queue1[rear][1] = start_y;
    rear++;
    for(;front < rear; front++){
        start_x = queue1[front][0], start_y = queue1[front][1];
        for (int i = 0; i < 4; ++i){
            if(start_x + mx[i] < 0 || start_x + mx[i] >= col || start_y + my[i] < 0 || start_y + my[i] >= row){
                continue;
            }
             if(steps[start_x + mx[i]][start_y + my[i]] != 0){
                continue;
            }
            if(start_x + mx[i] == ctr_x && start_y + my[i] == ctr_y){
                continue;
            }
            if(graph[start_x + mx[i]][start_y + my[i]] == 'x' || graph[start_x + mx[i]][start_y + my[i]] == 'B' || graph[start_x + mx[i]][start_y + my[i]] == 'A'
            ||graph[start_x + mx[i]][start_y + my[i]] == 't'|| graph[start_x + mx[i]][start_y + my[i]] == 'n'){
                steps[start_x + mx[i]][start_y + my[i]] = -1;
                continue;
            }
            if(graph[start_x + mx[i]][start_y + my[i]] == 'b' ){
                steps[mx[i]+start_x][my[i]+start_y] = steps[start_x][start_y] + 3;
                queue1[rear][0] = mx[i]+start_x, queue1[rear][1] = my[i]+ start_y;
                ++rear;
                continue;
            }
            steps[mx[i]+start_x][my[i]+start_y] = steps[start_x][start_y] + 1;
            queue1[rear][0] = mx[i]+start_x, queue1[rear][1] = my[i]+ start_y;
            ++rear;
        }
    }
    /*for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%d ", steps[i][j]);
        }
            printf("\n");
    }*/
    arr[0] = bfs(ctr_x+mx[0], ctr_y+my[0]);
    arr[1] = bfs(ctr_x+mx[1], ctr_y+my[1]);
     arr[2] = bfs(ctr_x+mx[2], ctr_y+my[2]);
    arr[3] = bfs(ctr_x+mx[3], ctr_y+my[3]);
    //printf("%f %f %f %f", arr[0], arr[1], arr[2], arr[3]);
    for(int w = 0; w < 4; w++){
            if(arr[w] > max){
                max = arr[w];
                num = w;
            }
    }
    if(me == 'B'){
        if(arr[0] == max && arr[1] == max){
                 srand(time(NULL));
            num = rand()%2;
        }
        if(arr[0] == max && arr[2] == max){
            srand(time(NULL));
           if(rand()%2 == 0){
               num = 0;
           }
           else{
               num = 2;
           }
        }
        if(arr[0] == max && arr[3] == max){
            srand(time(NULL));
           if(rand()%2 == 0){
               num = 0;
           }
           else{
               num = 3;
           }
        }
        if(arr[2] == max && arr[1] == max){
            srand(time(NULL));
           if(rand()%2 == 0){
               num = 1;
           }
           else{
               num = 2;
           }
        }
        if(arr[3] == max && arr[1] == max){
            srand(time(NULL));
           if(rand()%2 == 0){
               num = 1;
           }
           else{
               num = 3;
           }
        }
        if(arr[3] == max && arr[2] == max){
            srand(time(NULL));
           if(rand()%2 == 0){
               num = 2;
           }
           else{
               num = 3;
                       }
        }
    }
}



int main(){
    scanf("%d\n", &step);
    scanf("%d %d\n", &row, &col);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < 20; j++){
            scanf("%c", &graph[i][j]);
            if(graph[i][j] == 'A'){
                a_x = i;
                a_y = j;
            }
            if(graph[i][j] == 'B'){
                b_x = i;
                b_y = j;
            }
            if(graph[i][j] == ' '){
                j--;
            }
            if(graph[i][j] == '\n'){
                j = 0;
                break;
            }
        }
    }
    scanf("%d\n", &score_a);
    scanf("%d\n", &score_b);
    scanf("%c", &me);

    if(me == 'A'){
        ctr_x = a_x;
        ctr_y = a_y;
        choose(a_x, a_y);
        //printf("%d", num);
        if(num == 0){
            printf("RIGHT\n");
        }
        if(num == 1){
              printf("DOWN\n");
        }
        if(num == 2){
            printf("LEFT\n");
        }
        if(num == 3){
            printf("UP\n");
        }
    }
    else{
        ctr_x = b_x;
        ctr_y = b_y;
        choose(b_x, b_y);
        if(num == 0){
            printf("RIGHT\n");
        }
        if(num == 1){
            printf("DOWN\n");
        }
        if(num == 2){
            printf("LEFT\n");
        }
        if(num == 3){
            printf("UP\n");
        }
    }

}
