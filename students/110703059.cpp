#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State{
	int x;
	int y;
}state;

int main(){
	int round=0, size=0, ascore=0, bscore=0, score=0;
	int i=0, j=0;
	int ax=0, ay=0, bx=0, by=0, sx=0, sy=0;
	int step=-1;
	int ans[10]={0};
	int dx[4]={1, 0, -1, 0};
	int dy[4]={0, 1, 0, -1};	//{DOWN, RIGHT, UP, LEFT}
	int move [10]={0};
	char map[21][21];
	char player;
	scanf("%d\n", &round);
	scanf("%d %d", &size, &size);
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			scanf("%s", &map[i][j]);
			if(map[i][j]=='A'){
				ax=i;
				ay=j;
			}
			if(map[i][j]=='B'){
				bx=i;
				by=j;
			}
		}
	}
	scanf("%d\n%d\n", &ascore, &bscore);
	scanf("%c", &player);
	if(player=='A'){
		sx=ax;
		sy=ay;
		score=ascore;
	}
	else if(player=='B'){
		sx=bx;
		sy=by;
		score=bscore;
	}
	for(i=0; i<4; ++i){
		if(sx+dx[i]>=0&&sx+dx[i]<size&&sy+dy[i]>=0&&sy+dy[i]<size&&map[sx+dx[i]][sy+dy[i]]!='x'&&map[sx+dx[i]][sy+dy[i]]!='A'&&map[sx+dx[i]][sy+dy[i]]!='B'){
			move[i]=1;		//move[i]=1,valid to move; move[i]=2,not empty
			ans[i]=score;
			if(map[sx+dx[i]][sy+dy[i]]=='m'){
				ans[i]=score+1;
				move[i]=2;
			}
			else if(map[sx+dx[i]][sy+dy[i]]=='n'){
				ans[i]=score-1;
				move[i]=2;
			}
			else if(map[sx+dx[i]][sy+dy[i]]=='s'){
				ans[i]=score*2;
				move[i]=2;
			}
			else if(map[sx+dx[i]][sy+dy[i]]=='t'){
				ans[i]=score/2;
				move[i]=2;
			}
			else if(map[sx+dx[i]][sy+dy[i]]=='b'){
				move[i]=2;
			}
		}
	}
	for(i=0; i<4; ++i){
		if(move[i]==2){
			if(ans[i]>=score){
				step=i;
			}
		}
	}
	if(step<0){
		for(i=0; i<4; ++i){
			if(move[i]==2){
				step=i;
				break;
			}
		}
	}
	if(step<0){
		int bfs[4];
		memset(bfs, 1000, sizeof(bfs));
		for(i=0; i<4; ++i){
			if(sx+dx[i]>=0&&sx+dx[i]<size&&sy+dy[i]>=0&&sy+dy[i]<size&&map[sx+dx[i]][sy+dy[i]]!='x'&&map[sx+dx[i]][sy+dy[i]]!='A'&&map[sx+dx[i]][sy+dy[i]]!='B'){
				state queue[400];
				int rear=0, front=0;
				queue[rear].x=sx+dx[i];
				queue[rear].y=sy+dy[i];
				rear++;
				int table[size][size];
				memset(table, -1, sizeof(table));
				table[sx+dx[i]][sy+dy[i]]=0;
				for( ; front<rear; ++front){
					sx=queue[front].x;
					sy=queue[front].y;
					for(j=0; j<4; ++j){
						if(sx+dx[j]>=0&&sx+dx[j]<size&&sy+dy[j]>=0&&sy+dy[j]<size&&map[sx+dx[j]][sy+dy[j]]!='x'&&map[sx+dx[j]][sy+dy[j]]!='A'&&map[sx+dx[j]][sy+dy[j]]!='B'&&map[sx+dx[j]][sy+dy[j]]=='.'&&table[sx+dx[j]][sy+dy[j]]==-1){
							queue[rear].x=sx+dx[j];
							queue[rear].y=sy+dy[j];
							++rear;
							table[sx+dx[j]][sy+dy[j]]=table[sx][sy]+1;
						}
						else if(sx+dx[j]>=0&&sx+dx[j]<size&&sy+dy[j]>=0&&sy+dy[j]<size&&map[sx+dx[j]][sy+dy[j]]!='x'&&map[sx+dx[j]][sy+dy[j]]!='A'&&map[sx+dx[j]][sy+dy[j]]!='B'&&map[sx+dx[j]][sy+dy[j]]!='.'){
							bfs[i]=table[sx][sy]+1;
							break;
							break;
						}
					}
				}
			}
		}
		for(i=0; i<4; ++i){
			int min=1000;
			if(bfs[i]<=min&&move[i]>0){
				min=bfs[i];
				step=i;
			}
		}
	}


	if(step==0){
		printf("DOWN\n");
	}
	if(step==1){
		printf("RIGHT\n");
	}
	if(step==2){
		printf("UP\n");
	}
	if(step==3){
		printf("LEFT\n");
	}


	return 0;
}

