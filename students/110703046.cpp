#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

int Round, M, N;
char grid[20][20]={};

int steps[4][2] = {
        {0,1},
        {1,0},
        {-1,0},
        {0,-1}
};

struct cell{
        int dir;
        int pts;
        int i;
        int j;
        int count;
};

struct cell cache[20][20] = {};
queue<struct cell> que;

bool valid(int x, int y){
        return (
                        x >= 0 && x < M && y >=0 && y < N &&
                        grid[x][y] != 'x' &&
                        grid[x][y] != 'A' && grid[x][y] != 'B'
                   );
}

int countScore(int curr, int i, int j) {
        char now = grid[i][j];
        if(now == 'm')
                return curr + 1;
        else if(now == 's')
                return curr * 2;
        else if(now == 'n')
                return curr - 1;
        else if(now == 't')
                return curr / 2;
        else
                return curr;
}

string next_dir(int ci, int cj, int point) {
        struct cell u, d, l, r;
        u.i = ci + steps[2][0], u.j = cj + steps[2][1], u.dir = 2, u.count = 1;
        d.i = ci + steps[1][0], d.j = cj+ steps[1][1], d.dir = 1, d.count = 1;
        l.i = ci + steps[3][0], l.j = cj + steps[3][1], l.dir = 3, l.count = 1;
        r.i = ci + steps[0][0], r.j = cj + steps[0][1], r.dir = 0, r.count = 1;
        if (valid(l.i, l.j)) {
                l.pts = countScore(point, l.i, l.j);
                que.push(l);
        }
        if (valid(r.i, r.j)) {
                r.pts = countScore(point, r.i, r.j);
                que.push(r);
        }
        if (valid(u.i, u.j)) {
                u.pts = countScore(point, u.i, u.j);
                que.push(u);
        }
        if (valid(d.i, d.j)) {
                d.pts = countScore(point, d.i, d.j);
                que.push(d);
        }
        while(!que.empty()){
                struct cell deq = que.front();
                que.pop();
                if(cache[deq.i][deq.j].pts < deq.pts)
                        cache[deq.i][deq.j] = deq;
                if(deq.count < 6) {
                        for(int i = 0; i < 4; i++){
                                int next_i =  deq.i+steps[i][0];
                                int next_j = deq.j+steps[i][1];
                                if(valid(next_i, next_j)) {
                                        struct cell next;
                                        next.dir = deq.dir;
                                        next.count = deq.count+1;
                                        next.i = next_i;
                                        next.j = next_j;
                                        next.pts = countScore(deq.pts, next_i, next_j);
                                        que.push(next);
                                }
                        }
                }
        }
        int max = INT_MIN;
        int max_dir;
        for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                        if(cache[i][j].pts > max){
                                max = cache[i][j].pts;
                                max_dir = cache[i][j].dir;
                        }
                }
        }
        if(max_dir == 0)
                return "RIGHT";
        else if(max_dir == 1)
                return "DOWN";
        else if(max_dir == 2)
                return "UP";
        else if(max_dir == 3)
                return "LEFT";
}


int main(void){
        int A, B;
        char me;
        int ai, aj, bi, bj;
        cin >> Round >> M >> N;
        for(int i=0;i<M;i++)
                for(int j=0;j<N;j++) {
                        cin >> grid[i][j];
                        if(grid[i][j] == 'A')
                                ai = i, aj = j;
                        else if(grid[i][j] == 'B')
                                bi = i, bj = j;
                }

        cin >> A >> B >> me;
        if(me == 'A')
                cout << next_dir(ai, aj, A) << endl;
        else
                cout << next_dir(bi, bj, B) << endl;
}