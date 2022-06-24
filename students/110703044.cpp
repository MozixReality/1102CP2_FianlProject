#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<climits>
typedef struct position{ // record position
	int x;
	int y;
}Position;

enum Action{UP, DOWN, LEFT, RIGHT};
char *msg[] = {"UP", "DOWN", "LEFT", "RIGHT"};
char *msg1[] = {"RIGHT", "LEFT", "DOWN", "UP"};

int BestPath;
int TmpPath[26];
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};
int d1x[] = {1,-1,0,0};
int d1y[] = {0,0,-1,1};
int rounds, n_row, n_col, score_A, score_B, roleScore;

char role;
char** table;

float max = INT_MIN;
Position positionA, positionB, rolePosition;
bool visited[21][21];

void getData(){

	scanf("%d\n", &rounds);
	scanf("%d %d\n", &n_row, &n_col);

	table = (char**) malloc(n_row * sizeof(char*));

	for(int i = 0 ; i < n_row ; i++)
		table[i] = (char*) malloc(n_col * sizeof(char));


	for(int j = n_row-1 ; j >= 0 ; --j){

		for(int i = 0 ; i < n_row ; ++i){

			scanf("%c%*c", &table[i][j]);

			if(table[i][j] == 'A'){
				positionA.x = i;
				positionA.y = j;
			}
			if(table[i][j] == 'B'){
				positionB.x = i;
				positionB.y = j;
			}

		}
	}

	scanf("%d\n", &score_A);
	scanf("%d\n", &score_B);
	scanf("%c", &role);

	if(role == 'A'){
		rolePosition.x = positionA.x;
		rolePosition.y = positionA.y;
		roleScore = score_A;
	}
	else{
		rolePosition.x = positionB.x;
		rolePosition.y = positionB.y;
		roleScore = score_B;
	}

}

bool valid(int x, int y){

	if((0 <= x && x < n_col) && (0 <= y && y < n_row)){

		if(table[x][y] == 'x' || (table[x][y] == 'A') || (table[x][y] == 'B'))

			return false;

		else 
			return true;
	}
	return false;
}

float judge(int action, int score, int sx, int sy){ // sx, sy from which cube 

	if(action == UP){
		if(table[sx][sy+1] == 'b')
			score = score;
		if(table[sx][sy+1] == 'm')
			score += 15;
		if(table[sx][sy+1] == 'n')
			score -= 30;
		if(table[sx][sy+1] == 's')
			score *= 2;
		if(table[sx][sy+1] == 't')
			score /= 2;
	}

	if(action == DOWN){
		if(table[sx][sy-1] == 'b' )
			score = score;
		if(table[sx][sy-1] == 'm')
			score += 15;
		if(table[sx][sy-1] == 'n')
			score -= 30;
		if(table[sx][sy-1] == 's')
			score *= 2;
		if(table[sx][sy-1] == 't')
			score /= 2;
	}

	if(action == LEFT){
		if(table[sx-1][sy] == 'b')
			score = score;
		if(table[sx-1][sy] == 'm')
			score += 15;
		if(table[sx-1][sy] == 'n')
			score -= 30;
		if(table[sx-1][sy] == 's')
			score *= 2;
		if(table[sx-1][sy] == 't')
			score /= 2;
	}

	if(action == RIGHT){
		if(table[sx+1][sy] == 'b')
			score = score;
		if(table[sx+1][sy] == 'm')
			score += 15;
		if(table[sx+1][sy] == 'n')
			score -= 30;
		if(table[sx+1][sy] == 's')
			score *= 2;
		if(table[sx+1][sy] == 't')
			score /= 2;
	}
	return score;
}

void reset(){
	memset(visited, 0, sizeof(visited));
	visited[rolePosition.x][rolePosition.y] = 1;
	for(int i=0; i<20; ++i)
		TmpPath[i] = -1;
}

void clean(int depth){
	for(int i=depth; i<25; ++i)
		TmpPath[i] = -1;
}

void DFS(int sx, int sy, int steps, float score){

	if(steps == 25){
		if(score/(float)steps > max){
			max = score;
			BestPath = TmpPath[0];
		}
		return;
	}
	else if(steps < 25){
		if(steps != 0){
			if(score/(float)steps > max){
				max = score;
				BestPath = TmpPath[0];
			}
		}
	}
	if(role == 'B'){
		for(int i=0;i<4;++i){

			int X = sx+dx[i];
			int Y = sy+dy[i];

			if(valid(X, Y) && !visited[X][Y]){

				float value = judge(i, score, sx, sy);	
				visited[X][Y] = 1;
				TmpPath[steps] = i;
				DFS(X, Y, steps+1, value);
				clean(steps);
				visited[X][Y] = 0;

			}
		}
	}
	else if(role == 'A'){
		for(int i=0;i<4;++i){

			int X = sx+d1x[i];
			int Y = sy+d1y[i];

			if(valid(X, Y) && !visited[X][Y]){

				float value = judge(3-i, score, sx, sy);
				visited[X][Y] = 1;
				TmpPath[steps] = 3-i;
				DFS(X, Y, steps+1, value);
				clean(steps);
				visited[X][Y] = 0;

			}
		}	
	}

}
int main(void){
	getData();
	reset();
	DFS(rolePosition.x, rolePosition.y, 0, roleScore);
	/*if(BestPath == 0)
	  puts(msg[1]);
	  else if(BestPath == 1)
	  puts(msg[0]);
	  else if(BestPath == 2)
	  puts(msg[3]);
	  else
	  puts(msg[2]);*/
	puts(msg[BestPath]);
}
