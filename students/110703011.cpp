#include <bits/stdc++.h>
using namespace std;
#define DBG
#undef DBG
#define T
#undef T


int deadroad[20][20] = {};

int m,n,turn;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};


bool is_bump(const vector<vector<char> >& board){

        for(int i = 0;i < m;++i){
                for(int j = 0;j < n;++j)
                        if(board[i][j] == 'b')
                                return 1;
        }
        return false;
}

int setable(const vector<vector<char> >& table, int row, int col, int c_row, int c_col){
        int dis[20][20] = {};
        queue<pair<int, int> > que;
        que.push(make_pair(c_row,c_col));
        while(!que.empty()){
                int size = que.size();
                while(size--){
                        for(int k = 0;k < 4;++k){
                                int i_tmp = que.front().first + dy[k];
                                int j_tmp = que.front().second + dx[k];
                                if(i_tmp < 0 || i_tmp >= m || j_tmp < 0 || j_tmp >= n)
                                        continue;
                                else if(table[i_tmp][j_tmp] == 'x' || table[i_tmp][j_tmp] == 'b')
                                        dis[i_tmp][j_tmp] = -1;
                                else if(dis[i_tmp][j_tmp] == 0){
                                        dis[i_tmp][j_tmp] = dis[que.front().first][que.front().second] + 1;
                                        que.push(make_pair(i_tmp,j_tmp));
                                }

                        }
                        que.pop();
                }
        }
#ifdef DBG
        ofstream fout;
        fout.open("./cfile.txt", ios_base::app);
        for(int i = 0;i < m;++i){
                for(int j = 0;j < n;++j){
                        fout << dis[i][j] << " ";
                }
                fout << endl;
        }
        fout << endl;
        fout.close();
#endif
        return dis[row][col];
}
int bfs(const vector<vector<char> >& board, int row, int col, int c_row, int c_col,int point){
#ifdef DBG
        ofstream fout;
        fout.open("./afile.txt", ios_base::app);
        fout << m << " " << n << endl;
#endif


        vector<vector<int> > point_table(m, vector<int>(n, 0));
        vector<vector<int> > path(m, vector<int>(n, 0));
        vector<vector<int> > step_table(m, vector<int>(n, 0));



        queue<pair<int, int> > que;
        queue<pair<int, int> > dir_que;




        const int step = abs(row - c_row) + abs(col - c_col);
        char goal,avoid;
        if(step % 2 == 1){
                goal = 'b';
                avoid = board[c_row][c_col];
        }
        else{
                goal = board[c_row][c_col];
                avoid = 'b';
        }


        point_table[row][col] = point;
        step_table[row][col] = 1;

        que.push(make_pair(row,col));
        dir_que.push(make_pair(row,col));
        int time = 0,size;
        while(!que.empty()){
                size = que.size();

                while(size--){

                        pair<int,int> tmp = que.front();
                        int i = tmp.first;
                        int j = tmp.second;
                        int     point = point_table[dir_que.front().first][dir_que.front().second];

                        for(int k = 0;k < 4;++k){
                                int row_tmp = i + dy[k];
                                int col_tmp = j + dx[k];
                                if(row_tmp < 0 || row_tmp >= m || col_tmp < 0 || col_tmp >= n){
                                        continue;
                                }
                                else if(board[row_tmp][col_tmp] == 'x'){
                                        step_table[row_tmp][col_tmp] = -2;
                                }
                                else if(step_table[row_tmp][col_tmp] == 0 || step_table[row_tmp][col_tmp] == step_table[i][j] + 1){
                                        step_table[row_tmp][col_tmp] = step_table[i][j] + 1;
                                        que.push(make_pair(row_tmp,col_tmp));
                                        dir_que.push(make_pair(i , j));
                                }
                                else{
                                        continue;
                                }
                        }

                        if(board[i][j] == 'm')
                                point += 1;
                        else if(board[i][j] == 'n')
                                point -= 1;
                        else if(board[i][j] == 's')
                                point *= 2;
                        else if(board[i][j] == 't')
                                point /= 2;
                        else if(board[i][j] == goal)
                                point += 256;
                        else if(board[i][j] == avoid)
                                point -= 128;

                        if(dir_que.front().first == row && dir_que.front().second == col){
#ifdef DBG
                                fout << i << " " << j << " " << dir_que.front().first << " " << dir_que.front().second << endl;
#endif
                                for(int k = 0;k < 4;++k){
                                        if(i == dir_que.front().first + dy[k] && j == dir_que.front().second + dx[k])
                                                path[i][j] = k;
                                }
                                if(point >= point_table[i][j])
                                        point_table[i][j] = point;
                        }
                        else if(point >= point_table[i][j]){
                                point_table[i][j] = point;
                                path[i][j] = path[dir_que.front().first][dir_que.front().second];
                        }


                        que.pop();
                        dir_que.pop();



                }

#ifdef DBG
                for(int i = 0;i < m;++i){
                        for(int j = 0;j < n;++j)
                                fout << step_table[i][j] << " ";
                        fout << endl;
                }
                fout << endl;
                fout << que.size() << " "<< dir_que.size() << endl;
                for(int i = 0;i < m;++i){
                        for(int j = 0;j < n;++j)
                                fout << point_table[i][j] << " ";
                        fout << endl;
                }
                fout << endl;
                for(int i = 0;i < m;++i){
                        for(int j = 0;j < n;++j)
                                fout << path[i][j] << " ";
                        fout << endl;
                }
                fout << endl;
#endif

        }
#ifdef DBG
        fout << "out que" << endl;
#endif
        pair<int,int> ans;
        ans.first = 0;
        ans.second = 0;
        for(int i = 0;i < m;++i){
                for(int j = 0;j < n;++j){
                        if(point_table[i][j] > point_table[ans.first][ans.second]){
                                ans.first = i, ans.second = j;
                        }
                        else if(point_table[i][j] == point_table[ans.first][ans.second]){
                                if(step_table[i][j] < step_table[ans.first][ans.second]){
                                        ans.first = i, ans.second = j;
                                }
                        }
                }
        }

#ifdef DBG
        fout << path[ans.first][ans.second] << endl;
        fout.close();
#endif
        return path[ans.first][ans.second];
}

