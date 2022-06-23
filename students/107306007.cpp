#include <iostream>
#include <map>
#include <queue>
#include <limits.h>
using namespace std;

enum Direction { UP,
                 LEFT,
                 RIGHT,
                 DOWN };

string defaultOutput(Direction dir) {
    switch (dir) {
        case UP:
            return "UP";
        case DOWN:
            return "DOWN";
        case LEFT:
            return "LEFT";
        case RIGHT:
            return "RIGHT";
    }
    return "FALSE";
}

class Position {
   public:
    Position(int _score, Direction _direction, pair<int, int> _position, int _distance) {
        score = _score;
        direction = _direction;
        position = _position;
        distance = _distance;
    }
    void print() {
        cout << "==========" << endl;
        cout << "score: " << score << endl;
        cout << "direction: " << defaultOutput(direction) << endl;
        cout << "position: (" << position.first << ", " << position.second << ")" << endl;
        cout << "distance: " << distance << endl;
    }
    int score;
    Direction direction;
    pair<int, int> position;
    int distance;
};

class Timer {
   private:
    clock_t start_time;
    clock_t stop_time;

   public:
    void startTimer() {
        start_time = clock();
    }
    void stopTimer() {
        stop_time = clock();
    }
    double getTime() {
        return (double(stop_time) - double(start_time)) / CLOCKS_PER_SEC;
    }
};

class Random {
   public:
    int generateRandom(int from, int to) {
        int range = to - from + 1;
        return (rand() % range) + from;
    }
    void setRandom() {
        srand(time(NULL));
    }
};

class BOT : public Timer, public Random {
   public:
    BOT(int round, int width, int height);
    ~BOT();
    void init();
    string makeDecision();

   private:
    bool validatePosition(int x, int y);
    bool validateDirection(int x, int y, string type);
    pair<int, int> getCurrentPosition();
    pair<int, int> getOpponentPosition();
    int calculateScore(int currentScore, int x, int y);
    Position validateDeadend (int x, int y, int distance);
    Position initValidateDeadend (int x, int y);
    int initAttack(int x, int y);
    char** board;
    bool** visited;
    int round;
    int width, height;
    int AScore, BScore;
    pair<int, int> ALocation, BLocation;
    char identity;
};

BOT::BOT(int _round, int _width, int _height) {
    round = _round;
    width = _width;
    height = _height;
}

