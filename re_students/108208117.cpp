#include <iostream>
#include <cstdlib>
#include <utility>
#include <string>
#include <climits>


using namespace std;
typedef pair<int, int> PII;

#define F first
#define S second
#define mkp make_pair

int Round, M, N, A,B;
char Graph[20][20]={};
int visited[20][20] = {};
char me,opp;
struct Move
{
	int row, col;
};

bool valid(int x, int y){
	return (
			x >= 0 && x < M && y >=0 && y < N && 
			Graph[x][y] != 'x' && 
			Graph[x][y] != 'A' && Graph[x][y] != 'B'
		   );
}

int evaluate(char sign,int mySco,int oppSco,int isMe)
{	
	if(isMe){
		if(sign=='m')//+1
			mySco=mySco+2;
		else if(sign=='n')//-1
			mySco=mySco-2;
		else if(sign=='s')//*2
			mySco=mySco*2;
		else if(sign=='t')// /2
			mySco=mySco/2;
		else if(sign=='b')
			mySco=mySco+1;
		return mySco;
	}
	else{
		if(sign=='m')//+1
			oppSco=oppSco+2;
		else if(sign=='n')//-1
			oppSco=oppSco-2;
		else if(sign=='s')//*2
			oppSco=oppSco*2;
		else if(sign=='t')// /2
			oppSco=oppSco/2;
		else if(sign=='b')
			oppSco=oppSco+1;
		return oppSco;
	}
}
int minimax(char Graph[20][20], int depth, bool isMax, char sign,int mySco,int oppSco,int meX,int meY,int oppX,int oppY,int alpha,int beta)
{	
	int score,oppsco;

	
	score=evaluate(sign,mySco,oppSco,true);
	oppsco=evaluate(sign,mySco,oppSco,false);
	
	if(depth==13||depth==12)//8 ok
		return score;


	if(isMax){
		int best = INT_MIN;
		
		if(valid(meX+1,meY)&& visited[meX+1][meY] == 0){
			visited[meX+1][meY]=1;
			sign=Graph[meX+1][meY];
			Graph[meX+1][meY]=Graph[meX][meY];
			Graph[meX][meY]='.';
			best=max(best,minimax(Graph,depth+1,!isMax,sign,score,oppsco,meX+1,meY,oppX,oppY,alpha,beta));
			//Undo the move
			visited[meX+1][meY]=0;
			Graph[meX][meY]=me;
			Graph[meX+1][meY]=sign;
			
			alpha = max(alpha, best);
            // Alpha Beta Pruning
            if (beta <= alpha)
                return best;
		}
		if(valid(meX-1,meY)&& visited[meX-1][meY] == 0){
			visited[meX-1][meY]=1;
			sign=Graph[meX-1][meY];
			Graph[meX-1][meY]=Graph[meX][meY];
			Graph[meX][meY]='.';
			best=max(best,minimax(Graph,depth+1,!isMax,sign,score,oppsco,meX-1,meY,oppX,oppY,alpha,beta));
			//Undo the move
			visited[meX-1][meY] = 0;
			Graph[meX][meY]=me;
			Graph[meX-1][meY]=sign;
			alpha = max(alpha, best);
            // Alpha Beta Pruning
            if (beta <= alpha)
                return best;
		}
		if(valid(meX,meY+1)&&visited[meX][meY+1] == 0){
			visited[meX][meY+1]=1;
			sign=Graph[meX][meY+1];
			Graph[meX][meY+1]=Graph[meX][meY];
			Graph[meX][meY]='.';
			best=max(best,minimax(Graph,depth+1,!isMax,sign,score,oppsco,meX,meY+1,oppX,oppY,alpha,beta));
			//Undo the move
			visited[meX][meY+1]=0;
			Graph[meX][meY]=me;
			Graph[meX][meY+1]=sign;
			alpha = max(alpha, best);
            // Alpha Beta Pruning
            if (beta <= alpha)
                return best;
		}
		if(valid(meX,meY-1)&&visited[meX][meY-1]==0){
			visited[meX][meY-1]=1;
			sign=Graph[meX][meY-1];
			Graph[meX][meY-1]=Graph[meX][meY];
			Graph[meX][meY]='.';
			best=max(best,minimax(Graph,depth+1,!isMax,sign,score,oppsco,meX,meY-1,oppX,oppY,alpha,beta));
			//Undo the move
			visited[meX][meY-1]=0;
			Graph[meX][meY]=me;
			Graph[meX][meY-1]=sign;
			alpha = max(alpha, best);
            // Alpha Beta Pruning
            if (beta <= alpha)
                return best;
		}

		return best;
	}
	else{
		int best = INT_MAX;
		
		if(valid(oppX+1,oppY)&& visited[oppX+1][oppY] == 0){
			visited[oppX+1][oppY] = 1;
			sign=Graph[oppX+1][oppY];
			Graph[oppX+1][oppY]=Graph[oppX][oppY];
			Graph[oppX][oppY]='.';
			best=min(best,minimax(Graph,depth+1,isMax,sign,score,oppsco,meX,meY,oppX+1,oppY,alpha,beta));
			//Undo the move
			visited[oppX+1][oppY] = 0;
			Graph[oppX][oppY]=opp;
			Graph[oppX+1][oppY]=sign;

            beta = min(beta, best);
 
            // Alpha Beta Pruning
            if (beta <= alpha)
        		return best;
		}
		if(valid(oppX-1,oppY)&&visited[oppX-1][oppY] ==0){
			visited[oppX-1][oppY] = 1;
			sign=Graph[oppX-1][oppY];
			Graph[oppX-1][oppY]=Graph[oppX][oppY];
			Graph[oppX][oppY]='.';
			best=min(best,minimax(Graph,depth+1,isMax,sign,score,oppsco,meX,meY,oppX-1,oppY,alpha,beta));
			//Undo the move
			visited[oppX-1][oppY] = 0;
			Graph[oppX][oppY]=opp;
			Graph[oppX-1][oppY]=sign;
			beta = min(beta, best);
 
            // Alpha Beta Pruning
            if (beta <= alpha)
        		return best;
		}
		if(valid(oppX,oppY+1)&&visited[oppX][oppY+1] == 0){
			visited[oppX][oppY+1] = 1;
			sign=Graph[oppX][oppY+1];
			Graph[oppX][oppY+1]=Graph[oppX][oppY];
			Graph[oppX][oppY]='.';
			best=min(best,minimax(Graph,depth+1,isMax,sign,score,oppsco,meX,meY,oppX,oppY+1,alpha,beta));
			//Undo the move
			visited[oppX][oppY+1] = 0;
			Graph[oppX][oppY]=opp;
			Graph[oppX][oppY+1]=sign;
			 beta = min(beta, best);
 
            // Alpha Beta Pruning
            if (beta <= alpha)
        		return best;
		}
		if(valid(oppX,oppY-1)&&visited[oppX][oppY-1] == 0){
			visited[oppX][oppY-1] = 1;
			sign=Graph[oppX][oppY-1];
			Graph[oppX][oppY-1]=Graph[oppX][oppY];
			Graph[oppX][oppY]='.';
			best=min(best,minimax(Graph,depth+1,isMax,sign,score,oppsco,meX,meY,oppX,oppY-1,alpha,beta));
			//Undo the move
			visited[oppX][oppY-1] = 0;
			Graph[oppX][oppY]=opp;
			Graph[oppX][oppY-1]=sign;
			 beta = min(beta, best);
 
            // Alpha Beta Pruning
            if (beta <= alpha)
        		return best;
		}

		return best;
	}

}
Move findBestMove(char Graph[20][20],int meX,int meY,int oppX,int oppY){
	int bestSco=INT_MIN;
	int mySco,oppSco;
	if(me=='A'){
		mySco=A;
		oppSco=B;
	}
	else{
		mySco=B;
		oppSco=A;
	}
	Move bestMove;
	bestMove.row=-1;
	bestMove.col=-1;

	char sign;
	if(valid(meX+1,meY)&& visited[meX+1][meY] == 0){
		visited[meX+1][meY] =1;
		sign=Graph[meX+1][meY];
		Graph[meX+1][meY]=Graph[meX][meY];
		Graph[meX][meY]='.';
		int moveSco=minimax(Graph,0,true,sign,mySco,oppSco,meX+1,meY,oppX,oppY,INT_MIN,INT_MAX);
		//Undo the move
		visited[meX+1][meY] =0;
		Graph[meX][meY]=me;
		Graph[meX+1][meY]=sign;
		if (moveSco > bestSco){
			bestMove.row = meX+1;
			bestMove.col = meY;
			bestSco = moveSco;
		}
		//printf("best score: %d \n",bestSco);
	}
	if(valid(meX-1,meY)&&visited[meX-1][meY] ==0){
		visited[meX-1][meY] =1;
		sign=Graph[meX-1][meY];
		Graph[meX-1][meY]=Graph[meX][meY];
		Graph[meX][meY]='.';
		int moveSco=minimax(Graph,0,true,sign,mySco,oppSco,meX-1,meY,oppX,oppY,INT_MIN,INT_MAX);
		//Undo the move
		visited[meX-1][meY] =0;
		Graph[meX][meY]=me;
		Graph[meX-1][meY]=sign;
		if (moveSco > bestSco){
			bestMove.row = meX-1;
			bestMove.col = meY;
			bestSco = moveSco;
		}
		//printf("best score: %d \n",bestSco);
	}
	if(valid(meX,meY+1)&&visited[meX][meY+1] ==0){
		visited[meX][meY+1] =1;
		sign=Graph[meX][meY+1];
		Graph[meX][meY+1]=Graph[meX][meY];
		Graph[meX][meY]='.';
		int moveSco=minimax(Graph,0,true,sign,mySco,oppSco,meX,meY+1,oppX,oppY,INT_MIN,INT_MAX);
		//Undo the move
		visited[meX][meY+1] =0;
		Graph[meX][meY]=me;
		Graph[meX][meY+1]=sign;
		if (moveSco > bestSco){
			bestMove.row = meX;
			bestMove.col = meY+1;
			bestSco = moveSco;
		}
		//printf("best score: %d \n",bestSco);
	}
	if(valid(meX,meY-1)&&visited[meX][meY-1] ==0){
		visited[meX][meY-1] =1;
		sign=Graph[meX][meY-1];
		Graph[meX][meY-1]=Graph[meX][meY];
		Graph[meX][meY]='.';
		int moveSco=minimax(Graph,0,true,sign,mySco,oppSco,meX,meY-1,oppX,oppY,INT_MIN,INT_MAX);
		//Undo the move
		visited[meX][meY-1] =0;
		Graph[meX][meY]=me;
		Graph[meX][meY-1]=sign;
		if (moveSco > bestSco){
			bestMove.row = meX;
			bestMove.col = meY-1;
			bestSco = moveSco;
		}
		//printf("best score: %d \n",bestSco);
	}
	//printf("The value of the best Move is : %d\n\n",bestSco);

	
    return bestMove;
}
int main(void){

	//char me;
	cin >> Round >> M >> N;
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
			cin >> Graph[i][j];
	cin >> A >> B >> me;

	if(me=='A')
		opp='B';
	else
		opp='A';
	int meX,meY,oppX,oppY;//curPos
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++){
			if(Graph[i][j] == me){
				meX = i;
				meY = j;
			}
			else if(Graph[i][j] == opp){
				oppX = i;
				oppY = j;
			}
		}
	//printf("%d %d",meX,meY);
	if(valid(meX-1,meY) && (Graph[meX-1][meY] == 's'||Graph[meX-1][meY] == 'm'))
		printf("UP\n");
	else if(valid(meX+1,meY) && (Graph[meX+1][meY] == 's'||Graph[meX+1][meY] == 'm'))
		printf("DOWN\n");
	else if(valid(meX,meY+1) && (Graph[meX][meY+1] == 's'||Graph[meX][meY+1] == 'm'))
		printf("RIGHT\n");
	else if(valid(meX,meY-1) && (Graph[meX][meY-1] == 's'||Graph[meX][meY-1] == 'm'))
		printf("LEFT\n");
	else{
		Move bestMove = findBestMove(Graph,meX,meY,oppX,oppY);
		if(bestMove.row-meX==1)
		printf("DOWN\n");
		if(bestMove.row-meX==-1)
			printf("UP\n");
		if(bestMove.col-meY==1)
			printf("RIGHT\n");
		if(bestMove.col-meY==-1)
			printf("LEFT\n");

	}
	//  printf("The Optimal Move is : \n");
	//  printf("ROW: %d COL: %d\n\n", bestMove.row,bestMove.col );


	return 0;
	//1
	//8 8
	//A . t m x s x s
	//. x x m n m x m
	//m m b x m t x m
	//x x . m m . n m
	//m n . m m . x x
	//m x t m x b m m
	//m x m n m x x .
	//s x s x m t . B
	//0
	//0
	//A
	/*
	   int x, y, rand_seed;
	   for(int i=0;i<M;i++)
	   for(int j=0;j<N;j++)
	   if(Graph[i][j] == me){
	   x = i;
	   y = j;
	   rand_seed = i + j;
	   }
	 */
	//srand(rand_seed);
	//cout << next_dir(x, y, rand()) << endl;
}