void dead(const vector<vector<char> >& board){
        int deadline[20][20] = {};
        int time[20][20] = {};
        for(int i = 0;i < m ;++i){
                for(int j = 0;j < n;++j){
                        if(board[i][j] == 'x'){
                                deadline[i][j] = -1;
                                continue;
                        }
                        for(int k = 0;k < 4;++k){
                                int i_tmp = i + dy[k];
                                int j_tmp = j + dx[k];
                                if(i_tmp >= m || i_tmp < 0 || j_tmp >= n || j_tmp < 0 || board[i_tmp][j_tmp] == 'x')
                                        ++deadline[i][j];
                        }
                }
        }
        queue<pair<int,int> > que;
        for(int i = 0;i < m ;++i){
                for(int j = 0;j < n;++j){
                        if(deadline[i][j] == 3){
                                ++deadroad[i][j];
                                que.push(make_pair(i,j));
                                while(!que.empty()){
                                        for(int k = 0;k < 4;++k){
                                                int i_tmp = que.front().first + dy[k];
                                                int j_tmp = que.front().second + dx[k];
                                                if(i_tmp < m && i_tmp >= 0 && j_tmp < n && j_tmp >= 0 && deadline[i_tmp][j_tmp] == 2 && deadroad[i_tmp][j_tmp] == 0){
                                                        deadroad[i_tmp][j_tmp] = deadroad[que.front().first][que.front().second] + 1;
                                                        que.push(make_pair(i_tmp,j_tmp));
                                                }
                                        }
                                        ++time[i][j];
                                        que.pop();
                                }
                        }
                }
        }
        for(int i = 0;i < m ;++i){
                for(int j = 0;j < n;++j){
                        if(deadline[i][j] == 3){
                                ++time[i][j];
                                deadroad[i][j] -= time[i][j];
                                que.push(make_pair(i,j));
                                while(!que.empty()){
                                        for(int k = 0;k < 4;++k){
                                                int i_tmp = que.front().first + dy[k];
                                                int j_tmp = que.front().second + dx[k];
                                                if(i_tmp < m && i_tmp >= 0 && j_tmp < n && j_tmp >= 0 && deadline[i_tmp][j_tmp] == 2 && deadroad[i_tmp][j_tmp] != 0){
                                                        deadline[i_tmp][j_tmp] = -2;
                                                        deadroad[i_tmp][j_tmp] -= time[i][j];
                                                        que.push(make_pair(i_tmp,j_tmp));
                                                }
                                        }
                                        que.pop();
                                }
                        }
                }
        }
        for(int i = 0;i < m ;++i){
                for(int j = 0;j < n;++j){
                        deadroad[i][j] *= -1;
                }
        }
}

