#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define N 21
#define WIN 1000
#define LOSS -1000
#define CONTINUE 1

using namespace std;
using std::cout;
using std::cin;
using std::endl;

int curr_point(char stuff, int grade){

    if (stuff == 'm'){ //First order
        if (grade < 4) return grade+2;  //get as more as mushroom when point < 4
        else return grade+1;
    }
    else if (stuff == 's') return grade*2;
    else if (stuff == 'n') return grade-1;
    else if (stuff == 't') return grade/2;
    else return grade;

}

// judge where A and B can move
std::vector<std::pair<int, int>> get_legal_moves(char Graph[N][N], char marker, int row, int col)
{
	std::vector<std::pair<int, int>> legal_moves;
    for(int i=0; i<row; ++i){
        for(int j=0; j<col; ++j){
            if(Graph[i][j] == marker){ //(A is (0,0))
                if ( Graph[i+1][j] != 'x' && Graph[i+1][j] != 'A' && Graph[i+1][j] != 'B' && i+1 < row) //dowm
                    legal_moves.push_back(std::make_pair(i+1, j));
                if ( Graph[i-1][j] != 'x' && Graph[i-1][j] != 'A' && Graph[i-1][j] != 'B' && i-1 >=0 ) //up
                    legal_moves.push_back(std::make_pair(i-1, j));
                if ( Graph[i][j+1] != 'x' && Graph[i][j+1] != 'A' && Graph[i][j+1] != 'B' && j+1 < col) //right
                    legal_moves.push_back(std::make_pair(i, j+1));
                if ( Graph[i][j-1] != 'x' && Graph[i][j-1] != 'A' && Graph[i][j-1] != 'B' && j-1 >= 0) //left
                    legal_moves.push_back(std::make_pair(i, j-1));
                return legal_moves;
            }      
        }
    }
    return legal_moves;
}

char get_opponent_marker(char marker){
	if (marker == 'A') return 'B';
	else return 'A';
}

int curr_state(char marker, int Ap, int Bp){ //the first player(A)
    if (marker == 'A'){
        if (Ap > Bp) return (Bp - Ap)*100;
        else if (Ap == Bp) return -1;
        else return (Bp - Ap)*100; 
    }
    else{ //B
        if (Ap > Bp) return (Ap - Bp)*100; 
        else if (Ap == Bp) return -1;
        else return (Ap - Bp)*100; 
    }
}

int curr_state_last(char marker, int Ap, int Bp){ //the last player(B)

    if (marker == 'B'){ //B is alpha, go wrong -> increase the alpha more
        if (Ap > Bp) return (Bp - Ap)*100;
        else if (Ap == Bp) return -1;
        else return (Bp - Ap)*100; 
    }

    else{ // A is beta, go wrong -> decrease the beta
       if (Ap > Bp) return (Ap - Bp)*100; 
        else if (Ap == Bp) return -1;
        else return (Ap - Bp)*100; 
    }
}

bool valid(int x, int y, int row, int col, char Graph[N][N]){
    return (
        x >= 0 && x < row && y >=0 && y < col &&
        Graph[x][y] != 'x' &&
        Graph[x][y] != 'A' && Graph[x][y] != 'B'
    );
}

int game_state(char Graph[N][N], int row, int col, int Ap, int Bp, char marker){

    int num_of_mushroom = 0;
    int num_of_star= 0;
    int ax ,ay, bx, by;

    for(int i=0; i<row; ++i){
        for(int j=0; j<col; ++j){
            if( Graph[i][j] == 'm' )
                num_of_mushroom++;
            if( Graph[i][j] == 's' )
                num_of_star++;
            if (Graph[i][j] == 'A' ){
                ax = i;
                ay = j;
            }
            if (Graph[i][j] == 'B' ){
                bx = i;
                by = j;
            }
        }
    }

    if (marker == 'A'){
        if(num_of_mushroom == 0 && num_of_star == 0 && Ap<=Bp ) return LOSS; //No more grade
        else if ( Ap + num_of_mushroom <= Bp && num_of_star == 0) return LOSS; //residual mushroom will not win opponents
        else if ( num_of_mushroom == 0 && num_of_star == 0 && Ap > Bp ) return WIN;
        else if ( num_of_star != 0 && (Bp + num_of_mushroom)*2*(num_of_star) < Ap ) return WIN;
        else if ( valid(ax+1, ay, row, col , Graph) == 0 && valid(ax-1, ay, row, col , Graph) == 0 && //cannot move
                  valid(ax, ay+1, row, col , Graph) == 0 && valid(ax, ay-1, row, col , Graph) == 0) return LOSS;
        else return CONTINUE;
    }
    else{
        if(num_of_mushroom == 0 && num_of_star == 0 && Ap>=Bp ) return LOSS; //No more grade
        else if ( Bp + num_of_mushroom <= Ap && num_of_star == 0) return LOSS; //residual mushroom will not win opponents
        else if ( num_of_mushroom == 0 && num_of_star == 0 && Ap < Bp ) return WIN;
        else if ( num_of_star != 0 && (Ap + num_of_mushroom)*2*(num_of_star) < Bp ) return WIN;
        else if ( valid(bx+1, by, row, col , Graph) == 0 && valid(bx-1, by, row, col , Graph) == 0 && //cannot move
                  valid(bx, by+1, row, col , Graph) == 0 && valid(bx, by-1, row, col , Graph) == 0) return LOSS;
        else return CONTINUE;
    }
}

