#include <stdio.h>

/*將物件依殺傷力轉換成對應數*/
int Choice(int m,int n,int M,char x){
    int choice;
    if(m<0 || n<0 || m>=M || n>=M || x=='x' || x=='A' || x=='B'){
        choice = -4;
    }else if(x=='t'){
        choice = -3;
    }else if(x=='b'){
        choice = 0;
    }else if(x=='n'){
        choice = -1;
    }else if(x=='.'){
        choice = -2;
    }else if(x=='m'){
        choice = 1;
    }else if(x=='s'){
        choice = 2;
    }
    return choice;
}

int main(void)
{
    /*讀取資料*/
    int Run, M, N, Ascore, Bscore;
    char Who;
    scanf("%d%d%d", &Run, &M, &N);
    char map[M][N];
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            scanf(" %c", &map[i][j]);
        }
    }
    scanf("%d%d %c", &Ascore, &Bscore, &Who);
    
    int DirX[4] = {-1,0,1,0}; int DirY[4] = {0,1,0,-1};
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(map[i][j]==Who)
            {   
                /*將機器人所在位置的四個方向之物件換成對應數*/
                int dir[4]={};
		        for(int k=0; k<4; k++)
                {
			        dir[k] = Choice(i+DirX[k], j+DirY[k], M, map[i+DirX[k]][j+DirY[k]]);
			        /*printf("dir[%d]:%d\n",k,dir[k]);*/
		        }

                int max=-5;
                int direction;
                for(int p=0; p<4; p++)
                {
                    /*找四個方向中對應數最大者*/
		            if(dir[p]>max)
                    {
                        max = dir[p];
                        direction = p;
                        /*printf("** p=%d direction:%d\n",p,direction);*/
                    }
                    
                    /*當對應數與目前最大值相同時，使機器人各往兩方向走，看哪個方向的再下一步能獲取較大的對應數*/
		            else if(dir[p]==max)
                    {
                        /*機器人試著往第一個方向走*/
			            int same_dir[4]={};
			            int same_max=-5;
			            if(direction==0){
				            for(int k=0;k<4;k++){
					            same_dir[k] = Choice(i-1+DirX[k],j+DirY[k],M,map[i-1+DirX[k]][j+DirY[k]]);
					            /*printf("0* same_dir[%d]:%d\n",k,same_dir[k]);*/
				            }
			            }
			            if(direction==1){
				            for(int k=0;k<4;k++){
					            same_dir[k] = Choice(i+DirX[k],j+1+DirY[k],M,map[i+DirX[k]][j+1+DirY[k]]);
					            /*printf("1* same_dir[%d]:%d\n",k,same_dir[k]);*/
				            }
			            }
			            if(direction==2){
				            for(int k=0;k<4;k++){
					            same_dir[k] = Choice(i+1+DirX[k],j+DirY[k],M,map[i+1+DirX[k]][j+DirY[k]]);
					           /* printf("2* same_dir[%d]:%d\n",k,same_dir[k]);*/
				            }
			            }
			            if(direction==3){
				            for(int k=0;k<4;k++){
					            same_dir[k] = Choice(i+DirX[k],j-1+DirY[k],M,map[i+DirX[k]][j-1+DirY[k]]);
					            /*printf("3* same_dir[%d]:%d\n",k,same_dir[k]);*/
				            }
			            }
			            for(int k=0; k<4; k++){
				            if(same_dir[k]>same_max){
					            same_max = same_dir[k];
				            }
			            }
			            /*printf("same_max:%d\n",same_max);*/

                        /*機器人試往第二個方向走*/
			            int same_dir2[4]={};
			            int same_max2=-5;
			            if(p==0){
				            for(int k=0;k<4;k++){
					            same_dir2[k] = Choice(i-1+DirX[k],j+DirY[k],M,map[i-1+DirX[k]][j+DirY[k]]);
					            /*printf("0* same_dir2[%d]:%d\n",k,same_dir2[k]);*/
				            }
			            }
			            if(p==1){
				            for(int k=0;k<4;k++){
					            same_dir2[k] = Choice(i+DirX[k],j+1+DirY[k],M,map[i+DirX[k]][j+1+DirY[k]]);
					            /*printf("1* same_dir2[%d]:%d\n",k,same_dir2[k]);*/
				            }
			            }
			            if(p==2){
				            for(int k=0;k<4;k++){
					            same_dir2[k] = Choice(i+1+DirX[k],j+DirY[k],M,map[i+1+DirX[k]][j+DirY[k]]);
					            /*printf("2* same_dir2[%d]:%d\n",k,same_dir2[k]);*/
				            }
			            }
			            if(p==3){
				            for(int k=0;k<4;k++){
				                same_dir2[k] = Choice(i+DirX[k],j-1+DirY[k],M,map[i+DirX[k]][j-1+DirY[k]]);
				                /*printf("3* same_dir2[%d]:%d\n",k,same_dir2[k]);*/
				            }
			            }		
			            for(int k=0; k<4;k++){
				            if(same_dir2[k]>same_max2){
					            same_max2 = same_dir2[k];
				            }
			            }
			            /*printf("same_max2:%d\n",same_max2);*/
			            direction = same_max > same_max2 ? direction : p ;
		            }
                }
                
                /*printf("direction:%d\n",direction);*/
                if(direction == 0){
                    printf("UP\n");
                }
                if(direction == 1){
                    printf("RIGHT\n");
                }
                if(direction == 2){
                    printf("DOWN\n");
                }
                if(direction == 3){
                    printf("LEFT\n");
                }
            }
        }
    }
    

}
