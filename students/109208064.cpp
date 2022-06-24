#include <iostream>
#include <utility>
#include <vector>


using namespace std;

int DIR_Y[4] = { -1, 1, 0, 0 };
int DIR_X[4] = { 0, 0, -1, 1 };

string str_dir(int a);

float get_score(pair<int, int> curr_loc, float curr_score, const vector<vector<char> >& pane);

void dfs(pair<int, int> curr_loc,
    float curr_score,
    int curr_round,
    int first_dir,
    float& opt_score,
    int& opt_round,
    int& opt_dir,
    const vector<vector<char> >& pane,
    vector<vector<bool> >& invalid,
    bool is_first);

void solve(char C,
    pair<int, int> init_loc,
    float init_p,
    int init_round,
    int M, int N,
    const vector<vector<char> >& pane);

int main() {
    int T;
    cin >> T;
    int M, N;
    cin >> M >> N;
    vector<vector<char> > pane(M, vector<char>(N));
    pair<int, int> A_xy, B_xy;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> pane[i][j];
            if (pane[i][j] == 'A') {
                A_xy.first = i;
                A_xy.second = j;
            }
            else if (pane[i][j] == 'B') {
                B_xy.first = i;
                B_xy.second = j;
            }
        }
    }
    float P, Q;
    cin >> P >> Q;
    char C;
    cin >> C;
    pair<int, int> init_loc = (C == 'A') ? A_xy : B_xy;
    float init_p = (C == 'A') ? P : Q;
    solve(C, init_loc, init_p, T, M, N, pane);
}

void solve(char C,
    pair<int, int> init_loc,
    float init_p,
    int init_round,
    int M, int N,
    const vector<vector<char> >& pane) {
    vector<vector<bool> > invalid(M, vector<bool>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            invalid[i][j] = pane[i][j] == 'x' || pane[i][j] == 'A' || pane[i][j] == 'B';
        }
    }
    float opt_score = init_p;
    int opt_round = init_round, opt_dir = -1;
    dfs(init_loc,
        opt_score,
        opt_round,
        opt_dir,
        opt_score,
        opt_round,
        opt_dir,
        pane,
        invalid,
        true);
    if (opt_dir == -1) {
        for (int i = 0; i < 8; ++i) {
            pair<int, int> next_loc = init_loc;
            next_loc.first += DIR_Y[i];
            next_loc.second += DIR_X[i];
            // check valid
            if (next_loc.first >= pane.size() || next_loc.first < 0) continue;
            if (next_loc.second >= pane.back().size() || next_loc.first < 0) continue;
            if (invalid[next_loc.first][next_loc.second]) continue;
            cout << str_dir(i) << endl;
            break;
        }
    }
    else {
        cout << str_dir(opt_dir) << endl;
    }
}

void dfs(pair<int, int> curr_loc,
    float curr_score,
    int curr_round,
    int first_dir,
    float& opt_score,
    int& opt_round,
    int& opt_dir,
    const vector<vector<char> >& pane,
    vector<vector<bool> >& invalid,
    bool is_first) {
    if (curr_round + 1 > 1000) {
        return; // game over
    }
    // UP -> DOWN -> LEFT -> RIGHT
    for (int i = 0; i < 4; ++i) {
        if (is_first) first_dir = i;
        pair<int, int> next_loc = curr_loc;
        next_loc.first += DIR_Y[i];
        next_loc.second += DIR_X[i];
        // check valid
        if (next_loc.first >= pane.size() || next_loc.first < 0) continue;
        if (next_loc.second >= pane.back().size() || next_loc.first < 0) continue;
        if (invalid[next_loc.first][next_loc.second]) continue;
        //        // greater than 10 is useless
        //        if (curr_round > opt_round && curr_round - opt_round > 10) continue;
        if (pane[next_loc.first][next_loc.second] == 'b') {
            dfs(next_loc,
                curr_score,
                curr_round + 3,
                first_dir,
                opt_score,
                opt_round,
                opt_dir,
                pane,
                invalid,
                false);
            continue;
        }
        // mark as visited
        invalid[next_loc.first][next_loc.second] = true;
        // dfs
        float candi_score = get_score(next_loc, curr_score, pane);
        int candi_round = curr_round + 1;
        //        cout << "x: " << next_loc.first << " y: " << next_loc.second << endl
        //             << "candi_score:" << candi_score << endl
        //             << "candi_round:" << candi_round << endl
        //             << "first dir:" << str_dir(first_dir) << endl
        //             << "now dir:" << str_dir(i) << endl;
        if (candi_score > opt_score || (candi_score == opt_score && candi_round < opt_round)) {
            opt_score = candi_score;
            opt_round = candi_round;
            opt_dir = first_dir;
        }
        //        cout << "opt_score:" << opt_score << endl
        //             << "opt_round:" << opt_round << endl << endl;
        dfs(next_loc,
            candi_score,
            candi_round,
            first_dir,
            opt_score,
            opt_round,
            opt_dir,
            pane,
            invalid,
            false);
        // unmark
        invalid[next_loc.first][next_loc.second] = false;
    }

}

float get_score(pair<int, int> curr_loc, float curr_score, const vector<vector<char> >& pane) {
    if (pane[curr_loc.first][curr_loc.second] == 'm') {
        return curr_score += 1;
    }
    if (pane[curr_loc.first][curr_loc.second] == 'n') {
        return curr_score -= 1;
    }
    if (pane[curr_loc.first][curr_loc.second] == 's') {
        return curr_score *= 2;
    }
    if (pane[curr_loc.first][curr_loc.second] == 't') {
        return curr_score /= 2;
    }
    else {
        return curr_score;
    }
}

string str_dir(int a) {
    if (a == 0) {
        return "UP";
    }
    else if (a == 1) {
        return "DOWN";
    }
    else if (a == 2) {
        return "LEFT";
    }
    else if (a == 3) {
        return "RIGHT";
    }
}