void judge(double up, double down, double left, double right,int point_player,int point_opp){
        string msg[] = {"UP", "DOWN", "LEFT", "RIGHT"};
        vector<string> ans;
        if(up >= down && up >= left && up >= right)
                ans.push_back(msg[0]);
        if(down >= up && down >= left && down >= right)
                ans.push_back(msg[1]);
        if(left >= up && left >= down && left >= right)
                ans.push_back(msg[2]);
        if(right >= up && right >= down && right >= left)
                ans.push_back(msg[3]);
        int r = 0;
        if(point_opp > point_player){
                r = turn % ans.size();
        }
        cout << ans[r] << endl;
        return;
}


double dfs(vector<vector<char> > board, int depth, int row,int col, int step, double point, char opp, int status,int mine){
        if(depth > step)
                return point;

        int time = 0, condition = 0;


        char tem = board[row][col];
        board[row][col] = '.';

        double point_tem = point;


        if(board[row][col] == 'b')
                ++mine;

        if(row > 0 && board[row-1][col] != 'x'){
                ++time;
                point = dfs(board, depth + 1, row - 1, col, step, point_tem, opp, status, mine);
        }
        if(row < board.size() - 1 && board[row+1][col] != 'x'){
                ++time;
                point = max(point,dfs(board, depth + 1, row + 1, col, step, point_tem, opp, status, mine));
        }
        if(col > 0 && board[row][col - 1] !='x'){
                ++time;
                point = max(point, dfs(board, depth + 1, row, col - 1, step, point_tem,opp, status, mine));
        }
        if(col < board[0].size() - 1 && board[row][col+1] != 'x'){
                ++time;
                point = max(point, dfs(board, depth + 1, row, col + 1, step, point_tem,opp, status, mine));
        }

        board[row][col] = tem;


        double mul = pow(0.8 , (double)depth);
        if(board[row][col] == 'm')
                point += 1 * mul;
        else if(board[row][col] == 'n')
                point -= 1 * mul;
        else if(board[row][col] == 's')
                point += point * mul;
        else if(board[row][col] == 't')
                point -= (point / 2) * mul;
        else if(board[row][col] == opp && depth % 2 == 0 && time <= 2 && status == 0 && mine == 0){    // didn't consider time situation
                point += 1024 * mul;
                condition = 1;
        }
        else if(board[row][col] == opp && depth % 2 == 1)
                condition = -1;
        else if(board[row][col] == 'b'){
                if(condition == 0)
                        point -=  1 * mul;
                else if(condition == 1)
                        point -= 512 * mul ;
                else if(condition == -1)
                        point += 512 * mul;
                else
                        cout << "here is a bug" << endl;
        }


        return point;



}