std::pair<int, std::pair<int, int>> minimax_optimization_First(char Graph[N][N], char marker, int depth, int alpha, int beta, int row, int col, int Ap, int Bp){

    // initialization
    std::pair<int, int> best_move = std::make_pair(-1, -1);
	int best_score = (marker == 'A') ? LOSS : WIN;

    // terminated state
    if ( depth == 1000 || game_state(Graph, row, col, Ap, Bp, marker) != CONTINUE ){ 
        best_score = game_state(Graph, row, col, Ap, Bp, marker);
        return std::make_pair(best_score, best_move);
    }

    // Find legal moves
    std::vector<std::pair<int, int>> legal_moves = get_legal_moves(Graph, marker, row, col); //first is A

    if (marker == 'A'){ //A is the first
        for (int i = 0; i < legal_moves.size(); i++){ 

            char tmp; // memorize the previous value

            std::pair<int, int> curr_move = legal_moves[i];
            tmp = Graph[curr_move.first][curr_move.second];
            Graph[curr_move.first][curr_move.second] = marker;

            // opponents's score //A walk to this point and eat it
            int score = minimax_optimization_First(Graph, get_opponent_marker(marker), depth + 1, alpha, beta, row, col, curr_point(tmp, Ap), Bp).first;

            if (best_score < score) //while score > -1000, renew it
			{
                best_score = score + curr_state(marker, Ap, Bp); //if Ap>Bp, then reduce the score
				best_move = curr_move;
				//cout << marker <<": " <<best_move.first <<", " <<best_move.second << " " << best_score << ", "<< curr_state(marker, Ap, Bp) << endl;
				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				alpha = std::max(alpha, best_score); //ini: alpha is -1000
				Graph[curr_move.first][curr_move.second] = tmp; //return the previous value
				if (beta <= alpha) break; //How to Evaluation current graph?
			}
            Graph[curr_move.first][curr_move.second] = tmp;  //return the previous value
        }
    }

    else //opponent
	{
        for (int i = 0; i < legal_moves.size(); i++){ 

            char tmp; // memorize the previous value

            std::pair<int, int> curr_move = legal_moves[i];
            tmp = Graph[curr_move.first][curr_move.second];
            Graph[curr_move.first][curr_move.second] = marker;
       
            int score = minimax_optimization_First(Graph, get_opponent_marker(marker), depth + 1, alpha, beta, row, col, Ap, curr_point(tmp,Bp)).first;

			if (best_score > score)
			{
                best_score =  score + curr_state(marker, Ap, Bp);
                best_move = curr_move;
                //cout << marker<< ": "<<best_move.first <<", " <<best_move.second << " " << best_score << ", "  << curr_state(marker, Ap, Bp) <<endl;
				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				beta = std::min(beta, best_score);
				Graph[curr_move.first][curr_move.second] = tmp;
				if (beta <= alpha) break; 
			}    
            Graph[curr_move.first][curr_move.second] = tmp;     
        }
	}
    return std::make_pair(best_score, best_move);
}

