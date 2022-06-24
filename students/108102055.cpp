#include <iostream>
#include <cstdlib>
#include <utility>
#include <string>
#include <queue>
#include <map>

using namespace std;

typedef pair<int, int> PII;

#define BIG_NUMBER 99999

enum Direction{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Step{

    public:
        PII Pos;
        Direction OriDir;
};

int Round, M, N, myPoint;
bool visit[20][20] = {};
char Graph[20][20] = {};
queue<Step> q, nextQ;
map < Direction, float > DirPointMap;

bool isBadSituation = false;

string defaultOutput(Direction dir){
    
    switch (dir){

    case UP:
        return "UP";
    case DOWN:
        return "DOWN";
    case LEFT:
        return "LEFT";
    case RIGHT:
        return "RIGHT";
    default:
        break;
    }
    return "FALSE";
}

float getNewPoint(float point, char c){
   
    bool isInf = false;

    if (point == -BIG_NUMBER){
        point = myPoint;
        isInf = true;
    }

    switch (c){
    case 'm':
        return point + 1;
    case 'n':
        return point - 1;
    case 's':
        return point * 2;
    case 't':
        return point * 0.5f;
    case 'b':
        return point - 0.1f;
    default:
        if (isInf){
            return -BIG_NUMBER;
        }
        return point;
    }
}

void resetVisit(){

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            visit[i][j] = false;
        }
    }
}

pair<float, Direction> getResult(){
    
    Direction win1, win2;
    if (DirPointMap[UP] > DirPointMap[DOWN]){
        win1 = UP;
    }
    else{
        win1 = DOWN;
    }
    if (DirPointMap[LEFT] > DirPointMap[RIGHT]){
        win2 = LEFT;
    }
    else{
        win2 = RIGHT;
    }
    if (DirPointMap[win2] > DirPointMap[win1]){
        return make_pair(DirPointMap[win2], win2);
    }
    else{
        return make_pair(DirPointMap[win1], win1);
    }
}

bool inRange(int x, int y){
    return (x >= 0 && x < M && y >= 0 && y < N);
}

bool isFineSpot(int x, int y){
    return inRange(x,y) && (Graph[x][y] == 'm' || Graph[x][y] == 's');
}

bool valid(int x, int y){

    bool pass = Graph[x][y] != 'x' && Graph[x][y] != 'A' && Graph[x][y] != 'B';

    if (!isBadSituation){
        pass &= Graph[x][y] != 'n' && Graph[x][y] != 't' && Graph[x][y] != 'b';
    }

    return (inRange(x, y) &&  pass && !visit[x][y]);
}

void add2Q(Step out, int _x, int _y, queue<Step> *_q){
    
    int x = out.Pos.first + _x;
    int y = out.Pos.second + _y;

    if (valid(x, y)){
        Step newStep;
        newStep.OriDir = out.OriDir;
        newStep.Pos.first = x;
        newStep.Pos.second = y;
        _q -> push(newStep);
    }

    if (inRange(x,y) && !visit[x][y]){
        visit[x][y] = true;
    }
}

void oneStep(){

    Step step = q.front();
    PII pos = step.Pos;
    int x = pos.first;
    int y = pos.second;

    int nowPoint = DirPointMap[step.OriDir];
    int newPoint = getNewPoint(nowPoint, Graph[x][y]);
    if (newPoint > nowPoint){
        DirPointMap[step.OriDir] = newPoint;
    }

    add2Q(step, 1, 0, &nextQ);
    add2Q(step, -1, 0, &nextQ);
    add2Q(step, 0, -1, &nextQ);
    add2Q(step, 0, 1, &nextQ);
    q.pop();
}

void swap(queue<Step> *a, queue<Step> *b){
    
    queue<Step> temp = *a;
    *a = *b;
    *b = temp;
}

void initialize(PII pos){
    
    resetVisit();
    Step newStep1;
    newStep1.Pos = pos;
    newStep1.OriDir = RIGHT;
    DirPointMap[RIGHT] = -BIG_NUMBER;
    add2Q(newStep1, 1, 0, &q);

    Step newStep2;
    newStep2.Pos = pos;
    newStep2.OriDir = DOWN;
    DirPointMap[DOWN] = -BIG_NUMBER;
    add2Q(newStep2, 0, 1, &q);

    Step newStep3;
    newStep3.OriDir = LEFT;
    DirPointMap[LEFT] = -BIG_NUMBER;
    newStep3.Pos = pos;
    add2Q(newStep3, -1, 0, &q);

    Step newStep4;
    newStep4.OriDir = UP;
    DirPointMap[UP] = -BIG_NUMBER;
    newStep4.Pos = pos;
    add2Q(newStep4, 0, -1, &q);
}

Direction findWhateverWay(PII pos){
    
    int x = pos.first;
    int y = pos.second;

    if (inRange(x, y - 1) && Graph[x][y - 1] == '.'){
        return UP;
    }
    if (inRange(x, y + 1) && Graph[x][y + 1] == '.'){
        return DOWN;
    }
    if (inRange(x + 1, y) && Graph[x + 1][y] == '.'){
        return RIGHT;
    }
    if (inRange(x - 1, y) && Graph[x - 1][y] == '.'){
        return LEFT;
    }
    return NONE;
}

bool hasFineSpot()
{
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            if (isFineSpot(i,j)){
                return true;
            }
        }
    }
    return false;
}

Direction MakeDecision(PII myPos){
    
    initialize(myPos);

    visit[myPos.first][myPos.second] = true;

    while (true){
        while (!q.empty()){
            oneStep();
        }

        pair<float, Direction> result = getResult();

        if (result.first > 0){
            return result.second;
        }

        if (nextQ.empty()){
            if (result.first != -BIG_NUMBER){
                return result.second;
            }
            else{
                if (!isBadSituation && hasFineSpot()){
                    isBadSituation = true;
                    initialize(myPos);
                }
                else{
                    return findWhateverWay(myPos);
                }
            }
        }

        swap(&q, &nextQ);
    }
}

int main(void){
    
    int A, B;
    PII aPos, bPos, myPos;
    char me;
    cin >> Round >> M >> N;

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            visit[i][j] = false;
        }
    }

    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            
            char input;
            cin >> input;
            if (input == 'A'){
                aPos = make_pair(j, i);
            }
            else if (input == 'B'){
                bPos = make_pair(j, i);
            }
            Graph[j][i] = input;
        }
    }

    cin >> A >> B >> me;

    if (me == 'A'){
        myPoint = A;
        myPos = aPos;
    }
    if (me == 'B'){
        myPoint = B;
        myPos = bPos;
    }

    string result = defaultOutput(MakeDecision(myPos));

    cout << result << endl;
}