#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

using namespace std;
typedef struct point Point;
struct point{
	int x;
	int y;
	int D;
	int S;
	int lev;
};

char Map[20][20];
int ROUND;
int row, col;

bool valid(int x, int y){
	if(x >= 0 && y >= 0 && x < row && y < col && Map[x][y] != 'x' && Map[x][y] != 'A' && Map[x][y] != 'B')
		return true;
	else
		return false;
}

void hunt(int Sx, int Sy, int fir_score){
	int i, j = 1, k;
	int **visited = (int **)calloc(row, sizeof(int *));
	for(i = 0; i < row; ++i){
		visited[i] = (int *)calloc(col, sizeof(int));
	}
	visited[Sx][Sy] = 1;

	int Dx[4] = {1, -1, 0, 0};
	int Dy[4] = {0, 0, -1, 1};
	int max = INT_MIN,
		cur_x,
		cur_y,
		cur_D,
		cur_score,
		cur_lev,
		tmp_x,
		tmp_y;
	int turn;

	Point P[1000];
	P[0].x = Sx;
	P[0].y = Sy;
	P[0].S = fir_score;
	P[0].D = 0;
	P[0].lev = 0;

	for(i = 0; i < j; ++i){
		cur_x = P[i].x;
		cur_y = P[i].y;
		cur_score = P[i].S;
		cur_D = P[i].D;
		cur_lev = P[i].lev;

		//four direction
		for(k = 0; k < 4; ++k){
			tmp_x = cur_x + Dx[k];
			tmp_y = cur_y + Dy[k];

			if(valid(tmp_x, tmp_y) && visited[tmp_x][tmp_y] != 1 && cur_lev < 20){
				visited[tmp_x][tmp_y] = 1;
				P[j].x = tmp_x;
				P[j].y = tmp_y;
				P[j].lev = cur_lev + 1;

				if(!i)
					P[j].D = k;
				else
					P[j].D = cur_D;

				// update cur_score
				if(Map[tmp_x][tmp_y] == 'm')
					P[j].S = cur_score + 1;
				else if(Map[tmp_x][tmp_y] == 'm')
					P[j].S = cur_score - 1;
				else if(Map[tmp_x][tmp_y] == 's')
					P[j].S = cur_score * 2;
				else if(Map[tmp_x][tmp_y] == 't')
					P[j].S = cur_score / 2;
				else if(Map[tmp_x][tmp_y] == '.')
					P[j].S = cur_score;
				else if(Map[tmp_x][tmp_y] == 'b'){
					P[j].S = cur_score;
					P[j].lev = cur_lev + 4;
				}

				if(P[j].S > max){
					max = P[j].S;		//update max
					turn = P[j].D;
				}
				++j;

			}
		}
		//four direction end
	}

	free(visited);
	for(i = 0; i < row; ++i)
		free(visited[i]);

	//printf("\nNOW turn = %d\n", turn);

	//final output
	switch(turn){
		case 0:
			cout << "DOWN" << endl;
			break;
		case 1:
			cout << "UP" << endl;
			break;
		case 2:
			cout << "LEFT" << endl;
			break;
		case 3:
			cout << "RIGHT" << endl;
			break;
		default:
			break;
	}
}
int main(){

	int i, j; 			//variables
	int A, B;
	char role;
	scanf("%d\n%d %d\n", &ROUND, &row, &col);

	for(i = 0; i < col; ++i){
		for(j = 0; j < row; ++j){
			scanf("%c%*c", &Map[i][j]);
		}
	}

	scanf("%d\n%d\n%c", &A, &B, &role);

	int Sx, Sy;
	for(i = 0; i < col; ++i){
		for(j = 0; j < row; ++j){
			if(Map[i][j] == role){
				Sx = i;
				Sy = j;
			}
		}
	}

	int fir_score = 0;
	if(role == 'A')
		fir_score = A;
	else if(role == 'B')
		fir_score = B;

	hunt(Sx, Sy, fir_score);

	return 0;
}
