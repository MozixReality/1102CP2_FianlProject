#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include<stdbool.h>
#define MAX(a, b) (((a)>(b)) ? (a) : (b))
#define MIN(a, b) (((a)>(b)) ? (b) : (a))
int Round, n, m, score_A, score_B, gapX, gapY;
clock_t start_time;
clock_t stop_time;
int dx[] = {  0,  1,  0, -1 };
int dy[] = {  1,  0, -1,  0 }; 
char **map = NULL;
char player;
bool **visited = NULL;
struct coordinate{
	int x;
	int y;
	int score;
};
struct coordinate A, B;
void getInput(){

	scanf("%d\n", &Round);
	scanf("%d %d\n", &n, &m);

	map = (char**)malloc(sizeof(char*) * n);
	visited = (bool**)malloc(sizeof(bool*) *n);

	for(int i = 0 ; i < m ; i++){
		map[i] = (char*)malloc(sizeof(char) *m);
		visited[i] = (bool*)malloc(sizeof(bool) *m);
	}

	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < m ; j++){
			scanf("%c%*c", &map[i][j]);
			visited[i][j] = false;
			switch(map[i][j]){
				case'A':
					A.x = i;
					A.y = j;
					break;
				case'B':
					B.x = i;
					B.y = j;
					break;
			}
		}
	}
	scanf("%d\n", &A.score);
	scanf("%d\n", &B.score);
	scanf("%c\n", &player);

}
bool valid(int x, int y){

	if(x < 0 || x >= n)
		return false;
	else if(y < 0 || y >= m)
		return false;
	else if(map[x][y] == 'A' || map[x][y] == 'B')
		return false;
	else if(map[x][y] == 'x' )
		return false;
	else
		return true;
}
int calculateScore(int x, int y, int score){

	switch(map[x][y]){
		case 'm':
			return score + 1;
		case 'n':
			return score - 1;
		case 's':
			return score * 2;
		case 't': 
			return score / 2;
		case'.':
		case'b':
		default:
			return score;
	}

}
struct coordinate makeDecision(struct coordinate q, int depth, int alpha, int beta, bool maximizingPlayer){


	int x = q.x;
	int y = q.y;
	int currentScore = q.score;
	if( depth == 5 )
		return q;

	if(maximizingPlayer){

		struct coordinate bestMaxVal;
		bestMaxVal.score = INT_MIN;
		for(int i = 0 ; i < 4 ; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			struct coordinate tmpPos;
			if(valid(nx,ny) && !visited[nx][ny]){
				visited[x][y] = true;
				tmpPos.x = nx;
				tmpPos.y = ny;
				tmpPos.score = calculateScore(nx, ny, currentScore);
				struct coordinate tmpVal = makeDecision(tmpPos, depth+1, alpha, beta, false);
				if(tmpVal.score > bestMaxVal.score ){
					bestMaxVal.x = nx;
					bestMaxVal.y = ny;
					bestMaxVal.score = tmpVal.score;
				}
				alpha = MAX(alpha, tmpVal.score);
				if( beta <= alpha)
					break;
			}
		}
		return bestMaxVal;
	}

	else{
		struct coordinate bestMinVal;
		bestMinVal.score = INT_MAX;
		for(int i = 0 ; i < 4 ; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			struct coordinate tmpPos;
			if(valid(nx, ny) && !visited[nx][ny]){
				visited[x][y] = true;
				tmpPos.x = nx;
				tmpPos.y = ny;
				tmpPos.score = calculateScore(nx, ny, currentScore);
				struct coordinate tmpVal = makeDecision(tmpPos, depth+1, alpha, beta, true);
				if(tmpVal.score < bestMinVal.score){
					bestMinVal.x = nx;
					bestMinVal.y = ny;
					bestMinVal.score = tmpVal.score;
				}
				beta = MIN(beta, tmpVal.score);
				if( beta <= alpha)
					break;
			}
			
		}
		return bestMinVal;
	}
}
int main(void){

	getInput();
	struct coordinate bestVal;
	
	if(player == 'A'){
		bestVal = makeDecision(A, 0, INT_MIN, INT_MAX, true);
		gapX = bestVal.x - A.x;
		gapY = bestVal.y - A.y;
	}
	else{
		bestVal = makeDecision(B, 0, INT_MIN, INT_MAX, true);
		gapX = bestVal.x - B.x;
		gapY = bestVal.y - B.y;
	}
	if(gapX == 0 && gapY == 1) 
		printf("RIGHT\n");	
	else if(gapX == 1 && gapY == 0)
		printf("DOWN\n");
	else if(gapX == 0 && gapY == -1)
		printf("LEFT\n");
	else if(gapX == -1 && gapY == 0 )
		printf("UP\n");
	else{
		for(int i = 0 ; i < 4; i++){
			if( player == 'A' ){
				if( valid(A.x+dx[i], A.y+dy[i]) ){
					if( i == 0 ){
						printf("RIGHT\n");
						break;
					}
					else if( i == 1){
						printf("DOWN\n");
						break;
					}
					else if( i == 2 ){
						printf("LEFT\n");
						break;
					}
					else{
						printf("UP");
						break;
					}
				}
			}
			else if( player == 'B' ){
				if( valid(B.x+dx[i],B.y+dy[i]) ){
					if( i == 0 ){
						printf("RIGHT\n");
						break;
					}
					else if( i == 1){
						printf("DOWN\n");
						break;
					}
					else if( i == 2 ){
						printf("LEFT\n");
						break;
					}
					else{
						printf("UP\n");
						break;
					}
				}
			}
		}
	}
}
