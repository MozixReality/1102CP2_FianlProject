#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

using namespace std;

int M, N;
int map[20][20];
double score[4]; /* the score for judging 4 directions */
int max_num; /* the direction that has largest score */

int max(int a, int b){
    return (a>b)?a:b;
}

void recrusive(int depth, int level, int source, int ax, int ay, int score0){
    int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0}; /* Right Down Left Up */
    if (level > depth){return;}
    for (int i = 0; i < 4; ++i){
        if( level == 0){
            source = i;
        }
        /* try 4 directions */
        if ( dx[i]+ax >= 0 && dx[i]+ax < M && dy[i]+ay >= 0 && dy[i]+ay < N && map[dx[i]+ax][dy[i]+ay] != -4 && map[dx[i]+ax][dy[i]+ay] != -6) {
            /* if the current location near 's', then go to 's' */
            if (level == 0 && map[dx[i]+ax][dy[i]+ay] == 2){
                score[source] = INT_MAX;
                return;
            }
            if( level == depth ){
                score[source] = max(score[source], score0);
            }
        
            if ( abs(map[dx[i]+ax][dy[i]+ay]) == -2 ){
                recrusive(depth, level+1, source, dx[i]+ax, dy[i]+ay, score0/2 );
            }else if ( abs(map[dx[i]+ax][dy[i]+ay]) == 2 ){
                recrusive(depth, level+1, source, dx[i]+ax, dy[i]+ay, score0*2 );
            }else{
                recrusive(depth, level+1, source, dx[i]+ax, dy[i]+ay, map[dx[i]+ax][dy[i]+ay]+score0 );
            }
            
        }
    }
}

int main()
{
    /* set map */
    int A, B, ax, ay, bx, by, score0, Round;
    char me, input;
    cin >> Round >> M >> N;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin >> input;
            if(input == '.'){
                map[i][j] = 0;  /* path */
            }else if(input == 'x'){
                map[i][j] = -4;  /* wall or B */
            }else if(input == 'm'){
                map[i][j] = 1;  /* good mushroom */
            }else if(input == 'n'){
                map[i][j] = -1;  /* bad mushroom */
            }else if(input == 's'){
                map[i][j] = 2;  /* good star */
            }else if(input == 't'){
                map[i][j] = -2;  /* bad star */
            }else if(input == 'b'){
                map[i][j] = -3;  /* bump */
            }else if(input == 'A'){
                map[i][j] = -5;  /* A */
                ax = i;
                ay = j;
            }else if(input == 'B'){
                map[i][j] = -6;  /* B */
                bx = i;
                by = j;
            }
        }
    }
    cin >> A >> B >> me;
    
    /* set A or B */
    if( me == 'A'){
        score0 = A;
    }else if( me == 'B'){
        score0 = B;
        map[ax][ay] = -6;
        map[bx][by] = -5;
        ax = bx;
        ay = by;
    }

    /* map start */
    fill_n(&score[0], 4, INT_MIN);
    int depth = 11;
    recrusive(depth, 0, 0, ax, ay, score0);
    
    /* decide direction */
    int maxx = INT_MIN;
    for(int z = 0; z<4; ++z){
        if ( score[z] != INT_MIN ){
            score[z] += rand()/double(RAND_MAX);
        }
        if ( score[z] > maxx){
            maxx = score[z];
            max_num = z;
        }
    }
    
    /* print direction */
    if (max_num == 0){
        cout << "RIGHT" << endl;
    }else if(max_num == 1){
        cout << "DOWN" << endl;
    }else if(max_num == 2){
        cout << "LEFT" << endl;
    }else if(max_num == 3){
        cout << "UP" << endl;
    }else{
        cout << "UP" << endl;
    }

}






