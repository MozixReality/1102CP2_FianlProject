#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <map>
#include <climits>

using namespace std;

#define pii pair <int, int>
#define integer_min -2147483648

typedef struct Position{
    int i;
    int j;
    string dir;
    int score;
}Position;


bool valid(int i, int j, int n, char **table){
    if(i < 0 || i >= n)
        return false;
    else if(j < 0 || j >= n)
        return false;
    else if(table[i][j] == 'A' || 
            table[i][j] == 'B'  )
        return false;
    else if(table[i][j] == 'x')
        return false;
    else 
        return  true;
}

pii get_cur(char** table, int N, int M, char role){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(table[i][j] == role)
                return make_pair(i, j);
        }
    }
    return make_pair(-1, -1);
}

int cal_score(int i, int j, int score, char** table){
    if(table[i][j] == 'm')
        return score + 1;
    else if(table[i][j] == 'n')
        return score - 1;
    else if(table[i][j] == 's')
        return score * 2;
    else if(table[i][j] == 't')
        return score / 2;
    else if(table[i][j] == 'b')
        return score;
    else if(table[i][j] == '.')
        return score;
    return -1;
} 

int most_possible_score(char** table, bool** visited, int si, int sj, int score, int n){
    int di[4]      = {0, 1, 0, -1}, 
        dj[4]      = {1, 0, -1, 0}, 
        max_score  = integer_min,
        depth      = 5;
    
    queue <Position> q;
    Position cur = {si, sj, "NULL", score};
    visited[si][sj] = true;
    q.push(cur);
    while(!q.empty() && depth--){
        Position temp = q.front();
        q.pop();
        visited[temp.i][temp.j] = true;
        for(int k=0; k<4; k++){
            if(valid(temp.i+di[k], temp.j+dj[k], n, table) && !visited[temp.i+di[k]][temp.j+dj[k]]){
                int temp_score = cal_score(temp.i+di[k], temp.j+dj[k], temp.score, table);
                if(temp_score > max_score){
                    max_score = temp_score;
                }
                q.push({temp.i+di[k], temp.j+dj[k], "NULL", temp_score});
                visited[temp.i+di[k]][temp.j+dj[k]] = true;
            }
        }
    }
    return max_score;
}

string auto_move(char** table, int n, int m, char role, int a_score, int b_score, int round){
    queue <Position> q;
    int di[4]         = {0, 1, 0, -1}, 
        dj[4]         = {1, 0, -1, 0};
    string move[4]    = {"RIGHT", "DOWN", "LEFT", "UP"};
    string next_dir;
    pii current_pos   = get_cur(table, n, m, role);
    int current_score = (role == 'A') ? a_score : b_score;
    srand(round + current_pos.first + current_pos.second + time(NULL));

    bool **visited = new bool*[n];
    for(int i=0; i<n; i++){
        visited[i] = new bool[m];
        for(int j=0; j<m; j++){
            visited[i][j] = false;
        }
    }

    Position adj_pos[4] = { {current_pos.first+di[0], current_pos.second+dj[0],  move[0]},
                            {current_pos.first+di[1], current_pos.second+dj[1],  move[1]},
                            {current_pos.first+di[2], current_pos.second+dj[2],  move[2]},
                            {current_pos.first+di[3], current_pos.second+dj[3],  move[3]}};
    map<int, int> ref;
    for(int i=0; i<4; i++){
        ref[rand()] = i;
    }

    for(auto &s: ref){
        int k = s.second;
        if(valid(adj_pos[k].i, adj_pos[k].j, n, table)){
            q.push(adj_pos[k]);
        }
        else{
            adj_pos[k].score = INT_MIN;
        }
    }
    Position max = q.front();
    max.score    = cal_score(max.i, max.j, current_score, table);
    next_dir     = max.dir;
    q.pop();
    while(!q.empty()){
        Position temp = q.front();
        temp.score = cal_score(temp.i, temp.j, current_score, table);
        q.pop();
        if(most_possible_score(table, visited, max.i, max.j, max.score, n) <
           most_possible_score(table, visited, temp.i, temp.j, temp.score, n)){
                next_dir = temp.dir;
        }
        else if(max.score < temp.score){
            next_dir = temp.dir;
        }
        else{
            next_dir = max.dir;
        }
    }
    return next_dir;
}


int main(){
    int round, M, N, a_score, b_score;
    char role;
    cin >> round >> M >> N;
    char **table = new char*[M];
    for(int i=0; i<M; i++){
        table[i] = new char[N];
        for(int j=0; j<N; j++){
            cin >> table[i][j];
        }
    }
    cin >> a_score >> b_score >> role;
    cout << auto_move(table, N, M, role, a_score, b_score, round) << endl;
    for(int i=0; i<N; i++)
        delete[] table[i];
    delete[] table;
    return 0;
}

