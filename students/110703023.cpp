#include<stdio.h>
#include<limits.h>
#define SIZE 20
#define STEP 7
#define MAX 500
#define MIN 20
struct Data{
        int round; int wid; int len; int my_score; int op_score;
        int op_r; int op_c; int my_r; int my_c;
        char my_role; char op_role; char role;
        int record_direction; int step_of_find_op; int min_step_between_us; int flag_get_points;
        int num_block; int num_mushroom; int num_star;
}data;
struct place{
        int row; int col;
}location[6];
struct state{
        int row; int col;
}queue[MAX];
struct Block{
        int row; int col;
}block[50];
enum Direction{
        up, down, left, right
}direction;
enum Action{
        find_points, find_op, find_block, escape, tmp_star, tmp_other
}action;
char map[SIZE][SIZE];
int receive_direction[SIZE][SIZE], count_direction[SIZE][SIZE], step[SIZE][SIZE];
int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
void receive_data(void);
int count_grade(int, int, int);
int count_steps(int, int);
int search(int, int);
void find_action(int, int);
void print_action(void);
int judge_obstacle(int, int);//opponent, wall, out of the map
int judge_block_region(int, int);
int judge_blocked_up_me(int, int);
int judge_blocked_up_op(void);
int main()
{
        int action;
        receive_data();
        if(search(data.my_r, data.my_c)){
                if(judge_blocked_up_me(location[find_block].row, location[find_block].col)){
                        if((data.role == 'A' && data.min_step_between_us % 2 == 0) || (data.role == 'B' && data.min_step_between_us % 2 == 1))
                                action = find_points;
                        else if(((data.role == 'A' && data.min_step_between_us - step[location[escape].row][location[escape].col] * 2 >= 0) || (data.role == 'B' && data.min_step_between_us - step[location[escape].row][location[escape].col] * 2 > 0)))
                                action = find_points;
                        else
                                action = find_op;
                }
                else if(judge_blocked_up_op()){//Maybe I cannot block op
                        if(data.min_step_between_us > 1){
                                if((data.role == 'A' && (step[location[find_op].row][location[find_op].col] + 1) % 2 == 0) || (data.role == 'B') && (step[location[find_op].row][location[find_op].col] + 1) % 2 == 1)
                                        action = find_op;
                                else if(data.flag_get_points)
                                        action = find_points;
                                else
                                        action = find_op;
                        }
                        else
                                action = find_points;//because no any places can encounter op
                }
                else if(data.flag_get_points){
                        if(data.min_step_between_us > 1)
                                action = find_points;
                        else
                                action = find_op;//Because data.min_step_between_us == 1, I have chance to be blocked
                }
                else
                        action = find_op;
        }
        else{
                if(judge_block_region(data.my_r, data.my_c))
                        action = find_op;
                else
                        action = find_block;
        }
        find_action(location[action].row, location[action].col);
        print_action();
        return 0;
}
void receive_data()
{
        int score1, score2, Ar, Ac, Br, Bc;
        data.num_mushroom = 0, data.num_star = 0;
        scanf("%d %d %d", &data.round, &data.wid, &data.len);
        for(int i = 0; i < data.len; ++i){
                for(int j = 0; j < data.wid; ++j){
                        scanf("\n%c", &map[i][j]);
                        if(map[i][j] == 'A')
                                Ar = i, Ac = j;
                        else if(map[i][j] == 'B')
                                Br = i, Bc = j;
                        else if(map[i][j] == 'm')
                                data.num_mushroom++;
                        else if(map[i][j] == 's')
                                data.num_star++;
                }
        }
        scanf("%d %d %c", &score1, &score2, &data.role);
        if(data.role == 'A'){
                data.my_score = score1, data.op_score = score2;
                data.my_role = 'A', data.op_role = 'B';
                data.my_r = Ar, data.my_c = Ac, data.op_r = Br, data.op_c = Bc;
        }
        else{
                data.my_score = score2, data.op_score = score1;
                data.my_role = 'B', data.op_role = 'A';
                data.op_r = Ar, data.op_c = Ac, data.my_r = Br, data.my_c = Bc;
        }
        for(int i = 0; i < data.len; ++i){
                for(int j = 0; j < data.len; ++j){
                        if(judge_block_region(i, j))
                                block[data.num_block].row = i, block[data.num_block++].col = j;
                }
        }
}
int count_grade(int row, int col, int score)
{
        if(map[row][col] == 'm')
                return score + 1;
        else if(map[row][col] == 'n')
                return score - 1;
        else if(map[row][col] == 's')
                return score * 2;
        else if(map[row][col] == 't')
                return score / 2;
        else//bomb
                return score;
}
int count_steps(int row, int col)
{
        if(map[row][col] == 'b')
                return 4;
        else
                return 1;
}
int search(int row, int col)
{
        int score[SIZE][SIZE] = {0}, star[SIZE][SIZE] = {0}, toxic[SIZE][SIZE] = {0};
        int rear = 0, front = 0, flag_record_dead = 0, flag_record_escape = 0, flag_obstacle, flag_star = 0, min_step = INT_MAX;
        double best_rate = -1000.0, best_rate_of_op = -1000.0, best_rate_of_star = -1000.0;
        data.min_step_between_us = INT_MAX;
        queue[rear].row = row, queue[rear++].col = col;
        step[row][col] = 1, score[row][col] = data.my_score;
        while(front < rear){
                row = queue[front].row, col = queue[front].col;
                if(step[row][col] - 1 <= 1000 - data.round + 1 && !(star[row][col] && toxic[row][col]) && map[row][col] != '.'){
                        if(step[row][col] <= STEP && ((double)score[row][col] - data.my_score) / (step[row][col] - 1) > best_rate){
                                best_rate = ((double)score[row][col] - data.my_score) / (step[row][col] - 1);
                                location[tmp_other].row = row, location[tmp_other].col = col;
                        }
                        if(map[row][col] == 's' && (double)star[row][col] / (step[row][col] - 1) > best_rate_of_star){
                                best_rate_of_star = (double)star[row][col] / (step[row][col] - 1);
                                flag_star = 1;
                                location[tmp_star].row = row, location[tmp_star].col = col;
                        }
                }
                if(!flag_record_dead && judge_block_region(row, col)){
                        flag_record_dead = 1;
                        location[find_block].row = row, location[find_block].col = col;
                }
                for(int i = 0; i < 4; ++i){
                        flag_obstacle = judge_obstacle(row + dr[i], col + dc[i]);
                        if((!flag_obstacle && map[row + dr[i]][col + dc[i]] != 't') || map[row + dr[i]][col + dc[i]] == data.op_role || map[row + dr[i]][col + dc[i]] == data.my_role)
                                count_direction[row][col]++;
                        if(step[row + dr[i]][col + dc[i]] == 0){
                                if(map[row + dr[i]][col + dc[i]] == data.op_role){
                                        if(map[row][col] != data.my_role && !toxic[row][col]){
                                                if(!data.num_star && !data.num_mushroom){
                                                        if(step[row][col] - 1 < min_step){
                                                                location[find_op].row = row, location[find_op].col = col;
                                                                min_step = step[row][col] - 1;
                                                        }
                                                }
                                                else{
                                                        if(((double)score[row][col] - data.my_score) / (step[row][col] - 1) > best_rate_of_op){
                                                                best_rate_of_op = ((double)score[row][col] - data.my_score) / (step[row][col] - 1);
                                                                location[find_op].row = row, location[find_op].col = col;
                                                        }
                                                }
                                        }
                                        if(step[row][col] < data.min_step_between_us)
                                                data.min_step_between_us = step[row][col];
                                }
                                if(map[row + dr[i]][col + dc[i]] == 't')
                                        toxic[row + dr[i]][col + dc[i]] = toxic[row][col] + 1;
                                else
                                        toxic[row + dr[i]][col + dc[i]] = toxic[row][col];
                                if(map[row + dr[i]][col + dc[i]] == 's')
                                        star[row + dr[i]][col + dc[i]] = star[row][col] + 1;
                                else
                                        star[row + dr[i]][col + dc[i]] = star[row][col];
                                if(!flag_obstacle){
                                        step[row + dr[i]][col + dc[i]] = step[row][col] + count_steps(row + dr[i], col + dc[i]);
                                        score[row + dr[i]][col + dc[i]] = count_grade(row + dr[i], col + dc[i], score[row][col]);
                                        receive_direction[row + dr[i]][col + dc[i]] = i;
                                        //(row, col)往i方向走是(row + dr[i], col + dc[i])
                                        queue[rear].row = row + dr[i], queue[rear++].col = col + dc[i];
                                }
                        }
                }
                if(!flag_record_escape && count_direction[row][col] >= 3){
                        flag_record_escape = 1;
                        location[escape].row = row, location[escape].col = col;
                }
                ++front;
        }
        if(flag_star){
                if(data.my_score < (double)data.op_score * 3/4 || best_rate <= 0)
                        location[find_points].row = location[tmp_star].row, location[find_points].col = location[tmp_star].col;
                else
                        location[find_points].row = location[tmp_other].row,location[find_points].col = location[tmp_other].col;
        }
        else
                location[find_points].row = location[tmp_other].row, location[find_points].col = location[tmp_other].col;
        if(flag_star || best_rate > 0)
                data.flag_get_points = 1;
        else
                data.flag_get_points = 0;
        if(rear < MIN)
                return 0;
        else
                return 1;
}
void find_action(int row, int col)
{
        int last_row, last_col;
        while(row != data.my_r || col != data.my_c){
                last_row = row, last_col = col;
                if(receive_direction[row][col] == up)
                        row += dr[down], col += dc[down];
                else if(receive_direction[row][col] == down)
                        row += dr[up], col += dc[up];
                else if(receive_direction[row][col] == left)
                        row += dr[right], col += dc[right];
                else
                        row += dr[left], col += dc[left];
        }
        if(last_row == data.my_r){
                if(data.my_c < last_col)
                        data.record_direction = right;
                else
                        data.record_direction = left;
        }
        else{
                if(data.my_r < last_row)
                        data.record_direction = down;
                else
                        data.record_direction = up;
        }
}
void print_action(void)
{
        if(data.record_direction == up)
                printf("UP\n");
        else if(data.record_direction == down)
                printf("DOWN\n");
        else if(data.record_direction == left)
                printf("LEFT\n");
        else
                printf("RIGHT\n");
}
int judge_obstacle(int row, int col)
{
        if(row < data.len && row >= 0 && col < data.wid && col >= 0 && map[row][col] != 'x' && (row != data.op_r || col != data.op_c))
                return 0;
        else
                return 1;
}
int judge_block_region(int row, int col)
{
        int count = 0;
        for(int i = 0; i < 4; ++i){
                if((!judge_obstacle(row + dr[i], col + dc[i]) && map[row + dr[i]][col + dc[i]] != 't') || map[row + dr[i]][col + dc[i]] == data.my_role || map[row + dr[i]][col + dc[i]] == data.op_role)
                        count++;
        }
        if(count == 1)
                return 1;
        else
                return 0;
}
int judge_blocked_up_me(int row, int col)//place inside the block
{
        int flag_encounter_me = 0;
        while(count_direction[row][col] < 3){
                if(row == data.my_r && col == data.my_c){
                        flag_encounter_me = 1;
                        break;
                }
                if(receive_direction[row][col] == up)
                        row += dr[down], col += dc[down];
                else if(receive_direction[row][col] == down)
                        row += dr[up], col += dc[up];
                else if(receive_direction[row][col] == left)
                        row += dr[right], col += dc[right];
                else
                        row += dr[left], col += dc[left];
        }
        if(flag_encounter_me)
                return 1;
        else
                return 0;
}
int judge_blocked_up_op(void)
{
        for(int i = 0; i < data.num_block; ++i){
                if(!step[block[i].row][block[i].col])
                        return 1;
        }
        return 0;
}