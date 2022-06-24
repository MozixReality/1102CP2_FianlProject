#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define MAX_LENGHT 7

typedef struct{
        short x;
        short y;
        short far;
        short point;
        short dir;
}node;
typedef struct{
        short point;
        short dir;
}max_typ;

char **arr;
short row,col;

char BFS(short start_x, short start_y, short ene_x, short ene_y,short round_bfs, short your_point, short ene_point);

int main(){
        short round,point_A,point_B;
        short ax,ay,bx,by;

        scanf("%hd\n",&round);
        scanf("%hd %hd\n",&row,&col);

        arr = (char**)malloc(row*sizeof(char*));
        for(size_t i=0;i<row;++i){
                arr[i] = (char*) malloc(col * sizeof(char));
        }

        int i,j;
        for( i=0;i<row;++i){
                for( j=0;j<col;++j){
                        scanf("%c%*c",&arr[i][j]);
                        if(arr[i][j] == 'A'){
                                ax = i; ay = j;
                        }
                        if(arr[i][j] == 'B'){
                                bx = i; by = j;
                        }
                }
        }
        scanf("%hd\n",&point_A);
        scanf("%hd\n",&point_B);

        char who;
        short ans;
        scanf("%c",&who);
        if(who == 'A')
                ans = BFS(ax,ay,bx,by,round,point_A,point_B);
        else
                ans = BFS(bx,by,ax,ay,round,point_B,point_A);

        if(ans == 0 ) printf("RIGHT\n");
        if(ans == 1 ) printf("LEFT\n");
        if(ans == 2 ) printf("UP\n");
        if(ans == 3 ) printf("DOWN\n");
        return 0;
}

char BFS(short start_x, short start_y, short ene_x, short ene_y,short round_bfs, short your_point, short ene_point){

        short dx[] = {0,0,-1,1};
        short dy[] = {1,-1,0,0};
        short cur_x,cur_y,cur_far,cur_point,cur_dir,tx,ty;

        max_typ max; max.point = 0; max.dir = 0;

        bool book[row][col] = {0}; book[start_x][start_x] = 1;

        node queue[1000];
        queue[0].x = start_x; queue[0].y = start_y; queue[0].far = 0 ; queue[0].dir = -1; queue[0].point = your_point;


        int i,j,k;
        for(i=0,j=1;i<j;++i){
                cur_x = queue[i].x; cur_y = queue[i].y; cur_far = queue[i].far; cur_point = queue[i].point; cur_dir = queue[i].dir;

                for(k=0;k<4;++k){

                        tx = cur_x + dx[k];
                        ty = cur_y + dy[k];

                        if(tx < 0 || tx >= row || ty < 0 || ty >= col || arr[tx][ty] == 'x'|| cur_far >= MAX_LENGHT || cur_far > 1000 || tx == ene_x && ty == ene_y)
                                continue;

                        if(!book[tx][ty] && arr[tx][ty] != 'x' ){
                                book[tx][ty] = 1;
                                queue[j].x = tx; queue[j].y = ty; queue[j].far = cur_far + 1;

                                if( i!=0 )queue[j].dir = cur_dir;
                                else queue[j].dir = k;

                                if(arr[tx][ty] == 'b') {queue[j].far +=3; queue[j].point = cur_point;}
                                if(arr[tx][ty] == 'm') queue[j].point = cur_point+1;
                                if(arr[tx][ty] == 'n') queue[j].point = cur_point-1;
                                if(arr[tx][ty] == 's') queue[j].point = cur_point*2;
                                if(arr[tx][ty] == 't') queue[j].point = cur_point/2;
                                if(arr[tx][ty] == '.') queue[j].point = cur_point;

                                if(queue[j].point > max.point) {
                                        max.point = queue[j].point;
                                        max.dir = queue[j].dir;
                                        if(max.point>0 && max.point >queue[j].point)
                                                return max.dir;
                                }
                                ++j;
                        }
                }
        }
        return max.dir;
}