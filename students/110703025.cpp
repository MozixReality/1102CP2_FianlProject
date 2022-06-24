#include<stdio.h>

void initialize(char arr[20][20], int* my_row, int* my_col, int* amy_row, int* amy_col, int* limit, float* my_point, float* amy_point, char* input);
float recursive(char arr[20][20], int my_row, int my_col, float my_point, int step, int limit, char input, int init_point, int dimension, int* B_step, int* ptr);
int close(char arr[20][20] ,int a, int b, int target_a, int target_b);
int detect(char arr[20][20], int my_row, int my_col, int limit, int* step, char input);

int main()
{
        int  my_row, my_col, amy_row, amy_col, limit, max_way, max1_way, way_count= 0, check[4][3], check_flag= 0, filt_cmp, filt[2], B_step= 100, my_step= 1,
             mid_length= 100, mid_length_tmp= mid_length, mid_way, round;
        char arr[20][20], input, output[4][6]= {"UP", "DOWN", "LEFT", "RIGHT"};
        float my_point, amy_point, max_arr[4], max, max1;

        scanf("%d", &round);
        initialize(arr, &my_row, &my_col, &amy_row, &amy_col, &limit, &my_point, &amy_point, &input);

        for(int dimension= 10; dimension> 4; dimension-= 2){
                int dimension_decide= 1;
                max= -100, max1= -100;
                max_arr[0]= recursive(arr, my_row- 1, my_col, my_point, 1, limit, input, my_point, dimension, &B_step, &mid_length);
                if(mid_length_tmp!= mid_length){
                        mid_length_tmp= mid_length;
                        mid_way= 0;
                }
                max_arr[1]= recursive(arr, my_row+ 1, my_col, my_point, 1, limit, input, my_point, dimension, &B_step, &mid_length);
                if(mid_length_tmp!= mid_length){
                        mid_length_tmp= mid_length;
                        mid_way= 1;
                }
                max_arr[2]= recursive(arr, my_row, my_col- 1, my_point, 1, limit, input, my_point, dimension, &B_step, &mid_length);
                if(mid_length_tmp!= mid_length){
                        mid_length_tmp= mid_length;
                        mid_way= 2;
                }
                max_arr[3]= recursive(arr, my_row, my_col+ 1, my_point, 1, limit, input, my_point, dimension, &B_step, &mid_length);
                if(mid_length_tmp!= mid_length){
                        mid_length_tmp= mid_length;
                        mid_way= 3;
                }
                for(int i= 0; i< 4; i++){
                        if(max_arr[i]> max){
                                max1= max;
                                max1_way= max_way;
                                max= max_arr[i];
                                max_way= i;
                        }
                        else if(max_arr[i]== max)
                                dimension_decide= 0;
                }
                if(dimension_decide== 1)
                        break;
        }
        if(max== 0)
                max_way= mid_way;



        if(close(arr, my_row- 1, my_col, amy_row, amy_col)){
                check[check_flag][0]= my_row- 1;
                check[check_flag][1]= my_col;
                check[check_flag++][2]= 0;
        }
        if(close(arr, my_row+ 1, my_col, amy_row, amy_col)){
                check[check_flag][0]= my_row+ 1;
                check[check_flag][1]= my_col;
                check[check_flag++][2]= 1;
        }
        if(close(arr, my_row, my_col- 1, amy_row, amy_col)){
                check[check_flag][0]= my_row;
                check[check_flag][1]= my_col- 1;
                check[check_flag++][2]= 2;
        }
        if(close(arr, my_row, my_col+ 1, amy_row, amy_col)){
                check[check_flag][0]= my_row;
                check[check_flag][1]= my_col+ 1;
                check[check_flag++][2]= 3;
        }
        filt[0]= -100;
        for(int i= 0; i< check_flag; i++){
                filt_cmp= my_point;
                if(arr[check[i][0]][check[i][1]]== 'm') filt_cmp++;
                else if(arr[check[i][0]][check[i][1]]== 'n')    filt_cmp--;
                else if(arr[check[i][0]][check[i][1]]== 's')    filt_cmp*= 2;
                else if(arr[check[i][0]][check[i][1]]== 't')    filt_cmp/= 2;
                filt_cmp= filt_cmp- my_point;
                if(filt_cmp> filt[0]){
                        filt[1]= check[i][2];
                        filt[0]= filt_cmp;
                }
        }

        if(check_flag== 0|| my_point+ filt[0]> amy_point+ 5){
                        arr[my_row][my_col]= 'x';
                        if(max_way== 0){
                                if(!(detect(arr, my_row- 1, my_col, limit, &my_step, input))&& (B_step< my_step* 2- 1&& ((1001-round)>B_step)))
                                        max_way= max1_way;
                        }
                        else if(max_way== 1){
                                if(!(detect(arr, my_row+ 1, my_col, limit, &my_step, input))&& (B_step< my_step* 2- 1&& ((1001- round)> B_step)))
                                        max_way= max1_way;
                        }
                        else if(max_way== 2){
                                if(!(detect(arr, my_row, my_col- 1, limit, &my_step, input))&& (B_step< my_step* 2- 1&& ((1001- round)> B_step)))
                                        max_way= max1_way;
                        }
                        else if(max_way== 3){
                                if(!(detect(arr, my_row, my_col+ 1, limit, &my_step, input))&& (B_step< my_step* 2- 1&& ((1001- round)> B_step)))
                                        max_way= max1_way;
                        }

                printf("%s\n", output[max_way]);
        }
        else
                printf("%s\n", output[filt[1]]);

}