BOT::~BOT() {
    for (int i = 0; i < height; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void BOT::init() {
    board = new char*[height];
    for (int i = 0; i < height; i++) {
        board[i] = new char[width];
        for (int j = 0; j < width; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'A') ALocation = make_pair(j, i);
            if (board[i][j] == 'B') BLocation = make_pair(j, i);
        }
    }
    cin >> AScore >> BScore >> identity;
}

pair<int, int> BOT::getCurrentPosition() {
    if (identity == 'A')
        return ALocation;
    else if (identity == 'B')
        return BLocation;
    return make_pair(-1, -1);
}

pair<int, int> BOT::getOpponentPosition() {
    if (identity == 'A')
        return BLocation;
    else if (identity == 'B')
        return ALocation;
    return make_pair(-1, -1);
}

bool BOT::validatePosition(int x, int y) {
    if (x < 0 || x >= width)
        return false;
    else if (y < 0 || y >= height)
        return false;
    else if (board[y][x] == 'A' || board[y][x] == 'B')
        return false;
    else if (board[y][x] == 'x')
        return false;
    return true;
}

bool BOT::validateDirection(int x, int y, string type) {
    if (x < 0 || x >= width)
        return false;
    else if (y < 0 || y >= height)
        return false;
    else if (board[y][x] == 'x')
        return false;
    else if (identity == 'A'){
        if (type == "self"){
            if (board[y][x] == 'B')
                return false;  
        }
        else if (type == "opponent"){
            if (board[y][x] == 'A')
                return false;              
        }
    }
    else if (identity == 'B'){
        if (type == "self"){
            if (board[y][x] == 'A')
                return false;  
        }
        else if (type == "opponent"){
            if (board[y][x] == 'B')
                return false;              
        }         
    }
    return true;
}

int BOT::calculateScore(int currentScore, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return -1;
    char gettingObject = board[y][x];
    if (identity == 'A'){
        switch (gettingObject) {
            case 'm':
                return currentScore + 1;
            case 'n':
                return currentScore - 1;
            case 's':
                return currentScore * 2.5;
            case 't':
                return currentScore / 2;
            case '.':
            case 'b':
                return currentScore - 2;
            case 'B':
                return currentScore ;
            default:
                return currentScore;
        } 
    }else {
        switch (gettingObject) {
            case 'm':
                return currentScore + 1;
            case 'n':
                return currentScore - 1;
            case 's':
                return currentScore * 2.5;
            case 't':
                return currentScore / 2;
            case '.':
            case 'b':
                return currentScore - 2;
            case 'A':
                return currentScore ;
            default:
                return currentScore;        
        }
    }
}

Position BOT::initValidateDeadend (int x, int y){
    bool** visited = new bool*[height]; // init visited
    for (int i = 0; i < height; i++) {
        visited[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
        }
    }
    visited[x][y] = true;
    Direction currentDirection;
    int validDirectionCount = 0;
    int dead = -1;

    queue<Position> q;
    pair<int, int> currentPosition = make_pair(x, y);
    pair<int, int> opponentPosition = getOpponentPosition();
    Position initPsitions[4] = { // generate position for next 4 directions
        Position(0, LEFT, make_pair(currentPosition.first - 1, currentPosition.second), 1),
        Position(0, RIGHT, make_pair(currentPosition.first + 1, currentPosition.second), 1),
        Position(0, UP, make_pair(currentPosition.first, currentPosition.second - 1), 1),
        Position(0, DOWN, make_pair(currentPosition.first, currentPosition.second + 1), 1)};
    map<int, int> refrenceOrder; // key, value pair
    setRandom();
    for (int i = 0; i < 4; i++) {
        refrenceOrder[generateRandom(0, INT32_MAX)] = i; // generate 4 random num
    }
    for (const auto& s : refrenceOrder) {
        int i = s.second; // get value
        if (validateDirection(initPsitions[i].position.first, initPsitions[i].position.second, "self") && !visited[initPsitions[i].position.second][initPsitions[i].position.first]) {
            // Tp prevent illegal steps.
                validDirectionCount++;
                currentDirection = initPsitions[i].direction;
                q.push(initPsitions[i]);
        } else {
            initPsitions[i].score = -1;
        }          
    }

    bool flag1 = false;
    bool flag2 = false;   
    if (validDirectionCount >= 3)
        return Position(dead, LEFT, currentPosition, 1);
    if (validDirectionCount == 1){
        for(auto& s: initPsitions){
            if(s.position == opponentPosition){
                dead = -2;
                flag2 = true;
            }
        }
        if (dead != -2)
            dead = -3;
    }
    refrenceOrder.clear();
    visited[currentPosition.second][currentPosition.first] = true;
    while (!q.empty()) {
        queue<Position> tmpq;
        while (!q.empty()) {
            Position tmp = q.front();
            Position tmpInitPsitions[4] = {
                Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first - 1), tmp.direction, make_pair(tmp.position.first - 1, tmp.position.second), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first + 1), tmp.direction, make_pair(tmp.position.first + 1, tmp.position.second), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second - 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second - 1), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second + 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second + 1),tmp.distance+1)};
            setRandom();
            for (int i = 0; i < 4; i++) {
                refrenceOrder[generateRandom(0, INT32_MAX)] = i;
            }
            validDirectionCount = 0;
            for (const auto& s : refrenceOrder) {
                int i = s.second;
                // tmpInitPsitions[i].print();
                if (validateDirection(tmpInitPsitions[i].position.first, tmpInitPsitions[i].position.second, "self") && !visited[tmp.position.second][tmp.position.first]) {
                    validDirectionCount++;  
                    if(tmp.distance < 10){
                        tmpq.push(tmpInitPsitions[i]);
                    }
                }              
            }
            // cout << "validDirectionCount: " << validDirectionCount << endl;
            if (validDirectionCount >= 3){
                return Position(dead, tmp.direction, tmp.position, tmp.distance+1);
                visited[tmp.position.second][tmp.position.first] = true;
            }
            if (validDirectionCount == 1){              
                for(auto& s: tmpInitPsitions){
                    // s.print(); 
                    if(s.position == opponentPosition){
                        dead = -2;
                        flag2 = true;
                    }
                }
                if (dead != -2){
                    dead = -3;
                }
                              
            }              
            visited[tmp.position.second][tmp.position.first] = true;
            q.pop();
            refrenceOrder.clear();
        }
        q = tmpq;
    }
    delete[] visited;
}

