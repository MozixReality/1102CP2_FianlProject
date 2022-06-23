#include <iostream>
#include <queue>

using namespace std;

class player
{
    public:

        player(int _row, int _col);
        ~player();

        bool validMove(int row, int col);
        int setScore(int row, int col, int curScore);
        string move();


    private:

        int rowNum;
        int colNum;

        struct Maze
        {
            char sign;
            bool check;
        };
        
        Maze **maze;
        int AScore, BScore;
        char me;

        int meScore;
        int ARow, ACol, BRow, BCol;
        int meRow, meCol;

        string direction[4];
};


player::player(int _row, int _col) : rowNum(_row), colNum(_col)
{
    maze = new Maze*[rowNum];

    for (int i = 0 ; i < rowNum ; ++i)
    {
        maze[i] = new Maze[colNum];

        for (int j = 0 ; j < colNum ; ++j)
        {
            cin >> maze[i][j].sign;
            maze[i][j].check = false;

            if (maze[i][j].sign == 'A') {ARow = i; ACol = j;}
            else if (maze[i][j].sign == 'B') {BRow = i; BCol = j;}
        }
    }

    cin >> AScore >> BScore >> me;

    if (me == 'A') {meRow = ARow; meCol = ACol; meScore = AScore;}
    else if (me == 'B') {meRow = BRow; meCol = BCol; meScore = BScore;}

    direction[0] = "UP";
    direction[1] = "DOWN";
    direction[2] = "LEFT";
    direction[3] = "RIGHT";
}


player::~player()
{
    for (int i = 0 ; i < rowNum ; ++i)
        delete [] maze[i];
    
    delete [] maze;
}


bool
player::validMove(int row, int col)
{
    if (row < 0 || row >= rowNum || col < 0 || col >= colNum || maze[row][col].sign == 'x' \
       || maze[row][col].sign == 'A' || maze[row][col].sign == 'B')
       return false;
    
    return true;
}


int
player::setScore(int row, int col, int curScore)
{
    switch (maze[row][col].sign)
    {
        case 'm':
            return curScore+1;
        
        case 'n':
            return curScore-1;
        
        case 's':
            return curScore*2;
        
        case 't':
            return curScore/2;
        
        default:
            break;
    }

    return curScore;
}


string
player::move()
{
    int dirRow[4] = {-1,1,0,0};
    int dirCol[4] = {0,0,-1,1};

    struct bfsNode
    {
        int row, col, count, score;
        string dir;
        bfsNode(int _r, int _c, int _meScore) : row(_r), col(_c), count(0), score(_meScore), dir("") {}
        bfsNode(int _r, int _c, int _count, int _score, string _dir) : row(_r), col(_c), count(_count), score(_score), dir(_dir) {}
    };

    queue <bfsNode> bfsQ;

    bfsNode tmp(meRow, meCol, meScore);

    bfsQ.push(tmp);

    bool iniFourDir = false;

    int maxScore = meScore;
    string maxDir;
    string randDir;

    while (!bfsQ.empty())
    {
        if (bfsQ.front().score > maxScore)
        {
            maxScore = bfsQ.front().score;
            maxDir = bfsQ.front().dir;
        }
        
        for (int d = 0 ; d < 4 ; ++d)
        {
            int newRow = bfsQ.front().row + dirRow[d];
            int newCol = bfsQ.front().col + dirCol[d];

            if (validMove(newRow, newCol) && !maze[newRow][newCol].check && bfsQ.front().count < 7)
            {   

                if (!iniFourDir)
                {
                    bfsNode tmp2(newRow, newCol, bfsQ.front().count+1, setScore(newRow, newCol, bfsQ.front().score), direction[d]);
                    bfsQ.push(tmp2);
                    randDir = direction[d];
                }

                else
                {
                    bfsNode tmp2(newRow, newCol, bfsQ.front().count+1, setScore(newRow, newCol, bfsQ.front().score), bfsQ.front().dir);
                    bfsQ.push(tmp2);
                }

                maze[newRow][newCol].check = true;

            }
        }

        bfsQ.pop();

        if (!iniFourDir)
            iniFourDir = true;
    }

    if (maxDir != "")
        return maxDir;
    
    return randDir;
}



int main()
{

    int round, m, n;

    cin >> round >> m >> n;

    player player(m,n);

    cout << player.move() << endl;

    return 0;
}