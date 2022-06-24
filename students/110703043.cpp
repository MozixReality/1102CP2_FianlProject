#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char status_table[20][20], ch, turn;
int step_table[20][20] = {}, point_table[20][20] = {}, step_queue[400][2] = {}, path_x_table[20][20] = {}, path_y_table[20][20] = {};
int x_start, y_start, x_current, y_current, x_new, y_new, x_max, y_max, max_point = 0, now_point, x_temp, y_temp;
int x_A, y_A, x_B, y_B, x_enemy, y_enemy;
int move_x[] = {1, 0, -1, 0};
int move_y[] = {0, 1, 0, -1};
int T, M, N, A_point, B_point, final_result = 4;

void print_answer(){
    if(final_result == 0) printf("DOWN\n");
    else if(final_result == 1) printf("RIGHT\n");
    else if(final_result == 2) printf("UP\n");
    else if(final_result == 3) printf("LEFT\n");
}

bool survive(int x_target, int y_target){
    bool edge_check;
    int wall_count = 0;
    //target_check = BFS_target(x_target, y_target);
    for(int i=0;i<4;i++)
        if(x_target + move_x[i] < 0 || x_target + move_x[i] >= M || y_target + move_y[i] < 0 || y_target + move_y[i] >= N || status_table[ x_target + move_x[i] ][ y_target + move_y[i] ] == 'x')
            wall_count ++;
    if(wall_count >= 3) edge_check = true;    
    if(edge_check) return true;
    else return false;
}

void BFS_point(){
    bool check_survive = false;
	step_queue[0][0] = x_start;
	step_queue[0][1] = y_start;
    now_point = point_table[x_start][y_start];
	for(int i=0, j=1 ; i<j ; i++){
		x_current = step_queue[i][0];
		y_current = step_queue[i][1];
		for(int k=0 ; k<4 ; k++){
            now_point = point_table[x_current][y_current];
			x_new = x_current + move_x[k];
			y_new = y_current + move_y[k];
            if(x_new < 0 || y_new < 0) continue;
			if(step_table[x_new][y_new] == 0){
                continue;
            }else if(step_table[x_new][y_new] == -1 || step_table[x_new][y_new] == step_table[x_current][y_current]+1){
				step_table[x_new][y_new] = step_table[x_current][y_current]+1;
				step_queue[j][0] = x_new;
				step_queue[j][1] = y_new;
                if(status_table[x_new][y_new] == 'm'){
                    now_point += 1;
                }else if(status_table[x_new][y_new] == 'n'){
                    now_point -= 1;
                }else if(status_table[x_new][y_new] == 's'){
                    now_point *= 2;
                }else if(status_table[x_new][y_new] == 't'){
                    now_point /= 2;
                }
                if(now_point >= point_table[x_new][y_new]){
                    point_table[x_new][y_new] = now_point;
                    path_x_table[x_new][y_new] = x_current;
                    path_y_table[x_new][y_new] = y_current;
                    //check_survive = survive(x_new, y_new);
                    //if(check_survive) continue;
                    if(point_table[x_new][y_new] > max_point){
                        max_point = point_table[x_new][y_new];
                        x_max = x_new;
                        y_max = y_new;
                    }
                }
				j++;
			}
		}
	}
    for(int i = step_table[x_max][y_max]; i > 1; i--){
        x_temp = x_max;
        y_temp = y_max;
        x_max = path_x_table[x_temp][y_temp];
        y_max = path_y_table[x_temp][y_temp];
    }
    x_temp = x_max - x_start;
    y_temp = y_max - y_start;
    if( x_temp == move_x[0] && y_temp == move_y[0]) final_result = 0;
    else if( x_temp == move_x[1] && y_temp == move_y[1]) final_result = 1;
    else if( x_temp == move_x[2] && y_temp == move_y[2]) final_result = 2;
    else if( x_temp == move_x[3] && y_temp == move_y[3]) final_result = 3;
}

int main(void){
    scanf("%d%d%d",&T ,&M ,&N);
    getchar();
    for(int i=0, j=0; i<M; i++ ){
        while(true){
            ch = getchar();
            if(ch == '\n'){
                j = 0;
                break;
            }else if(ch != ' '){
                status_table[i][j] = ch;
                step_table[i][j] = -1;
                if(ch == 'A'){
                    x_A = i;
                    y_A = j;
                    step_table[i][j] = 0;
                }else if(ch == 'B'){
                    x_B = i;
                    y_B = j;
                    step_table[i][j] = 0;
                }else if(ch == 'x') step_table[i][j] = 0;
                j++;
            }
        }
    }
    scanf("%d%d", &A_point, &B_point);
    getchar();
    scanf("%c", &turn);
    if(turn == 'A'){
        x_start = x_A;
        y_start = y_A;
        point_table[x_start][y_start] = A_point;
    }else if(turn == 'B'){
        x_start = x_B;
        y_start = y_B;
        point_table[x_start][y_start] = B_point;
    }
    BFS_point();  
    print_answer();
}