int main(void){
#ifdef DBG
        auto start_clock = clock();
        double average;
        ofstream fout;
        fout.open("./myfile.txt", ios_base::app);
#endif
        scanf("%d\n",&turn);
        scanf("%d %d\n",&m,&n);
        char tem;
        vector<vector<char> > board(m, vector<char>(n) );
        for(int i = 0;i < m;++i){
                for(int j = 0;j < n;++j){
                        if(j != n - 1)
                                scanf("%c ",&tem);
                        else
                                scanf("%c",&tem);
                        board[i][j] = tem;
                }
                scanf("\n");
        }
        int pointA,pointB;
        char stand;
        double point;
        scanf("%d\n%d\n%c",&pointA, &pointB, &stand);
        //fout << stand << endl;


        int A_row,A_col, B_row, B_col;

#ifdef DBG
        //debug for map


        for(int i = 0;i < m;++i){
                for(int j = 0;j < n;++j)
                        fout << board[i][j] << " ";
                fout << endl;
        }
#endif


        dead(board);

        for(int i = 0;i < m;++i){
                for(int j = 0;j < n;++j){
                        if(board[i][j] == 'A'){
                                A_row = i;
                                A_col = j;
                        }
                        else if(board[i][j] == 'B'){
                                B_row = i;
                                B_col = j;
                        }
                }
        }

        int step = abs(A_row - B_row) + abs(A_col - B_col) ;
        int col,row;
        int c_col, c_row;
        char opp;
        int point_player, point_opp;
        if(stand == 'A'){
                col = A_col;
                row = A_row;
                c_col = B_col;
                c_row = B_row;
                opp = 'B';
                point_player = pointA;
                point_opp = pointB;
        }
        else{
                col = B_col;
                row = B_row;
                c_col = A_col;
                c_row = A_row;
                opp = 'A';
                point_player = pointB;
                point_opp = pointA;
        }



        int step2 = min(8, 10001 - turn);


        double right,left,up,down;
        double direction[4] = {};
        double direction2[4] = {};

        int row_tmp, col_tmp;
        for(int i = 0;i < 4;++i){
                row_tmp = row + dy[i];
                col_tmp = col + dx[i];
                if(row_tmp < 0 || row_tmp >= m || col_tmp < 0 || col_tmp >= n || board[row_tmp][col_tmp] == 'x' || board[row_tmp][col_tmp] == opp)
                        direction[i] = -8192;
                else{
                        direction[i] = dfs(board, 1, row_tmp , col_tmp, step2, (double)point_player, opp, 0, 0);
                        direction2[i] = direction[i];
                        char tmp = board[row_tmp][col_tmp];
                        board[row][col] = '.';
                        board[row_tmp][col_tmp] = stand;
                        double point_opp_tmp = dfs(board, 0, c_row, c_col, step2 - 1, (double)point_opp, stand, 1, 0);

#ifdef DBG
                        //fout << direction[i] << "  " << point_opp_tmp << endl;
#endif
                        direction[i] -= point_opp_tmp;
                        board[row][col] = stand;
                        board[row_tmp][col_tmp] = tmp;
                }
        }

        //int middle = m / 2;
        //if(turn > (m*m) / 2 && point_player > point_opp && step % 2 == 1){
        //if(row > middle)
        //direction[0] += (double)(point_player - point_opp) / 2;
        //else if(row < middle)
        //direction[1] += (double)(point_player - point_opp) / 2;
        //if(col > middle)
        //direction[2] += (double)(point_player - point_opp) / 2;
        //else if(col < middle)
        //direction[3] += (double)(point_player - point_opp) / 2;

        //}

        if(((is_bump(board) && step % 2 == 1) || step % 2 == 0) && turn > 400 && point_player < point_opp){
#ifdef DBG
                fout << "enter bfs" << endl;
#endif
                int dir_tmp = bfs(board, row, col, c_row, c_col,point_player);
                direction[dir_tmp] += 1024;
        }

        int step3 = setable(board,row,col,c_row,c_col);
#ifdef DBG
        fout << row << " " << col << " " << c_row << " " << c_col << endl;
        fout << "step3: " << step3 << "step:" << step <<  endl;
#endif

        for(int k = 0;k < 4;++k){
                row_tmp = row + dy[k];
                col_tmp = col + dx[k];
                if(row_tmp >= 0 && row_tmp < m && col_tmp > 0 && col_tmp){
                        if(deadroad[row_tmp][col_tmp] != 0 && step3 % 2 == 1 && step3 <= (deadroad[row_tmp][col_tmp] * 2) - 1){
                                direction[k] -= 2048;


#ifdef DBG
                                fout << "judge avoid deadroad" << endl;
                                for(int i = 0;i < m;++i){
                                        for(int j = 0;j < n;++j)
                                                fout << deadroad[i][j] << " ";
                                        fout << endl;
                                }
                                fout << endl;
                                fout << deadroad[row_tmp][col_tmp] << " " << step << " " << (deadroad[row_tmp][col_tmp] * 2) - 1 << endl;
#endif
                        }
                }
        }

        judge(direction[0], direction[1], direction[2], direction[3],point_player, point_opp);

#ifdef DBG
        average = (clock() - start_clock) * 1.0 / CLOCKS_PER_SEC;

        if (fout.is_open()){
                fout << point_player << "  "<< point_opp << endl;
                fout << direction[0] << " " << direction[1] << " " << direction[2] << " "  << direction[3]  << " " << endl;
                fout << average << endl;
        }
        fout.close();
#endif
        return 0;
}