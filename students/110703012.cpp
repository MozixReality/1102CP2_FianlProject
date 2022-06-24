#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#define SIZE 21
#define depth 16
struct Queue{
    int x;
    int y;
};
struct Queue queue[ SIZE*SIZE ] = {0};
char Maze[ SIZE ][ SIZE ] = {};
float map[ SIZE ][ SIZE ] = {0};
int Round, M, N, i = 0, j = 0, sx, sy, range_x, range_y, k;
char player, opponent = 'B';
int playermode = 0, Ax, Ay, Bx, By, ox, oy; 
int front = 0, rear = 0, maxi = 0;
float score = 0, max = 0;
int my_score = 0, op_score = 0;
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0};
const char *msg[] = {"RIGHT", "DOWN", "LEFT", "UP"};
float DFP[4] = {0};
bool Valid( int x3, int y3 ) {
    if( 0 <= x3 && x3 < N && 0 <= y3 && y3 < M ) {
      if( Maze[x3][y3] != player && Maze[x3][y3] != 'x') {
          return true;
      } else {
          return false;
      }
  } 
  return false;
}
void Enqueue( int x1, int y1 ) {
    queue[ rear ].x = x1;
    queue[ rear ].y = y1;
    rear++;
}
void Dequeue(){
    front++;
}
bool Empty(){
    if( front == rear )
        return true;
    return false;
}
struct Queue GetFront(){
    return queue[ front ];
}
void Reset(){
     memset( map, 0, sizeof( map[0][0] ) * SIZE * SIZE );
     front = 0;
     rear = 0;
     score = 0;
}
void Decision( int a, int b ){
    if( Maze[a][b] == '.' ) {
        score += 0;
    }
    if( Maze[a][b] == 'm' ) {
        score += 1/map[a][b];
    }
    if( Maze[a][b] == 'n' ) {
        score += -1/map[a][b];
    }
    if( Maze[a][b] == 's' ) {
        score += score/map[a][b]; 
    }
    if( Maze[a][b] == 't' ) {
        score -= score/map[a][b];
    } 
    if( Maze[a][b] == 'b' ){
       map[ a ][ b ] += 3;
       score += 0;
    }
}
void Dir_decide(){
    for( int index = 0; index < 4; index++) {
        int px = sx + dx[index];
        int py = sy + dy[index];
        if( Valid( px, py ) && Maze[ px ][ py ] != opponent ) {
                if( max == 0 ) {
                    max = DFP[index];
                    maxi = index;
                } else  {
                    if( DFP[index] >= max ) {
                    max = DFP[index];
                    maxi = index;
                    }
                }
            }
         }
    }
void BFS( int x, int y ) {
    while( !Empty() ) {
        struct Queue cur_q = GetFront();
        Dequeue();
        for ( k = 0; k < 4; k++) {
            int cur_x = cur_q.x + dx[k]; 
            int cur_y = cur_q.y + dy[k];
               if( Valid( cur_x, cur_y ) && Maze[cur_x][cur_y] != opponent && map[cur_x][cur_y] == 0 ) {
                   Enqueue( cur_x, cur_y );
                    map[cur_x][cur_y] = map[cur_q.x][cur_q.y] + 1;
                    if( map[cur_x][cur_y] == depth )
                        return;
                        Decision( cur_x, cur_y );
                }
         }
     }
}
int main( void )
{
    scanf("%d", &Round); 
    scanf("%d %d\n", &M, &N);
        for ( i = 0;i < M; i++) {
             for ( j = 0; j < N; j++) {
                if( j == 0 ) {
                    scanf("\n%c", &Maze[i][j]);
                } else {
                    scanf(" %c", &Maze[i][j]);
                }
                if( Maze[ i ][ j ] == 'A' ) {
                    Ax = i, Ay = j;
                    playermode = 1;
                 }
                if( Maze[ i ][ j ] == 'B' ){
                    Bx = i, By = j;
                }
            }
        }
    scanf("%d", &my_score);
    scanf("%d\n", &op_score);
    scanf("%c", &player);
    if ( player == 'A' ){
        sx = Ax, sy = Ay;
    } else {
        sx = Bx, sy = By;
        opponent = 'A';
      int tmp = my_score;
       my_score = op_score;
       op_score = tmp;
    }
        for ( int v = 0; v < 4; v++) {
            Reset();
            int vx = sx + dx[v]; 
            int vy = sy + dy[v];
               if( Valid( vx, vy ) && Maze[vx][vy] != opponent && Maze[vx][vy] != 't' && map[vx][vy] == 0 ) {
                   Enqueue( vx, vy );
                   map[vx][vy] = 1;
                   if( map[vx][vy] == depth )
                       break;
                   Decision( vx, vy );
                 BFS( sx, sy ); 
             }
             DFP[v]  = score;
        }
    Dir_decide(); // Direction decision
    printf("%s\n", msg[maxi]); 
}
