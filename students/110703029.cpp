#include <stdio.h>
#include <string.h>



int a(int map;int size;int startx ;int starty;int score){
            if(score>=1){
                    if(map[startx+1][starty]=='S'){
                        return 0;
                    }
                    else if(map[startx-1][starty]=='S'){
                        return 1;
                    }
                    else  if(map[startx][starty+1]=='S'){
                        return 2;
                    }
                    elseif(map[startx][starty-1]=='S')
                        return 3;
                    }
       
            
            if(map[startx+1][starty]!='T'||map[startx+1][starty]!='X'&&startx+1<size&&startx+1>0&&starty<size&&starty>0){
                return 0;
                }else if(map[startx-1][starty]!='T'||map[startx-1][starty]!='X'&&startx-1<size&&startx-1>0&&starty<size&&starty>0){

                    return 1;
                }
                else if(map[startx][starty+1]!='T'||map[startx][starty+1]!='X'&&startx<size&&startx>0&&starty+1<size&&starty+1>0){
        

                    return 2;
                }
                else if(map[startx][starty-1]!='T'||map[startx][starty-1]!='X'&&startx<size&&startx>0&&starty-1<size&&starty-1>0){
        

                    return 3;
                }
            }














int main(){
 int T;
 scanf("%d",&T);

//Map scaning//
    int M;
    int N;

    scanf("%d",&M);
    scanf("%d",&N);

    int maze[M][N];
    int xb;
    int xa;
    int yb;
    int ya;

    for(int i ;i<M;i++){
        for(int j;j<N;j++){
            

        scanf("%d",&maze[i][j]);
        if(maze[i][j]=='A'){
            xa=i;
            ya=j;
        }
        if(maze[i][j]='B'){
            xb=i;
            yb=j;
        }
    }
    }

    int P;
    int Q;
    scanf("%d",&P);
    scanf("%d",&Q);

    int player;
    scanf("%d",&player);
    int ans=0;
    if(player=='A'){

        int ans= a(maze,M,xa,ya,P);
    }else{
    ans= a(maze,M,xb,yb,Q);

    }

    switch(ans){
        case 0;
            printf("UP");
            break;
        case 1;
            printf("DOWN");
            break;
        case 2;
            printf("LEFT");
            break;
        case 3;
            printf("RIGHT");
            break;



    }

   


    return 0;

}