int BOT::initAttack(int x, int y) {
    bool** visited = new bool*[height]; // init visited
    for (int i = 0; i < height; i++) {
        visited[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
        }
    }

    Direction currentDirection;

    queue<Position> q;
    pair<int, int> currentPosition = getOpponentPosition();
    Position initPsitions[4] = { // generate position for next 4 directions
        Position(0, LEFT, make_pair(currentPosition.first - 1, currentPosition.second), 1),
        Position(0, RIGHT, make_pair(currentPosition.first + 1, currentPosition.second), 1),
        Position(0, UP, make_pair(currentPosition.first, currentPosition.second - 1), 1),
        Position(0, DOWN, make_pair(currentPosition.first, currentPosition.second + 1), 1)};
    map<int, int> refrenceOrder; // key, value pair
    setRandom();
    for (int i = 0; i < 4; i++) {
        refrenceOrder[generateRandom(0, INT32_MAX)] = i; // generate 4 random num
    }
    for (const auto& s : refrenceOrder) {
        int i = s.second; // get value
        if (validateDirection(initPsitions[i].position.first, initPsitions[i].position.second, "self")) {
            if (initPsitions[i].position.first == x && initPsitions[i].position.second == y)
                    return initPsitions[i].distance;
            // Tp prevent illegal steps.
                currentDirection = initPsitions[i].direction;
                q.push(initPsitions[i]);
        } else {
            initPsitions[i].score = -1;
        }
    }
    refrenceOrder.clear();
    visited[currentPosition.second][currentPosition.first] = true;
    while (!q.empty()) {
        queue<Position> tmpq;
        while (!q.empty()) {
            Position tmp = q.front();
            Position tmpInitPsitions[4] = {
                Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first - 1), tmp.direction, make_pair(tmp.position.first - 1, tmp.position.second), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first + 1), tmp.direction, make_pair(tmp.position.first + 1, tmp.position.second), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second - 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second - 1), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second + 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second + 1),tmp.distance+1)};
            setRandom();
            for (int i = 0; i < 4; i++) {
                refrenceOrder[generateRandom(0, INT32_MAX)] = i;
            }
            for (const auto& s : refrenceOrder) {
                int i = s.second;
                // tmpInitPsitions[i].print();
                if (validateDirection(tmpInitPsitions[i].position.first, tmpInitPsitions[i].position.second, "self") && !visited[tmp.position.second][tmp.position.first]) {
                    if (tmpInitPsitions[i].position.first == x && tmpInitPsitions[i].position.second == y) {
                        return tmpInitPsitions[i].distance;
                        // tmpInitPsitions[i].print();
                    }
                    if(tmp.distance < 12){
                        tmpq.push(tmpInitPsitions[i]);
                    }
                }
            }
            visited[tmp.position.second][tmp.position.first] = true;
            q.pop();
            refrenceOrder.clear();
        }
        q = tmpq;
    }
    delete[] visited;
    return INT_MAX;
}

