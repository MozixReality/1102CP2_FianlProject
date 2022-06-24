#include <iostream>
#include <climits>
#include <map>
#include <queue>


//#define uP 0
//#define dOWN 1
//#define lEFT 2
//#define rIGHT 3
#define F first
#define S second
#define mkp make_pair

using namespace std;

pair<int, int> _up = make_pair<int, int>(-1, 0 );
pair<int, int> _dowm = make_pair<int, int>(1,  0);
pair<int, int> _left = make_pair<int, int>(0, -1);
pair<int, int> _right = make_pair<int, int>(0, 1);
int M, N;
string defaultOutput[4] = { "UP",
							"DOWN",
							"LEFT",
							"RIGHT"};

class BOT{
	public:
		BOT(int round, int width, int height);
		~BOT();
		void init();
		char board[20][20];
		string makeDecision();
		int condition = 0;
		pair<int, int> ALocation, BLocation;
		int AScore, BScore;
		char identity;
		pair<int, int> getCurrentPosition();
	private:
		bool validatePosition(int x, int y);
		int calculateScore(int currentScore, int x, int y);
		int round;
		int width, height;
};
BOT::BOT(int _round, int _width, int _height) {
	round = _round;
	width = _width;
	height = _height;
}
BOT::~BOT() {
	//for (int i = 0; i < height; i++) {
	//delete[] player.board[i];
	//}
	//delete[] player.board;
}
void BOT::init() {
	//player.board = new char*[width];
	for (int i = 0; i < height; i++) {
		//player.board[i] = new char[height];
		for (int j = 0; j < width; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'A') ALocation = make_pair(i, j);
			if (board[i][j] == 'B') BLocation = make_pair(i, j);
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
int getNewScore(int currentScore, char targetObject){
	switch (targetObject) {
		case 'm':
			return currentScore + 1;
		case 'n':
			return currentScore - 1;
		case 's':
			return currentScore * 2;
		case 't':
			return currentScore / 2;
		case '.':
		case 'b':
		default:
			return currentScore;
	}
}

bool canmove(BOT player){
	if(player.condition == 0)
		return true;
	else
		return false;
}
bool validMove(const BOT player, const int x, const int y) {
	if (x < 0 || x >= M)
		return false;
	else if (y < 0 || y >= N)
		return false;
	else if (player.board[x][y] == 'A' && player.identity == 'B')
		return false;
	else if (player.board[x][y] == 'B' && player.identity == 'A')
		return false;
	else if (player.board[x][y] == 'x')
		return false;
	return true;
}
int DFS(int score, BOT player, pair<int, int> now, pair<int, int> next_Dir, int depth){
	if(!validMove(player, now.first + next_Dir.first, now.second + next_Dir.second)) return INT_MIN;
	if(depth >= 10){
		score = getNewScore(score, player.board[now.F + next_Dir.F][now.S + next_Dir.S]);//renew score
		return score;
	}
	if(player.board[now.F + next_Dir.F][now.S + next_Dir.S] == 'b'){
		player.condition += 3;
		return DFS(score, player, now, make_pair<int, int>(0, 0), depth + 1);
	}
	if(canmove(player)){
		score = getNewScore(score, player.board[now.F + next_Dir.F][now.S + next_Dir.S]);//renew score
		player.board[now.first][now.second] = '.';
		player.board[now.first + next_Dir.first][now.second + next_Dir.second] = player.identity;//move
		now.first += next_Dir.first;
		now.second += next_Dir.second;//renew now
		int max = INT_MIN;
		int arr[4]; //call next one
		arr[0] = DFS(score, player, now, _up, depth + 1);
		arr[1] = DFS(score, player, now, _dowm, depth + 1);
		arr[2] = DFS(score, player, now, _left, depth + 1);
		arr[3] = DFS(score, player, now, _right, depth + 1);
		return std::max(std::max(arr[0], arr[1]), std::max(arr[2], arr[3]));
	}
	else{//not recover from bomb 
		player.condition--;
		return DFS(score, player, now, make_pair<int, int>(0, 0), depth + 1);
	}
}
int main(void) {
	int round;
	cin >> round >> M >> N;
	BOT player(round, M, N);
	player.init();
	pair<int, int> myLocation =player.getCurrentPosition();
	int myScore = player.identity == 'A' ? player.AScore : player.BScore;
	//cout << player.makeDecision() << end;
	int arr[4];
		arr[0] = DFS(myScore, player, myLocation, _up, 1);
		arr[1] = DFS(myScore, player, myLocation, _dowm, 1);
		arr[2] = DFS(myScore, player, myLocation, _left, 1);
		arr[3] = DFS(myScore, player, myLocation, _right, 1);
	int max = arr[0];
	int res = 0;
	for(int i = 1; i < 4; i++){
		if(arr[i] > max){
			max = arr[i];
			res = i;
		}
	}
	cout << defaultOutput[res] << endl;
}
