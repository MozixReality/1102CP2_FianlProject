#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
int Round, M, N,tmpScore;
int dirx[] = {0,1,0,-1},diry [] = {1,0,-1,0};
char Graph[20][20]={};
bool visited[20][20];
string sym[] = {"RIGHT","DOWN","LEFT","UP"};
//ensure the direction of object(str) is valid  
bool valid(int x, int y){
	/*	if(Round > M*N/4)
		return (
		x >= 0 && x < M && y >=0 && y < N && 
		Graph[x][y] != 'x' && 
		Graph[x][y] != 'A' && Graph[x][y] != 'B' //&& visited[x][y] == false
		);
		else
	 */		return (
			 x >= 0 && x < M && y >=0 && y < N && 
			 Graph[x][y] != 'x' && 
			 Graph[x][y] != 'A' && Graph[x][y] != 'B' //&& visited[x][y] == false
			 );

}
//count scores
int newScore(int x, int y, int oldScore){
	if(Graph[x][y] == 'm') oldScore += 1;
	else if(Graph[x][y] == 'n') oldScore -= 1;
	else if(Graph[x][y] == 's') oldScore *= 2;
	else if(Graph[x][y] == 't') oldScore /= 2;
	return oldScore;
}


int ans = -10000,setRound = 7;
string finalDir ="NO";
void DFS(int x, int y, int score, int round, string dir, int dirOri, int setRound){
	if(round >= setRound){
		if(/*valid_ == true &&*/ score > ans){
			finalDir = dir;
			ans = score;
		}
		return;
	}
	else{	
		//visited[x][y] = true;
		score = newScore(x,y,score);
		if(Graph[x][y] == 'b') round +=2;
		for(int i = 0; i < 4; i++){
			if(valid(x+dirx[i],y+diry[i]) && ((i == dirOri) || (i%2 == (dirOri+1)%2)))
				DFS(x+dirx[i], y+diry[i], score, round+1, dir, i, setRound);
		}
	}
	//return;
}
int main(void){
	int A, B;
	char me;
	cin >> Round >> M >> N;
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
			cin >> Graph[i][j];
	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
			visited[i][j] = false;
	cin >> A >> B >> me;
	int x, y, rand_seed;

	for(int i=0;i<M;i++)
		for(int j=0;j<N;j++)
			if(Graph[i][j] == me){
				x = i;
				y = j;
			}
	int sco, specialx,specialy;
	if(me == 'A') sco = A; else sco = B;
//	if(Round <= 500){
		for(int i = 0; i < 4; ++i){
			if(valid(x+dirx[i],y+diry[i]))
				DFS(x+dirx[i],y+diry[i],sco,0,sym[i],i,setRound);
		}
//	}
//	else{
		/*for(int i=0;i<M;i++)
			for(int j=0;j<N;j++)
				if(valid(i,j) && Graph[i][j] != '.'){
					
					 specialx = i;
					 specialy = j;
				}
		setRound = 1;
	*/	for(int i = 0; i < 4; ++i){
			if(valid(x+dirx[i],y+diry[i]))
				DFS(x+dirx[i],y+diry[i],sco,0,sym[i],i,setRound);
		}
//	}
	cout << finalDir << endl;
}
