#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

typedef pair<int, int> PII;

#define F first
#define S second

string Dir1[4] = {"RIGHT", "DOWN", "LEFT", "UP"};
string Dir2[4] = {"RIGHT", "UP", "LEFT", "DOWN"};
string Dir[4];
int M, N;
char MAP[20][20] = {};

double dist( double x1, double y1, double x2, double y2 ){
    double dist = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return dist;
}

bool valid(int x, int y){
        return(
            x >= 0 && x < M && y >=0 && y < N &&
            MAP[x][y] != 'x' &&
            MAP[x][y] != 'A' && MAP[x][y] != 'B'
        );
    }


void pk(int T, int M, int N, char player, int A_score, int B_score){
    PII A_site, B_site, site;
    int score;
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            if(MAP[i][j] == 'A'){
                A_site.F = i;
                A_site.S = j;
            }
            else if(MAP[i][j] == 'B'){
                B_site.F = i;
                B_site.S = j;
            }
        }
    }
    if(player == 'A'){
        site = A_site;
        score = A_score;
    }
    else if(player == 'B'){
        site = B_site;
        score = B_score;
    }
    int dx1[4] = {0, 1, 0, -1};
    int dy1[4] = {1, 0, -1, 0};
    int dx2[4] = {0, -1, 0, 1};
    int dy2[4] = {1, 0, -1, 0};
    int dx[4];
    int dy[4];

    if((T/23) % 2 == 0){
        for(int i = 0 ; i < 4 ; i++){
            Dir[i] = Dir1[i];
            dx[i] = dx1[i];
            dy[i] = dy1[i];
        }
    }else{
        for(int i = 0 ; i < 4 ; i++){
            Dir[i] = Dir2[i];
            dx[i] = dx2[i];
            dy[i] = dy2[i];
        }
    } 

    for(int d = 0 ; d < 4 ; d++){
        int x = site.F + dx[d];
        int y = site.S + dy[d];

        if(!valid(x, y))
            continue;

        if(MAP[x][y] == 'm'){
            cout << Dir[d] << endl;
            return;
        }

        if(score >= 0 && MAP[x][y] == 's'){
            cout << Dir[d] << endl;
            return;
        }

        if(score <= 0 && MAP[x][y] == 't'){
            cout << Dir[d] << endl;
            return;
        }
    }
    
    for(int d = 0 ; d < 4 ; d++){
        int x = site.F + dx[d];
        int y = site.S + dy[d];

        if(!valid(x, y))
            continue;

        if(score <= 0 && (MAP[x][y] == 'n'))
            continue;

        if(score > 0 && MAP[x][y] == 't'){
            continue;
        }

        cout << Dir[d] << endl;
        return;
    }

    cout << Dir[0] << endl;
}

int main(){
    int T, A_score, B_score;
    char player;
    cin >> T >> M >> N;
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            cin >> MAP[i][j];
        }
    }
    cin >> A_score >> B_score >> player;

    pk(T, M, N, player, A_score, B_score);

    return 0;
}