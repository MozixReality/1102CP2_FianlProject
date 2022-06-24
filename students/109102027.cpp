#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

typedef struct Step{
    int y;
    int x;                 // coordinates
    int score;             // score cummulated so far
    string command;        // the first step
    int distance;          // the distance travelled in the unit of steps
}step;

class TIME{
    private:
        clock_t start;
        clock_t end;
    public:
        void enable(){
            start = clock();
        }
        double fetchTime(){
            end = clock();
            return ((double)end - (double)start)/CLOCKS_PER_SEC;
        }
};

class GRAPH : public TIME{
    public:
        GRAPH(int round, int M, int N);
        void buildgraph();
        string move();

    private:
        int round, M, N;
        char graph[20][20];
        int scoreA, scoreB;
        char me, match;
        pair<int, int> positionA, positionB;

        bool valid(int y, int x);
        pair<int, int> getPosition(char me);
        int getScore(char me);
        int calculateScore(int original, int y, int x);
};

GRAPH::GRAPH(int r, int m, int n){
    round = r;
    M = m;
    N = n;
};

void GRAPH::buildgraph(){
    for(int i=0; i<M; ++i){
        for(int j=0; j<N; ++j){
            cin >> graph[i][j];
            if(graph[i][j] == 'A') positionA = make_pair(i, j);
            if(graph[i][j] == 'B') positionB = make_pair(i, j);
        }
    }
    cin >> scoreA >> scoreB >> me;
    if(me == 'A') match = 'B';
    if(me == 'B') match = 'A';
}

bool GRAPH::valid(int y, int x){
    return (
        y >= 0 && y < M && x >=0 && x < N 
        && graph[y][x] != 'x' && graph[y][x] != 'A' && graph[y][x] != 'B'
    );
}

pair<int, int> GRAPH::getPosition(char me){
    if(me == 'A') return positionA;
    if(me == 'B') return positionB;
    return make_pair(-1, -1);
}

int GRAPH::getScore(char me){
    if(me == 'A') return scoreA;
    if(me == 'B') return scoreB;
    return -1;
}

int GRAPH::calculateScore(int original, int y, int x){
    if(graph[y][x] == 'm') return original + 1;
    if(graph[y][x] == 'n') return original - 1;
    if(graph[y][x] == 's') return original * 2;
    if(graph[y][x] == 't') return original / 2;
    return original;
}

string GRAPH::move(){

    int access[20][20];
    for(int i=0; i<20; ++i){
        for(int j=0; j<20; ++j){
            access[i][j] = 0;
        }
    }

    // to record the distance from every accessible spot to the match
    int distance2match[20][20];
    for(int i=0; i<20; ++i){
        for(int j=0; j<20; ++j){
            distance2match[i][j] = INT16_MAX;
        }
    }
    queue<step> qmatch;
    step initial = {getPosition(match).first, getPosition(match).second, 0, "insignificant", 0};
    qmatch.push(initial);
    int dy[4] = {-1, 1, 0, 0};
    int dx[4] = {0, 0, -1, 1};
    while(!qmatch.empty() && fetchTime() < 0.3){           // cease if execution time exceeds 0.3 sec
        for(int i=0; i<4; ++i){
            step tmp = {qmatch.front().y, qmatch.front().x, 0, "inisgnificant", qmatch.front().distance + 1};
            if(valid(tmp.y, tmp.x) && access[tmp.y][tmp.x] == 0){
                if(graph[tmp.y][tmp.x] == 'b') tmp.distance += 3;
                if(tmp.distance < distance2match[tmp.y][tmp.x]) distance2match[tmp.y][tmp.x] = tmp.distance;
                qmatch.push(tmp);
                access[tmp.y][tmp.x] = -1;                 // mark as inaccessible
            }
        }
        qmatch.pop();
    }

    for(int i=0; i<20; ++i){
        for(int j=0; j<20; ++j){
            access[i][j] = 0;
        }
    }

    queue<step> BFS;
    pair<int, int> myPosition = getPosition(me);
    string directions[4] = {"UP", "DOWN", "LEFT", "RIGHT"};

    // starting from the 4 directions of the initial position
    for(int i=0; i<4; ++i){
        step tmp = {myPosition.first + dy[i], myPosition.second + dx[i], getScore(me), directions[i], 1};
        if(valid(tmp.y, tmp.x)){
            if(graph[tmp.y][tmp.x] == 'b') tmp.distance += 3; 
            tmp.score = calculateScore(tmp.score, tmp.y, tmp.x);        // renew the score
            access[tmp.y][tmp.x] = -1;
            BFS.push(tmp);
        }
    }

    string firstStep = BFS.front().command;          // valid output guaranteed
    int hightest=-INT16_MAX;

    while(!BFS.empty() && fetchTime()<0.8){          // cease if execution time exceeds 0.8 sec

        // save the highest score along the way
        if(BFS.front().score > hightest){
            hightest = BFS.front().score;
            firstStep = BFS.front().command;
        }

        // expand in the 4 directions
        for(int i=0; i<4; ++i){
            step tmp = {BFS.front().y + dy[i], BFS.front().x + dx[i], BFS.front().score, BFS.front().command, BFS.front().distance + 1};    // inherit the score of the previous step
            if(valid(tmp.y, tmp.x) && access[tmp.y][tmp.x] == 0 && tmp.distance < distance2match[tmp.y][tmp.x]){
                if(graph[tmp.y][tmp.x] == 'b') tmp.distance += 3; 
                tmp.score = calculateScore(tmp.score, tmp.y, tmp.x);
                access[tmp.y][tmp.x] = -1;
                BFS.push(tmp);
            }
        }
        BFS.pop();
    }
    return firstStep;
}

int main(void){
    
    int round, M, N;
    cin >> round >> M >> N;
    GRAPH fight(round, M, N);
    fight.enable();
    fight.buildgraph();
    cout << fight.move() << endl;
    // cout << fight.fetchTime() << endl;
    return 0;
}