#include <stdio.h>

int best_score,my_score,your_score;
int best_direction=3,size_x,size_y;
char table[20][20];

typedef struct block_information{
	int x;
	int y;
}block_information;

typedef struct road{//1=up 2=down 3=left 4=right //b bomb,m +1,n -1,s *2,t /2,x wall
	int nowx;
	int nowy;
	int score;
	int start_direction;
	block_information walked_path[20];
}road;

void all_path(road path,int step)
{
	int valid=1,repeat=0;
	if(step>=13)
	{
		valid=0;
		repeat=1;
	}
	if(path.nowx<0||path.nowx>=size_x||path.nowy<0||path.nowy>=size_y)
	{
		valid=0;
	}
	else if(table[path.nowx][path.nowy]-'A'==0||table[path.nowx][path.nowy]-'B'==0||table[path.nowx][path.nowy]-'x'==0)
	{
		valid=0;
	}
	if(valid==1)
	{
		for(int h=step-1;h>=1;--h)///////
		{
			if(path.nowx==path.walked_path[h].x&&path.nowy==path.walked_path[h].y)
			{
				repeat=1;
			}
		}////
		if(repeat==0)
		{
			switch(table[path.nowx][path.nowy])
			{
				case 'm':
					path.score+=1;
					break;
				case 'n':
					path.score-=1;
					break;
				case 's':
					path.score*=2;
					break;
				case 't':
					path.score/=2;
					break;
				case '.':
					break;
				case 'b':
					break;
			}
		}
		if(path.score>=best_score)
		{
			best_score=path.score;
			best_direction=path.start_direction;
		}
		path.walked_path[step].x=path.nowx;
		path.walked_path[step].y=path.nowy;
		//
		road up=path,down=path,left=path,right=path;
		step++;
		//
		up.nowy+=1;	
		all_path(up,step);
		//
		down.nowy-=1;
		all_path(down,step);
		//
		left.nowx-=1;
		all_path(left,step);
		//
		right.nowx+=1;
		all_path(right,step);
		//
	}
}

int main()
{
	int round,score_A,score_B;
	scanf("%d\n%d %d",&round,&size_x,&size_y);
	char controlling_player,ax,ay,bx,by,startx,starty;
	for(int i=0;i<size_x;++i)
	{
		for(int j=0;j<size_y;++j)
		{
			scanf("%s",&table[i][j]);
			if(table[i][j]=='A')
			{
				ax=i;
				ay=j;
			}
			else if(table[i][j]=='B')
			{
				bx=i;
				by=j;
			}
		}
	}
	scanf("%d\n%d\n%c",&score_A,&score_B,&controlling_player);
	if(controlling_player=='A')
	{
		my_score=score_A;
		your_score=score_B;
		startx=ax;
		starty=ay;
	}
	else
	{
		my_score=score_B;
		your_score=score_A;
		startx=bx;
		starty=by;
	}
	int road_score=my_score,step=1;
	best_score=my_score;
	road up,down,left,right;
	//
	up.nowx=startx;
	up.nowy=starty+1;
	up.score=road_score;
	up.start_direction=1;	
	up.walked_path[step].x=up.nowx;	
	up.walked_path[step].y=up.nowy;
	all_path(up,step);
	//
	down.nowx=startx;
	down.nowy=starty-1;
	down.score=road_score;
	down.start_direction=2;	
	down.walked_path[step].x=down.nowx;	
	down.walked_path[step].y=down.nowy;
	all_path(down,step);
	//
	left.nowx=startx-1;
	left.nowy=starty;
	left.score=road_score;
	left.start_direction=3;	
	left.walked_path[step].x=left.nowx;	
	left.walked_path[step].y=left.nowy;
	all_path(left,step);
	//
	right.nowx=startx+1;
	right.nowy=starty;
	right.score=road_score;
	right.start_direction=4;	
	right.walked_path[step].x=right.nowx;	
	right.walked_path[step].y=right.nowy;
	all_path(right,step);
	//
	switch(best_direction)//1=right 2=left 3=up 4=down //origin 1=up 2=down 3=left 4=right
	{
		case 1:
			printf("RIGHT ");
			break;
		case 2:
			printf("LEFT ");
			break;
		case 3:
			printf("UP ");
			break;
		case 4:
			printf("DOWN ");
			break;
	}
}
