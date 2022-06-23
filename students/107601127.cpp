#include <iostream>
#include <cstdlib>
using namespace std;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

class Player {
public:
    Player(int round, int width, int height);
    ~Player();
    void init();
    string makeDecision();
    int dfs(int count, int x, int y, int x2, int y2, int hold, int hold2, int value, bool** visited, bool** visited2);
    bool validatePosition(int x, int y);
    pair<int, int> getCurrentPosition();
    int calculateScore(int currentScore, int x, int y, bool reverse);
    char** board;
    int round;
    int width, height;
    int AScore, BScore;
    pair<int, int> ALocation, BLocation;
    char identity;
    int getscore();
    int evaluate(int currentScore, int x, int y, int currentValue, char id);
    pair<int, int> getoppPosition();
    char Makemove(int x, int y, int i, char id);
    void Unmakemove(int x, int y, int i, char id, char pre);
    char oppid();
    int getoppScore();
};

Player::Player(int _round, int _width, int _height) {
    round = _round;
    width = _width;
    height = _height;
}

Player::~Player() {
    for (int i = 0; i < height; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void Player::init() {
    board = new char* [height];
    for (int i = 0; i < height; i++) {
        board[i] = new char[width];
        for (int j = 0; j < width; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'A') ALocation = make_pair(i, j);
            if (board[i][j] == 'B') BLocation = make_pair(i, j);
        }
    }
    cin >> AScore >> BScore >> identity;

}

bool Player::validatePosition(int x, int y) {
    if (x < 0 || x >= height)
        return false;
    else if (y < 0 || y >= width)
        return false;
    else if (board[x][y] == 'A' || board[x][y] == 'B')
        return false;
    else if (board[x][y] == 'x')
        return false;
    return true;
}

pair<int, int> Player::getCurrentPosition() {
    if (identity == 'A')
        return ALocation;
    else if (identity == 'B')
        return BLocation;
}

pair<int, int> Player::getoppPosition() {
    if (identity == 'A')
        return BLocation;
    else if (identity == 'B')
        return ALocation;
}

int Player::calculateScore(int currentScore, int x, int y, bool reverse) {
    char gettingObject = board[x][y];
    switch (gettingObject) {
    case 'm':
    {
        if (reverse) {
            return currentScore - 1;
        }
        else {
            return currentScore + 1;
        }
    }
    case 'n':
    {
        if (reverse) {
            return currentScore + 1;
        }
        else {
            return currentScore - 1;
        }
    }
    case 's':
    {
        if (reverse) {
            return currentScore / 2;
        }
        else {
            return currentScore * 2;
        }
    }

    case 't':
    {
        if (reverse) {
            return currentScore * 2;
        }
        else {
            return currentScore / 2;
        }
        return currentScore / 2;
    }
    case '.':
    case 'b':
    default:
        return currentScore;
    }
}

int Player::evaluate(int currentScore, int x, int y, int currentValue, char id) {
    char gettingObject = board[x][y];
    switch (gettingObject) {
    case 'm':
    {
        if (id == identity) {
            return currentValue + 10;
        }
        else {
            return currentValue - 10;
        }
    }

    case 'n':
    {
        if (id == identity) {
            return currentValue - 10;
        }
        else {
            return currentValue + 10;
        }
    }
    case 's':
    {
        if (id == identity) {
            return currentValue + currentScore * 10;
        }
        else {
            int  v = currentScore / 2;
            return currentValue - currentScore * 10;
        }
    }
    case 't':
    {
        if (id == identity) {
            int  v = currentScore / 2;
            return currentValue - (currentScore - v) * 10;
        }
        else {
            int  v = currentScore / 2;
            return currentValue + (currentScore - v) * 10;
        }
    }
    case '.':
        return currentValue;
    case 'b':
    {
        if (id == identity) {
            return currentValue - 30;
        }
        else {
            return currentValue + 30;
        }
    }
    default:
        return currentValue;
    }
}

int Player::getscore() {
    if (identity == 'A') {
        return AScore;
    }
    else {
        return BScore;
    }
}
char Player::Makemove(int x, int y, int i, char id) {
    board[x][y] = '.';
    int x1 = dx[i] + x;
    int y1 = dy[i] + y;
    char save = board[x1][y1];
    bool reverse = false;
    if (id == 'A') {
        AScore = calculateScore(AScore, x1, y1, reverse);
    }
    else {
        BScore = calculateScore(BScore, x1, y1, reverse);
    }
    board[x1][y1] = id;

    return save;
}

void Player::Unmakemove(int x, int y, int i, char id, char pre) {
    board[x][y] = id;
    int x1 = dx[i] + x;
    int y1 = dy[i] + y;
    board[x1][y1] = pre;
    bool reverse = true;
    if (id == 'A') {
        AScore = calculateScore(AScore, x1, y1, reverse);
    }
    else {
        BScore = calculateScore(BScore, x1, y1, reverse);
    }
}

int Player::dfs(int count, int x, int y, int x2, int y2, int hold, int hold2, int value, bool** visited, bool** visited2) {


    int x1, y1;
    int bestvalue;
    int val;
    if (count == 0) {
        return value;

    }
    if (count % 2 == 0) {
        bestvalue = -20000;
        visited[x][y] = true;
    }
    else {
        bestvalue = 20000;
        visited2[x2][y2] = true;
    }

    for (int i = 0; i < 4; i++) {
        if (count % 2 == 0) {
            x1 = dx[i] + x;
            y1 = dy[i] + y;

            if (validatePosition(x1, y1) && !visited[x1][y1]) {
                visited[x1][y1] = true;
                int v = evaluate(hold, x1, y1, value, identity);
                char move = Makemove(x, y, i, identity);
                val = dfs(count - 1, x1, y1, x2, y2, getscore(), hold2, v, visited, visited2);
                visited[x1][y1] = false;
                Unmakemove(x, y, i, identity, move);
                bestvalue = max(val, bestvalue);

            }
        }
        else {
            x1 = dx[i] + x2;
            y1 = dy[i] + y2;
            if (validatePosition(x1, y1) && !visited2[x1][y1]) {
                visited2[x1][y1] = true;
                int v = evaluate(hold2, x1, y1, value, oppid());
                char move2 = Makemove(x2, y2, i, oppid());
                val = dfs(count - 1, x, y, x1, y1, hold, getoppScore(), v, visited, visited2);
                visited2[x1][y1] = false;
                Unmakemove(x2, y2, i, oppid(), move2);
                bestvalue = min(val, bestvalue);
            }
        }

    }
    return bestvalue;
}
int Player::getoppScore() {
    if (identity == 'A') {
        return BScore;
    }
    else {
        return AScore;
    }
}

char Player::oppid() {
    if (identity == 'A') {
        return 'B';
    }
    else {
        return 'A';
    }
}

string Player::makeDecision() {
    string str[4] = { "RIGHT", "DOWN", "LEFT", "UP" };
    bool** visited = new bool* [height];
    for (int i = 0; i < height; i++) {
        visited[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            visited[i][j] = false;
        }
    }
    bool** visited2 = new bool* [height];
    for (int i = 0; i < height; i++) {
        visited2[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            visited2[i][j] = false;
        }
    }
    pair<int, int> currentPosition = getCurrentPosition();
    pair<int, int> oppPosition = getoppPosition();
    int sc[4];
    int ans = 0;
    int x1, y1, x2, y2;
    int big = -20000;
    x2 = oppPosition.first;
    y2 = oppPosition.second;
    visited[currentPosition.first][currentPosition.second] = true;
    for (int i = 0; i < 4; i++) {
        x1 = dx[i] + currentPosition.first;
        y1 = dy[i] + currentPosition.second;
        if (validatePosition(x1, y1)) {
            visited[x1][y1] = true;
            int v = evaluate(getscore(), x1, y1, 0, identity);
            char move = Makemove(currentPosition.first, currentPosition.second, i, identity);
            sc[i] = dfs(13, x1, y1, x2, y2, getscore(), getoppScore(), v, visited, visited2);
            visited[x1][y1] = false;
            if (sc[i] > big) {
                big = sc[i];
                ans = i;
            }
            Unmakemove(currentPosition.first, currentPosition.second, i, identity, move);

        }

    }
    return str[ans];

}

int main() {
    int round, M, N;
    cin >> round >> M >> N;
    Player player(round, M, N);
    player.init();
    cout << player.makeDecision() << endl;
}


