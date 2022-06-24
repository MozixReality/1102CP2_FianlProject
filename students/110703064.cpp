#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
int Round; 
int M; int N;
char map[20][20];
int steps[2002] = {};
int count = 0;
int visited[20][20] = {};
bool valid(int x, int y){
	if(x >= 0 && x < 8 && y >= 0 && y < 8 && map[x][y] != 'x' && map[x][y] != 'A' && map[x][y] != 'B')
		return true;
	else return false;
}
int findmax(int up , int down , int right , int left  , int times){
	int max = -100000;
	if(up > max){
		max = up;
		steps[times] = 1;
	}
	if(down > max){
		max = down;
		steps[times] = 2;
	}
	if(right > max){
		max = right;
		steps[times] = 3;
	}
	if(left > max){
		max = left;
		steps[times] = 4;
	}
	return max;
}
int nextstep(int sx, int sy , int score , int times){
	if(times == (17) || times > 1000 - Round)
		return score;
	else{
		if(map[sx][sy] == 's')
			score*=2;
		else if(map[sx][sy] == 'm')
			score+=1;
		else if(map[sx][sy] == 'n')
			score-=1;
		else if(map[sx][sy] == 't')
			score/=2;
		int up = -10000000; int down = -10000000;  int right = -10000000; int left = -10000000;
		if(valid(sx-1,sy) && visited[sx-1][sy] == 0){
			visited[sx-1][sy] = 1;
			up = nextstep(sx - 1 , sy , score , times+1);
			visited[sx-1][sy] = 0;
		}
		if(valid(sx+1,sy) && visited[sx+1][sy] == 0){
			visited[sx+1][sy] = 1;
			down = nextstep(sx + 1 , sy  , score , times+1);
			visited[sx+1][sy] = 0;
		}
		if(valid(sx,sy+1) && visited[sx][sy+1] == 0){
			visited[sx][sy+1] = 1;
			right = nextstep(sx , sy + 1 , score , times+1);
			visited[sx][sy+1] = 0;
		}
		if(valid(sx,sy-1) && visited[sx][sy-1] == 0){
			visited[sx][sy+1] = 1;
			left = nextstep(sx , sy - 1 , score ,times+1);
			visited[sx][sy+1] = 0;
		}
		return findmax(up , down , right , left , times);
	}
}

int main(){
	int A, B, myscore, emyscore;
	char me;
	scanf("%d",&Round);
	scanf("%d %d ",&M,&N);
	for(int i = 0 ; i < M ; i++){
		for(int j = 0 ; j < N ; j++)
			scanf("%c ",&map[i][j]);
	}
	scanf("%d",&A);
	scanf("%d ",&B);
	scanf("%c",&me);
	int sx; int sy;
	for(int i = 0 ; i < M ; i++){
		for(int j = 0 ; j < N ; j++)
			if(map[i][j] == me){
				sx = i;
				sy = j;
			}
	}
	if(me == 'A'){
		myscore = A;
		emyscore = B;
	}
	else {
		myscore = B;
		emyscore = A;
	}
	int i = 0; int result = 0;
	if(emyscore > myscore){
		if(valid(sx-1,sy) && map[sx-1][sy] == 's')
			printf("UP\n");
		else if(valid(sx+1,sy) && map[sx+1][sy] == 's')
			printf("DOWN\n");
		else if(valid(sx,sy+1) && map[sx][sy+1] == 's')
			printf("RIGHT\n");
		else if(valid(sx,sy-1) && map[sx][sy-1] == 's')
			printf("LEFT\n");
		else{
			nextstep(sx , sy , myscore , count);
			if(steps[0] == 1)
				printf("UP\n");
			if(steps[0] == 2)
				printf("DOWN\n");
			if(steps[0] == 3)
				printf("RIGHT\n");
			if(steps[0] == 4)
				printf("LEFT\n");
		}
	}else{
		nextstep(sx , sy , myscore , count);
		if(steps[0] == 1)
			printf("UP\n");
		if(steps[0] == 2)
			printf("DOWN\n");
		if(steps[0] == 3)
			printf("RIGHT\n");
		if(steps[0] == 4)
			printf("LEFT\n");
	}

}

