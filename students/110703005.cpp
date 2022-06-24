#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct coordinate {
        int i ;
        int j ;
} queue[500]={}, start, goal, temp, myLocation, nxLocation ;

int ROUND, sideM, sideN, scoreA, scoreB, myScore ;
int up, down, left, right ;
int rear=0, front=0 ;
int stepRecord, step[21][21]={}, point[21][21]={} ;
char map[21][21]={}, dir[6]="UP", ME, OPNT ;

void inputMap(void) {
        scanf("%d\n%d %d\n", &ROUND, &sideM, &sideN) ;
        for (int m=0;m<sideM;++m) {
                for (int n=0;n<sideN-1;++n)
                        scanf("%c ", &map[m][n]) ;
                scanf("%c\n", &map[m][sideN-1]) ;
        }
        scanf("%d\n%d\n", &scoreA, &scoreB) ;
        scanf("%c", &ME) ;
        if (ME=='A') {
                myScore=scoreA ;
                OPNT='B' ;
        }
        else {
                myScore=scoreB ;
                OPNT='A' ;
        }
}

bool isValidMove(int i, int j) {
        return
        (
                i>=0 && i<sideM && j>=0 && j<sideN && map[i][j]!='x'
                && map[i][j]!='A' && map[i][j]!='B'
        );
}

bool isNearbyOpponent(int i, int j) {
        return
        (
                map[i-1][j]==OPNT || map[i+1][j]==OPNT || map[i][j+1]==OPNT || map[i][j-1]==OPNT
        ) ;
}

bool isWithin15steps(int i, int j) {
        return (step[i][j]<15) ;
}

int SWITCH (int val, char item) {

        switch(item) {

                case 'm' :
                        val+=1 ;
                        break ;

                case 'n' :
                        val-=1 ;
                        break ;

                case 's' :
                        val*=2 ;
                        break ;

                case 't' :
                        val/=2 ;
                        break ;

                default :
                        break ;
        }
        return val ;
}

void enqueue(int i, int j) {
        queue[rear].i=i ;
        queue[rear++].j=j ;
}

struct coordinate push() {
        return queue[front++] ;
}

int bfs(int i, int j) {

        int hor[4]={1, 0, -1,  0} ;
        int ver[4]={0, 1,  0, -1} ;

        point[myLocation.i][myLocation.j]=myScore ;
        enqueue(i, j) ;
        step[i][j]=1 ;
        while (front<rear) {
                temp=push() ;
                if (isNearbyOpponent(temp.i, temp.j))
                        continue ;
                for (int k=0;k<4;++k) {
                        int ni=temp.i+ver[k] ;
                        int nj=temp.j+hor[k] ;
                        if (isValidMove(ni, nj) && step[ni][nj]==0 && isWithin15steps(temp.i, temp.j)) {
                                enqueue(ni, nj) ;
                                step[ni][nj]=step[temp.i][temp.j]+1 ;
                                point[ni][nj]=SWITCH(point[temp.i][temp.j], map[ni][nj]) ;
                        }
                }
        }
        int bestDP=0 ;
        for (int a=0;a<sideM;++a) {
                for (int b=0;b<sideN;++b) {
                        if (point[a][b]>bestDP) {
                                bestDP=point[a][b] ;
                                stepRecord=step[a][b] ;
                        }
                }
        }

        memset(step, 0, sizeof(step[0][0])*21*21) ;
        memset(point, 0, sizeof(point[0][0])*21*21) ;

        return bestDP ;
}

bool isBetter(int preStep, int newStep) {
        return (newStep<preStep) ;
}

void computePotent(int i, int j) {

        int upScore=0, rightScore=0, downScore=0, leftScore=0 ;
        int upStep=0, rightStep=0, downStep=0, leftStep=0 ;
        if (isValidMove(i-1, j)) { /*UP is valid*/
                step[i][j]=1 ;
                point[i-1][j]=SWITCH(myScore, map[i-1][j]) ;
                upScore=bfs(i-1, j) ;
                upStep=stepRecord ;
        }
        if (isValidMove(i, j+1)) { /*RIGHT is valid*/
                step[i][j]=1 ;
                point[i][j+1]=SWITCH(myScore, map[i][j+1]) ;
                rightScore=bfs(i, j+1) ;
                rightStep=stepRecord ;
        }

        if (isValidMove(i+1, j)) { /*DOWN is valid*/
                step[i][j]=1 ;
                point[i+1][j]=SWITCH(myScore, map[i+1][j]) ;
                downScore=bfs(i+1, j) ;
                downStep=stepRecord ;
        }

        if (isValidMove(i, j-1)) { /*LEFT is valid*/
                step[i][j]=1 ;
                point[i][j-1]=SWITCH(myScore, map[i][j-1]) ;
                leftScore=bfs(i, j-1) ;
                leftStep=stepRecord ;
        }

        int bestPotent=upScore ;
        int bestStep=upStep ;
        nxLocation.i=myLocation.i-1 ;
        nxLocation.j=myLocation.j ;
        if (downScore>bestPotent || (downScore==bestPotent && isBetter(bestStep, downStep))) {
                strcpy(dir, "DOWN") ;
                bestPotent=downScore ;
                bestStep=downStep ;
                nxLocation.i=myLocation.i+1 ;
                nxLocation.j=myLocation.j ;
        }
        if (leftScore>bestPotent || (leftScore==bestPotent && isBetter(bestStep, leftStep))) {
                strcpy(dir, "LEFT") ;
                bestPotent=leftScore ;
                bestStep=leftStep ;
                nxLocation.i=myLocation.i ;
                nxLocation.j=myLocation.j-1 ;
        }
        if (rightScore>bestPotent || (rightScore==bestPotent && isBetter(bestStep, rightStep))) {
                strcpy(dir, "RIGHT") ;
                bestPotent=rightScore ;
                bestStep=
                nxLocation.i=myLocation.i ;
                nxLocation.j=myLocation.j+1 ;
        }

}

int main(void)
{
        inputMap() ;

        point[myLocation.i][myLocation.j]=myScore ;
        for (int i=0;i<sideM;++i) {
                for (int j=0;j<sideN;++j) {
                        if (map[i][j]==ME) {
                                myLocation.i=i ;
                                myLocation.j=j ;
                        }
                }
        }
        if (ROUND>1950) { /*avoid every 't' when the game is about to end*/
                for (int i=0;i<sideM;++i) {
                        for (int j=0;j<sideN;++j) {
                                if (map[i][j]=='t')
                                        map[i][j]=='x' ;
                        }
                }
        }

        computePotent(myLocation.i, myLocation.j) ;
        printf("%s\n", dir) ;
}