void initialize(char arr[20][20], int* my_row, int* my_col, int* amy_row, int* amy_col, int* limit, float* my_point, float* amy_point, char* input)
{
        int row, col, A_row, A_col, B_row, B_col;
        float A_point, B_point;
        char alpha;
        scanf("%d %d", &row, &col);
        for(int i= 0; i< row; i++){
                for(int k= 0; k< col*2; k++){
                        scanf("%c", &alpha);
                        if(alpha== 'A'){
                                A_row= i;
                                A_col= k/2;
                        }
                        if(alpha== 'B'){
                                B_row= i;
                                B_col= k/2;
                        }
                        if(alpha!= ' ')
                                arr[i][k/2]= alpha;
                }
        }
        scanf("%f", &A_point);
        scanf("%f", &B_point);
        scanf("\n%c", &alpha);
        if(alpha== 'A') {
                *my_point= A_point;
                *amy_point= B_point;
                *my_col= A_col;
                *my_row= A_row;
                *amy_row= B_row;
                *amy_col= B_col;
                *input= 'B';
        }
        else{
                *my_point= B_point;
                *amy_point= A_point;
                *my_col= B_col;
                *my_row= B_row;
                *amy_row= A_row;
                *amy_col= A_col;
                *input= 'A';
        }
        *limit= row;
}
float recursive(char arr[20][20], int my_row, int my_col, float my_point, int step, int limit, char input, int init_point, int dimension, int* B_step, int* ptr)
{
        if(my_row< 0|| my_row>= limit)  return -10000;
        if(my_col< 0|| my_col>= limit)  return -10000;
        if(step> dimension){
                int middle1= limit/2- my_row, middle2= limit/2- my_col;
                if(middle1< 0)  middle1= -middle1;
                if(middle2< 0)  middle2= -middle2;
                middle1= middle1+ middle2;
                if(*ptr> middle1)
                        *ptr= middle1;
                return (my_point- init_point)/(step- 1);
        }
        if(arr[my_row][my_col]== input) {
                if(step< *B_step)
                        *B_step= step;
                return -10000;
        }
        else if(arr[my_row][my_col]== 'x')      return -10000;

        else if(arr[my_row][my_col]== 'm')      my_point++;
        else if(arr[my_row][my_col]== 'n')      my_point--;
        else if(arr[my_row][my_col]== 's')      my_point*= 2;
        else if(arr[my_row][my_col]== 't')      my_point/= 2;
        else if(arr[my_row][my_col]== 'b')      step+= 3;

        char tmp= arr[my_row][my_col];
        float dir[4], max;

        arr[my_row][my_col]= '.';
        dir[0]= recursive(arr, my_row- 1, my_col, my_point, step+ 1, limit, input, init_point, dimension, B_step, ptr);
        dir[1]= recursive(arr, my_row+ 1, my_col, my_point, step+ 1, limit, input, init_point, dimension, B_step, ptr);
        dir[2]= recursive(arr, my_row, my_col- 1, my_point, step+ 1, limit, input, init_point, dimension, B_step, ptr);
        dir[3]= recursive(arr, my_row, my_col+ 1, my_point, step+ 1, limit, input, init_point, dimension, B_step, ptr);

        for(int i= 0; i< 4; i++){
                if(i== 0)       max= dir[i];
                else
                        if(dir[i]> max)
                                max= dir[i];
        }
        arr[my_row][my_col]= tmp;
        return max;
}
int close(char arr[20][20] ,int a, int b, int target_a, int target_b)
{
        if((a== target_a)&& (b== target_b- 1)&& (arr[a][b]!= 'x')&& (arr[a][b]!= 'b'))  return 1;
        else if((a== target_a)&& (b== target_b+ 1)&& (arr[a][b]!= 'x')&& (arr[a][b]!= 'b'))     return 1;
        else if((a== target_a- 1)&& (b== target_b)&& (arr[a][b]!= 'x')&& (arr[a][b]!= 'b'))     return 1;
        else if((a== target_a+ 1)&& (b== target_b)&& (arr[a][b]!= 'x')&& (arr[a][b]!= 'b'))     return 1;
        else    return 0;
}
int detect(char arr[20][20], int my_row, int my_col, int limit, int* step, char input)
{
        int dir[4];
        if(my_row<0 ||my_row>= limit)   return 0;
        if(my_col<0 ||my_col>= limit)   return 0;
        if(arr[my_row][my_col]== input) return 0;
        if(arr[my_row][my_col]== 'x')   return 0;
        if(*step> limit)        return 1;

        (*step)++ ;
        arr[my_row][my_col]= 'x';
        dir[0]= detect(arr, my_row- 1, my_col, limit, step, input);
        dir[1]= detect(arr, my_row+ 1, my_col, limit, step, input);
        dir[2]= detect(arr, my_row, my_col- 1, limit, step, input);
        dir[3]= detect(arr, my_row, my_col+ 1, limit, step, input);

        for(int i= 0; i< 4; i++)
                if(dir[i]> 0)
                        return dir[i];

        return 0;

}