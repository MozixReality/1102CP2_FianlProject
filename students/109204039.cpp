#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a,b) (((a)>(b))?(a):(b))



int valid(int x, int y, char *Graph[], int M, int N){
    if(x >= 0 && x < M && y >=0 && y < N){
        if(Graph[x][y] != 'x' && Graph[x][y] != 'A' && Graph[x][y] != 'B'){
            return 1;
        }
    }
    return 0;
}

int random_move(int x, int y, char *Graph[], int M, int N, int num){
    for(int i=0;i<4 ;i++){
        switch(num%4){
            case 0: 
                if(valid(x-1, y, Graph, M, N))
                    return 0;
                else break;
            case 1:
                if(valid(x+1, y, Graph, M, N)) 
                    return 1;
                else break;
            case 2: 
                if(valid(x, y-1, Graph, M, N))
                    return 2;
                else break;
            case 3: 
                if(valid(x, y+1, Graph, M, N))
                    return 3;
                else break;
            default: return 3;
        }
        num++;
    }
    return 3;
}

int next_dir(int x, int y, char *Graph[], int M, int N, int score, int *visit[], int depth, int check, int num){
    int dx[] = { -1, 1, 0, 0};
    int dy[] = { 0, 0, -1, 1};
    int direction_score[4];
    for(int a=0; a<4; ++a){
        direction_score[a] = score;
    }

    visit[x][y] = 1;

    for(int i=0; i<4; ++i){
        if(valid(x + dx[i], y + dy[i], Graph, M, N) && visit[x + dx[i]][y + dy[i]] == 0){
            if(depth == 0){
                switch(Graph[x + dx[i]][y + dy[i]]){
                    case '.':
                        direction_score[i] = score;
                        break;
                    case 'b':
                        direction_score[i] = score-3;
                        break;
                    case 'm':
                        direction_score[i] = score+100;
                        break;
                    case 'n':
                        direction_score[i] = score-1;
                        break;
                    case 's':
                        direction_score[i] = score*100;
                        break;
                    case 't':
                        direction_score[i] = score/100;
                        break;
                }
            }
            else{
                switch(Graph[x + dx[i]][y + dy[i]]){
                    case '.':
                        direction_score[i] = next_dir(x + dx[i], y + dy[i], Graph, M, N, score, visit, depth-1, 0, rand()*2);
                        break;
                    case 'b':
                        direction_score[i] = next_dir(x + dx[i], y + dy[i], Graph, M, N, score-3, visit, depth-1, 0, rand()*3);
                        break;
                    case 'm':
                        direction_score[i] = score+100;
                        break;
                    case 'n':
                        direction_score[i] = next_dir(x + dx[i], y + dy[i], Graph, M, N, score-1, visit, depth-1, 0, rand()*4);
                        break;
                    case 's':
                        direction_score[i] = score*100;
                        break;
                    case 't':
                        direction_score[i] = score/100;
                        break;
                }
            }
        }
        else{
            direction_score[i] = -10000;
        }
    }

    int max_score = MAX(MAX(direction_score[0], direction_score[1]), MAX(direction_score[2], direction_score[3]));
    if(max_score == -10000){
        return score;
    }
    else if(check == 0){
        return max_score;
    }
    else{
        int if_equal_MAXscore[4] = {0};
        for(int k=0; k<4; ++k){
            if(direction_score[k] == max_score){
                if_equal_MAXscore[k] = 1;
            }
            else{
                if_equal_MAXscore[k] = 0;
            }
        }

        int foo=0;
        for(int m=0; m<4; ++m){
            foo += if_equal_MAXscore[m];
        }

        if(foo == 1){
            for(int p=0; p<4; ++p){
                if(direction_score[p] == max_score){
                    return p;
                }
            }
        }
        else{
            for(int i=0;i<4 ;i++){
                switch(num%4){
                    case 0: 
                        if(valid(x-1, y, Graph, M, N) && if_equal_MAXscore[num%4] == 1)
                            return 0;
                        else break;
                    case 1:
                        if(valid(x+1, y, Graph, M, N) && if_equal_MAXscore[num%4] == 1) 
                            return 1;
                        else break;
                    case 2: 
                        if(valid(x, y-1, Graph, M, N) && if_equal_MAXscore[num%4] == 1)
                            return 2;
                        else break;
                    case 3: 
                        if(valid(x, y+1, Graph, M, N) && if_equal_MAXscore[num%4] == 1)
                            return 3;
                        else break;
                    default: return 3;
                }
                num++;
            }
        }
    }
}



int main(void){

    int Round, A, B, M, N;
    char me;
    scanf("%d", &Round);
    scanf("%d %d ", &M, &N);
    char **GRAPH = (char **)malloc(M * sizeof(char *));
    for(int i=0; i<M; ++i){
        GRAPH[i] = (char *)malloc(N * sizeof(char));
    }
    char trash;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            scanf("%c%c", &GRAPH[i][j], &trash);
        }
    }
    scanf("%d", &A);
    scanf("%d ", &B);
    scanf("%c", &me);


    // input test-------------------
    // for(int i=0;i<M;i++){
    //     printf("\n");
    //     for(int j=0;j<N;j++){
    //         printf("%c ", GRAPH[i][j]);
    //     }
    // }
    // printf("\n");
    // printf("Round = %d\n", Round);
    // printf("M = %d\n", M);
    // printf("N = %d\n", N);
    // printf("A = %d\n", A);
    // printf("B = %d\n", B);
    // printf("me = %c\n", me);


    int ax, ay, bx, by;
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            if(GRAPH[i][j] == 'A'){
                ax = i;
                ay = j;
            }
            else if(GRAPH[i][j] == 'B'){
                bx = i;
                by = j;
            }
        }
    }

    // input test-------------------
    // printf("ax = %d, ay = %d, bx = %d, by = %d\n", ax, ay, bx, by);


    
    int **visit = (int **)malloc(M * sizeof(int *));
    for(int i=0; i<M; ++i){
        visit[i] = (int *)malloc(N * sizeof(int));
    }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            visit[i][j] = 0;


    char final_decision;
    srand(time(NULL));
    if((Round%100) >40 && (Round%100) < 60){
        if(me == 'A'){
            final_decision = random_move(ax, ay, GRAPH, M, N, rand());
        }
        else{
            final_decision = random_move(bx, by, GRAPH, M, N, rand());
        }
    }
    else{
        if(me == 'A'){
            final_decision = next_dir(ax, ay, GRAPH, M, N, A, visit, 4, 1, rand());
        }
        else{
            final_decision = next_dir(bx, by, GRAPH, M, N, B, visit, 4, 1, rand());
        }
    }
    


    switch(final_decision){
        case 0: 
            printf("UP ");
            break;
        case 1:
            printf("DOWN ");
            break;
        case 2: 
            printf("LEFT ");
            break;
        case 3: 
            printf("RIGHT ");
            break;
    }


    for(int i=0; i<M; ++i){
        free(GRAPH[i]);
    }
    free(GRAPH);


    for(int i=0; i<M; ++i){
        free(visit[i]);
    }
    free(visit);

    return 0;
}