std::pair<int, std::pair<int, int>> minimax_optimization_Last(char Graph[N][N], char marker, int depth, int alpha, int beta, int row, int col, int Ap, int Bp){

    // initialization
    std::pair<int, int> best_move = std::make_pair(-1, -1);
	int best_score = (marker == 'B') ? LOSS : WIN;

    // terminated state
    if (  depth == 1000 || game_state(Graph, row, col, Ap, Bp, marker) != CONTINUE ){ //B, A, B, A, B
        best_score = game_state(Graph, row, col, Ap, Bp, marker);
        return std::make_pair(best_score, best_move);
    }
    // Find legal moves
    std::vector<std::pair<int, int>> legal_moves = get_legal_moves(Graph, marker, row, col); //first is A
    
    if (marker == 'B'){ 

        for (int i = 0; i < legal_moves.size(); i++){ 

            char tmp; // memorize the previous value

            std::pair<int, int> curr_move = legal_moves[i];
            tmp = Graph[curr_move.first][curr_move.second];
            Graph[curr_move.first][curr_move.second] = marker;

            int score = minimax_optimization_Last(Graph, get_opponent_marker(marker), depth + 1, alpha, beta, row, col, Ap, curr_point(tmp,Bp)).first;
			
            if (best_score < score)
			{
                best_score = score + curr_state_last(marker, Ap, Bp);
				best_move = curr_move;
				//cout << marker <<": " <<best_move.first <<", " <<best_move.second << " " << best_score << ", "<< curr_state(marker, Ap, Bp) << endl;
			
				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				alpha = std::max(alpha, best_score); //ini: alpha is -1000
				Graph[curr_move.first][curr_move.second] = tmp;
				if (beta <= alpha) break;
			}
            Graph[curr_move.first][curr_move.second] = tmp;
        }
    }

    else //opponent
	{
        for (int i = 0; i < legal_moves.size(); i++){ 

            char tmp; // memorize the revious value

            std::pair<int, int> curr_move = legal_moves[i];
            tmp = Graph[curr_move.first][curr_move.second];
            Graph[curr_move.first][curr_move.second] = marker;
   
            int score = minimax_optimization_Last(Graph, get_opponent_marker(marker), depth + 1, alpha, beta, row, col, curr_point(tmp, Ap), Bp).first;

			if (best_score > score)
            {
                best_score = score + curr_state(marker, Ap, Bp);
                best_move = curr_move;
            	//cout << marker <<": " <<best_move.first <<", " <<best_move.second << " " << best_score << ", "<< curr_state(marker, Ap, Bp) << endl;
			
				// Check if this branch's best move is worse than the best
				// option of a previously search branch. If it is, skip it
				beta = std::min(beta, best_score);
				Graph[curr_move.first][curr_move.second] = tmp;
				if (beta <= alpha) break; 
			}
            Graph[curr_move.first][curr_move.second] = tmp;
        }
    }
    return std::make_pair(best_score, best_move);
}


int main(void){

        int round, row, col;

        scanf("%d", &round);
        scanf("%d %d", &row, &col);

        char Graph[N][N];
        for(int i=0;i<row;i++){
                for(int j=0; j<col; j++)
                        scanf(" %c", &Graph[i][j]);
        }

        int A, B, ax, ay;
        char me;

        scanf("%d",&A);
        scanf("%d",&B);
        scanf(" %c",&me); //A point and B point

        for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                        if(Graph[i][j] == me){
                                ax = i;
                                ay = j;
                        }
                }
        }

        if (me == 'A'){
            std::pair<int, int> best_move = minimax_optimization_First(Graph, me, 0,LOSS, WIN, row, col, A, B).second;
            if (best_move.first + 1 == ax && best_move.second == ay) cout << "UP" << endl;
            else if (best_move.first - 1 == ax && best_move.second == ay) cout << "DOWN" << endl;
            else if (best_move.first == ax && best_move.second + 1 == ay) cout << "LEFT" << endl;
            else if (best_move.first == ax && best_move.second - 1 == ay) cout << "RIGHT" << endl;
            else{
                if ( Graph[ax+1][ay] != 'x' && Graph[ax+1][ay] != 'A' && Graph[ax+1][ay] != 'B' && ax+1 < row) //dowm
                    cout << "DOWN" << endl;
                else if ( Graph[ax-1][ay] != 'x' && Graph[ax-1][ay] != 'A' && Graph[ax-1][ay] != 'B' && ax-1 >=0 ) //up
                    cout << "UP" << endl;
                else if ( Graph[ax][ay+1] != 'x' && Graph[ax][ay+1] != 'A' && Graph[ax][ay+1] != 'B' && ay+1 < col) //right
                    cout << "RIGHT" << endl;
                else if ( Graph[ax][ay-1] != 'x' && Graph[ax][ay-1] != 'A' && Graph[ax][ay-1] != 'B' && ay-1 >= 0) //left
                    cout << "LEFT" << endl;
            }
        }

        else{ //B
            std::pair<int, int> best_move = minimax_optimization_Last(Graph, me, 0, LOSS, WIN, row, col, A, B).second;
            if (best_move.first + 1 == ax && best_move.second == ay) cout << "UP" << endl;
            else if (best_move.first - 1 == ax && best_move.second == ay) cout << "DOWN" << endl;
            else if (best_move.first == ax && best_move.second + 1 == ay) cout << "LEFT" << endl;
            else if (best_move.first == ax && best_move.second - 1 == ay) cout << "RIGHT" << endl;
            else{
                if ( Graph[ax+1][ay] != 'x' && Graph[ax+1][ay] != 'A' && Graph[ax+1][ay] != 'B' && ax+1 < row) //dowm
                    cout << "DOWN" << endl;
                else if ( Graph[ax-1][ay] != 'x' && Graph[ax-1][ay] != 'A' && Graph[ax-1][ay] != 'B' && ax-1 >=0 ) //up
                    cout << "UP" << endl;
                else if ( Graph[ax][ay+1] != 'x' && Graph[ax][ay+1] != 'A' && Graph[ax][ay+1] != 'B' && ay+1 < col) //right
                    cout << "RIGHT" << endl;
                else if ( Graph[ax][ay-1] != 'x' && Graph[ax][ay-1] != 'A' && Graph[ax][ay-1] != 'B' && ay-1 >= 0) //left
                    cout << "LEFT" << endl;
            }
        }
}