string BOT::makeDecision() {
    int depth;
    if (round < 200)
        depth = 6;
    else if (round > 600)
        depth = 12; 

    bool** visited = new bool*[height]; // init visited
    for (int i = 0; i < height; i++) {
        visited[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
        }
    }

    int currentMaxScore = 0;
    Direction currentDirection;
    Direction backupDirection;

    queue<Position> q;
    pair<int, int> currentPosition = getCurrentPosition();
    pair<int, int> opponentPosition = getOpponentPosition();
    Position backupPosition = Position(0, LEFT, currentPosition, 0);
    Position initPsitions[4] = { // generate position for next 4 directions
        Position(0, LEFT, make_pair(currentPosition.first - 1, currentPosition.second), 0),
        Position(0, RIGHT, make_pair(currentPosition.first + 1, currentPosition.second), 0),
        Position(0, UP, make_pair(currentPosition.first, currentPosition.second - 1), 0),
        Position(0, DOWN, make_pair(currentPosition.first, currentPosition.second + 1), 0)};
    map<int, int> refrenceOrder; // key, value pair
    setRandom();
    for (int i = 0; i < 4; i++) {
        refrenceOrder[generateRandom(0, INT32_MAX)] = i; // generate 4 random num
    }
    int distance_to_opponent = INT_MAX;
    Position escape = Position(0, LEFT, make_pair(currentPosition.first, currentPosition.second), 0);
    int attack;
    for (const auto& s : refrenceOrder) {
        int i = s.second; // get value
        if (validatePosition(initPsitions[i].position.first, initPsitions[i].position.second)) {
            escape = initValidateDeadend(initPsitions[i].position.first, initPsitions[i].position.second);
            attack = initAttack(escape.position.first, escape.position.second);
            // initPsitions[i].print();
            // cout << "escape: " << escape.distance << ", x: " << escape.position.first << ", y:" << escape.position.second << ", score: " << escape.score << ", attack: " << attack << endl;
            // Tp prevent illegal steps.
            if (escape.distance <= attack || escape.score == -2){
                currentDirection = initPsitions[i].direction;
                q.push(initPsitions[i]);
            } else if (escape.score == -1){
                backupDirection = initPsitions[i].direction;
                backupPosition = initPsitions[i];               
            } else {
                initPsitions[i].score = -1;
            }
        }
    }
    refrenceOrder.clear();
    visited[currentPosition.second][currentPosition.first] = true;
    if (q.empty()){
        currentDirection = backupDirection;
        q.push(backupPosition);
    }
    while (!q.empty()) {
        if (getTime() > 0.9) break;
        queue<Position> tmpq;
        while (!q.empty()) {
            if (getTime() > 0.9) break;
            Position tmp = q.front();
            Position tmpInitPsitions[4] = {
                Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first - 1), tmp.direction, make_pair(tmp.position.first - 1, tmp.position.second), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first + 1), tmp.direction, make_pair(tmp.position.first + 1, tmp.position.second), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second - 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second - 1), tmp.distance+1),
                Position(calculateScore(tmp.score, tmp.position.second + 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second + 1),tmp.distance+1)};
            setRandom();
            for (int i = 0; i < 4; i++) {
                refrenceOrder[generateRandom(0, INT32_MAX)] = i;
            }
            for (const auto& s : refrenceOrder) {
                int i = s.second;
                // tmpInitPsitions[i].print();
                if (validatePosition(tmpInitPsitions[i].position.first, tmpInitPsitions[i].position.second)) {
                    if (tmpInitPsitions[i].score > currentMaxScore) {
                        currentMaxScore = tmpInitPsitions[i].score;
                        currentDirection = tmpInitPsitions[i].direction;
                        // tmpInitPsitions[i].print();
                    }
                    if(tmp.distance < depth){
                        tmpq.push(tmpInitPsitions[i]);
                    }
                }
            }
            visited[tmp.position.second][tmp.position.first] = true;
            q.pop();
            refrenceOrder.clear();
        }
        q = tmpq;
    }
    delete[] visited;
    return defaultOutput(currentDirection);
}

int main(void) {
    int round, M, N;
    cin >> round >> M >> N;
    BOT bot(round, N, M);
    bot.startTimer();
    bot.init();
    cout << bot.makeDecision() << endl;
    bot.stopTimer();
    // cout << bot.getTime() << endl;
}