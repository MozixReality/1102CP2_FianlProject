
#include <bits/stdc++.h>
using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};
const int ddr[4] = {-2, 2, 0, 0};
const int ddc[4] = {0, 0, -2, 2};

void endFunction(int i){
        if(i == 0){
                cout << "UP" << endl;
        }
        if(i == 1){
                cout << "DOWN" << endl;
        }
        if(i == 2){
                cout << "LEFT" << endl;
        }
        if(i == 3){
                cout << "RIGHT" << endl;
        }
}

int main(){
        int T;
        cin >> T;
        int M, N;
        cin >> M >> N;
        char map[M][N];
        int Ax, Ay, Bx, By, x, y;
        for(int i = 0; i < M; ++i){
                for(int j = 0; j < N; ++j){
                        cin >> map[i][j];
                        if(map[i][j] == 'A'){
                                Ax = i;
                                Ay = j;
                        }
                        if(map[i][j] == 'B'){
                                Bx = i;
                                By = j;
                        }
                }
        }
        int scoreA, scoreB;
        cin >> scoreA >> scoreB;
        char player, opponent;
        cin >> player;
        if(player == 'A'){
                x = Ax;
                y = Ay;
                opponent = 'B';
        }
        else{
                x = Bx;
                y = By;
                opponent = 'A';
        }

        int analysis[7][4];
        for(int i = 0; i <= 3; ++i){
                for(int j = 0; j < 4; ++j){
                        analysis[i][j] = -1;
                }
        }
        for(int i = 4; i <= 6; ++i){
                for(int j = 0; j < 4; ++j){
                        analysis[i][j] = 0;
                }
        }
        int nx, ny;
        for (int i = 0; i < 4; ++i) {
                nx = x + dr[i];
                ny = y + dc[i];
                if(nx >= M || nx < 0 || ny >=M || ny < 0 ||
                                map[nx][ny] == opponent || map[nx][ny] == 'x'){
                        analysis[0][i] = 0;
                }
                else{
                        analysis[0][i] = 1;
                }
                if(map[nx][ny] == 'm' || map[nx][ny] == 's'){
                        analysis[1][i] = 1;
                }
                if(map[nx][ny] == 't' || map[nx][ny] == 'n' || map[nx][ny] == 'b'){
                        analysis[2][i] = 1;
                }
                nx = x + ddr[i];
                ny = y + ddc[i];
                if(map[nx][ny] == 's' || map[nx][ny] == 'm'){
                        analysis[3][i] = 1;
                }
        }
        for(int i = x-3; i <= x-1; ++i){
                for(int j = y-3; j <= y+3; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's' || map[i][j] =='m'){

                                        analysis[4][0] ++;
                                }
                        }
                }
        }
        for(int i = x+1; i <= x+3; ++i){
                for(int j = y-3; j <= y+3; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's' || map[i][j] =='m'){
                                        analysis[4][1] ++;
                                }
                        }
                }
        }
        for(int i = x-3; i <= x+3; ++i){
                for(int j = y-3; j <= y-1; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's' || map[i][j] =='m'){
                                        analysis[4][2] ++;
                                }
                        }
                }
        }
        for(int i = x-3; i <= x+3; ++i){
                for(int j = y+1; j <= y+3; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's' || map[i][j] =='m'){
                                        analysis[4][3] ++;
                                }
                        }
                }
        }

        for(int i = 0; i <= x-1; ++i){
                for(int j = 0; j < M; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's'){
                                        analysis[5][0] ++;
                                }
                                if(map[i][j] =='m'){
                                        analysis[6][0] ++;
                                }
                        }
                }
        }
        for(int i = x+1; i < M; ++i){
                for(int j = 0; j < M; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's'){
                                        analysis[5][1] ++;
                                }
                                if(map[i][j] =='m'){
                                        analysis[6][1] ++;
                                }
                        }
                }
        }
        for(int i = 0; i < M; ++i){
                for(int j = 0; j <= y-1; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's'){
                                        analysis[5][2] ++;
                                }
                                if(map[i][j] =='m'){
                                        analysis[6][2] ++;
                                }
                        }
                }
        }
        for(int i = 0; i < M; ++i){
                for(int j = y+1; j < M; ++j){
                        if(i >= M || i < 0 || j >=M || j < 0){
                                continue;
                        }
                        else{
                                if(map[i][j] == 's'){
                                        analysis[5][3] ++;
                                }
                                if(map[i][j] =='m'){
                                        analysis[6][3] ++;
                                }
                        }
                }
        }
        //1:
        for(int i = 0; i < 4; ++i){
                if(analysis[0][i] == 1){
                        if(analysis[1][i] == 1){
                                endFunction(i);
                                return 0;
                        }
                }
        }
        //2:
        bool worst_case = true;
        for(int i = 0; i < 4; ++i){
                nx = x + dr[i];
                ny = y + dc[i];
                if(analysis[0][i] == 1){
                        if(map[nx][ny] == 'm' || map[nx][ny] == 's'
                                        || map[nx][ny] == '.'){
                                worst_case = false;
                        }
                }
        }
        if(worst_case){
                for(int i = 0; i < 4; ++i){
                        nx = x + dr[i];
                        ny = y + dc[i];
                        if(analysis[0][i] == 1){
                                if(map[nx][ny] == 'b'){
                                        endFunction(i);
                                        return 0;
                                }
                        }
                }
        }
        if(worst_case){
                for(int i = 0; i < 4; ++i){
                        nx = x + dr[i];
                        ny = y + dc[i];
                        if(analysis[0][i] == 1){
                                if(map[nx][ny] == 'n'){
                                        endFunction(i);
                                        return 0;
                                }
                        }
                }
        }
        /*if(worst_case){
                for(int i = 0; i < 4; ++i){
                        nx = x + dr[i];
                        ny = y + dc[i];
                        if(analysis[0][i] == 1){
                                if(map[nx][ny] == 't'){
                                        endFunction(i);
                                        return 0;
                                }
                        }
                }
        }*/
        //3:
        for(int i = 0; i < 4; ++i){
                nx = x + dr[i];
                ny = y + dc[i];
                if(analysis[0][i] == 1 && analysis[3][i] == 1
                                && map[nx][ny] != 't'){
                        endFunction(i);
                        return 0;
                }
        }
        //4:
        int max = 0;
        int choose = -1;
        for(int i = 0; i < 4; ++i){
                nx = x + dr[i];
        ny = y + dc[i];
                if(analysis[0][i] == 1 && map[nx][ny]!='t'){
                        if(analysis[4][i] > max){
                                max = analysis[4][i];
                                choose = i;
                        }
                }
        }
        if(max!=0){
                endFunction(choose);
                return 0;
        }
        //5:
        max = 0;
        choose = -1;
        for(int i = 0; i < 4; ++i){
 nx = x + dr[i]; ny = y + dc[i];
                if(analysis[0][i] == 1 && map[nx][ny]!='t' ){
                        if(analysis[5][i] > max){
                                max = analysis[5][i];
                                choose = i;
                        }
                }
        }
        if(max!=0){
                endFunction(choose);
                return 0;
        }
        //6:
        max = 0;
        choose = -1;
        for(int i = 0; i < 4; ++i){
                nx = x + dr[i]; ny = y + dc[i];
                if(analysis[0][i] == 1 && map[nx][ny]!= 't'){
                        if(analysis[6][i] > max){
                                max = analysis[6][i];
                                choose = i;
                        }
                }
        }
        if(max!=0){
                endFunction(choose);
                return 0;
        }

        for(int i = 0; i < 4; ++i){
                if(analysis[0][i] == 1 && analysis[2][i] != 1){
                        endFunction(i);
                        return 0;
                }
        }
        for(int i = 0; i < 4; ++i){
                nx = x + dr[i];
                ny = y + dc[i];
                if(analysis[0][i] == 1 && map[nx][ny] != 't'){
                        endFunction(i);
                        return 0;
                }
        }
        for(int i = 0; i < 4; ++i){
                if(analysis[0][i] == 1){
                        endFunction(i);
                        return 0;
                }
        }
}

