/* Version 10 Delete unuse function */
/* round < 700 -> Dijkstra*/ 
/* Version 11 dangerZone */
#include <iostream> 
#include <vector>
#include <math.h>

using namespace std;

enum Direction {
	NOTSET,UP, DOWN, RIGHT, LEFT
};
typedef struct Position {
	int x;
	int y;
	Position(const int& _x, const int& _y) : x(_x), y(_y) {}
	Position(const Position& pos) : x(pos.x), y(pos.y) {}
	Position() : x(-1), y(-1) {}
} Position;

class Bot {
public:
	Bot(const vector<vector<char> > _map, const int _P, const int _Q, const char _character) : map(_map), P(_P), Q(_Q), character(_character) {
		const int M = _map.size(), N = _map[0].size();
		traveled = new bool*[M];
		foe_traveled = new bool*[M];
		distance = new int*[M];
		previous = new Direction*[M];
		/* queue = new Position[401]; */
		for (int i=0; i<N; ++i) {
			traveled[i] = new bool[N];
			foe_traveled[i] = new bool[N];
			distance[i] = new int[N];
			previous[i] = new Direction[N];
		}
		/* cout << "Create Bot Success" << endl; */
		if (character == 'A') {
			foe_character = 'B';
			myScore = _P;
			foeScore = _Q;
		} else {
			foe_character = 'A';
			myScore = _Q;
			foeScore = _P;
		}
	}
	~Bot();
	void decide(const int _round) {
		// test line 
		/* printf("Leave_num = %d\n", in_danger_zone('A')); */
		/* cout << "AB_dis == " << AB_dis() << endl; */
		// test line
		Position cur_pos = find_pos(character);
		round = _round;
		bool IAlreadyWin = false;
		bool IAlreadyLose = false;
		Position countIfWin = countMushroomsAndStar(map);
		const int mushrooms_num = countIfWin.x;
		const int superStars_num = countIfWin.y;
		if (superStars_num == 0) {
			if (myScore > mushrooms_num + foeScore)
				IAlreadyWin = true; 
			if (myScore + mushrooms_num < foeScore)
				IAlreadyLose = true;
		} else {
			if (myScore > (foeScore + mushrooms_num) * pow(2, superStars_num))
				IAlreadyWin = true; 
			if ((myScore + mushrooms_num) * pow(2, superStars_num) < foeScore)
				IAlreadyLose = true;
		}
		/* if (false) { */
		const int disBetween = AB_dis();
		IAlreadyWin |= (trapped_foe_already(foe_character) && disBetween % 2 == 1);
		if (true) {
			/* Dijkstra */
			const int M = map.size()-1, N = map[0].size()-1;
			const Position init_pos(cur_pos);
			/* cout << M << " x " << N << endl; */

			/* init */
			const int boundary = map.size();
			for (int i=0; i<boundary; ++i) {
				for (int j=0; j<boundary; ++j) {
					distance[i][j] = INT32_MIN;
					traveled[i][j] = is_in(map[i][j], "xAB");
					foe_traveled[i][j] = is_in(map[i][j], "xAB");
					previous[i][j] = NOTSET;
				}
			}
			distance[cur_pos.x][cur_pos.y] = myScore;
			/* print_distance(); */

			/* Algorithm */
			int back = 1, cur = 0;
			queue[0] = cur_pos;
			/* queue[0].y = cur_pos.y; */
			traveled[queue[0].x][queue[0].y] = true;
			/* printf("Cur: (x, y) = (%d, %d)\n", queue[0].x, queue[0].y); */
			/* cout << "Do_While Statement\n"; */
			/* int cur_distance = myScore; */
			/* cout << "MyScore: " << myScore << endl; */
			do {
				const int x = queue[cur].x, y = queue[cur].y;
				const int cur_distance = distance[x][y];
				int max_distance = INT32_MIN;
				if (x > 0 && !traveled[x-1][y] && previous[x-1][y] != DOWN) {
					if (cur_distance + distance_calculator(x-1, y, cur_distance) > distance[x-1][y]) {
						distance[x-1][y] = cur_distance + distance_calculator(x-1, y, cur_distance);
						queue[back].x = x - 1;
						queue[back].y = y;
						++back;
						previous[x-1][y] = DOWN;
					}
					/* distance[x-1][y] = max(cur_distance + distance_calculator(x-1, y, cur_distance), distance[x-1][y]); */
					/* ++back; */
					/* traveled[x-1][y] = true; */
				}
				if (x < M && !traveled[x+1][y] && previous[x+1][y] != UP) {
					if (cur_distance + distance_calculator(x+1, y, cur_distance) > distance[x+1][y]) {
						queue[back].x = x + 1;
						queue[back].y = y;
						distance[x+1][y] = cur_distance + distance_calculator(x+1, y, cur_distance);
						++back;
						previous[x+1][y] = UP;
					}
					/* ++back; */
					/* traveled[x+1][y] = true; */
				}
				if (y > 0 && !traveled[x][y-1] && previous[x][y-1] != RIGHT) {
					if (cur_distance + distance_calculator(x, y-1, cur_distance) > distance[x][y-1]) {
						queue[back].x = x;
						queue[back].y = y-1;
						distance[x][y-1] = cur_distance + distance_calculator(x, y-1,cur_distance);
						++back;
						previous[x][y-1] = RIGHT;
					}
					/* distance[x][y-1] = max(cur_distance + distance_calculator(x, y-1, cur_distance), distance[x][y-1]); */
					/* ++back; */
					/* traveled[x][y-1] = true; */
				}
				if (y < N && !traveled[x][y+1] && previous[x][y+1] != LEFT) {
					if (cur_distance + distance_calculator(x, y+1, cur_distance) > distance[x][y+1]) {
						queue[back].x = x;
						queue[back].y = y+1;
						distance[x][y+1] = cur_distance + distance_calculator(x, y+1, cur_distance);
						++back;
						previous[x][y+1] = LEFT;
					}
					/* distance[x][y+1] = max(cur_distance + distance_calculator(x, y+1, cur_distance), distance[x][y+1]); */
					/* ++back; */
					/* traveled[x][y+1] = true; */
				}
				traveled[x][y] = true;
				++cur;
				/* printf("Cur: (x, y) = (%d, %d)\n", x, y); */
			} while (cur < back);
			/* cout << "Leave Do_While\n"; */
			/* print_distance(); */

			/* Choose Path */
			/* int valid_position_count[5] = {0}; // If two ways to go and one 0, one > 0 */ 
			/* if (valid_position_count(init_pos.x, init_pos.y) == 2) { */

			/* } */

			int target_distance = INT32_MIN;
			Position target_pos;
			distance[init_pos.x][init_pos.y] = INT32_MIN; // Set init_pos back to INT32_MIN to avoid target_pos == init_pos
			for (int i=0; i<map.size(); ++i) {
				for (int j=0; j<map[0].size(); ++j) {
					if (target_distance < distance[i][j]) {
						target_pos.x = i;
						target_pos.y = j;
						target_distance = distance[i][j];
					}
				}
			}
			/* if (trapped_foe_already()) cout << "Trapped foe already\n"; */ 
			/* else cout << "Haven't trapped it yet\n"; */
			if (trapped_foe_already(foe_character) && disBetween % 2 == 1) {
				const Position tmp_target_pos = follow_foe();
				if (valid_position(tmp_target_pos.x, tmp_target_pos.y))
					target_pos = tmp_target_pos;
				/* printf("pos = (%d, %d)", target_pos.x, target_pos.y); */
			}
			else if (target_distance == myScore || IAlreadyLose || IAlreadyWin) { // No more better target or trapped foe already
				/* cout << "target_distance = myScore\n"; */ 
				/* if (IAlreadyLose) cout << "Lose\n"; */
				/* print_previous(); */
				const Position tmp_target_pos = follow_foe();
				if (distance[tmp_target_pos.x][tmp_target_pos.y] >= myScore && valid_position(tmp_target_pos.x, tmp_target_pos.y)) 
					target_pos = tmp_target_pos;
				/* printf("TargetPos = %d, %d\n", target_pos.x, target_pos.y); */
			}
			/* if (trapped_foe_already()) */
			/* 	target_pos = approach_foe(); */
			/* cout << "target_pos = " << target_pos.x << ", " << target_pos.y << endl; */
			/* All done */
			if (target_pos.x == init_pos.x && target_pos.y == init_pos.y) {
				/* cout << "TargetPos = InitPos\n"; */
				const int x = target_pos.x, y = target_pos.y; 
				if (valid_position(x-1, y)) {
					cout << "UP\n";
					return;
				}
				if (valid_position(x, y-1)) {
					cout << "LEFT\n";
					return;
				}
				if (valid_position(x+1, y)) {
					cout << "DOWN\n";
					return;
				}
				if (valid_position(x, y+1)) {
					cout << "RIGHT\n";
					return;
				}
				cout << "DEAD\n";
				return;
			}
			/* Not all done */
			while (true) {
				if (target_pos.x == init_pos.x - 1 && target_pos.y == init_pos.y) {
					cout << "UP\n";
					return;
				}
				if (target_pos.x == init_pos.x + 1 && target_pos.y == init_pos.y) {
					cout << "DOWN\n";
					return;
				}
				if (target_pos.x == init_pos.x && target_pos.y == init_pos.y - 1) {
					cout << "LEFT\n";
					return;
				}
				if (target_pos.x == init_pos.x && target_pos.y == init_pos.y + 1) {
					cout << "RIGHT\n";
					return;
				}
				Direction _from = previous[target_pos.x][target_pos.y];
				switch (_from) {
					case UP:
						target_pos.x -= 1;
						/* cout << "up\n"; */
						break;
					case DOWN:
						target_pos.x += 1;
						/* cout << "down\n"; */
						break;
					case RIGHT:
						target_pos.y += 1;
						/* cout << "right\n"; */
						break;
					case LEFT:
						target_pos.y -= 1;
						/* cout << "left\n"; */
						break;
					case NOTSET:
						cout << "ERROR\n";
						return;
				}
			}
		} else {
			// Add Alpha-beta search, call it 16 times
			cout << "D" << endl;
			const Position myPos = find_pos(character), foePos = find_pos(foe_character);
			Position newMe = myPos, newFoe = foePos;
			int result[16] = {0};
			for (int i=0; i<16; ++i) result[i] = INT_MIN;
			const int newMeXdir[16] =  { 1,  1, -1, -1,  0,  0,  0,  0,  1,  1, -1, -1,  0,  0,  0,  0};
			const int newMeYdir[16] =  { 0,  0,  0,  0,  1,  1, -1, -1,  0,  0,  0,  0,  1,  1, -1, -1};
			const int newFoeXdir[16] = { 1,  0,  1,  0,  1,  0,  1,  0, -1,  0, -1,  0, -1,  0, -1,  0};
			const int newFoeYdir[16] = { 0,  1,  0,  1,  0,  1,  0,  1,  0, -1,  0, -1,  0, -1,  0, -1};
			Position MushroomsAndStars = countMushroomsAndStar(map);
			for (int i=0; i<16; ++i) {
				/* printf("myNewPos = (%d, %d), foeNewPos = (%d, %d)\n", myPos.x + newMeXdir[i], myPos.y + newMeYdir[i], foePos.x + newFoeXdir[i], foePos.y + newFoeYdir[i]); */
				if (valid_position(myPos.x + newMeXdir[i], myPos.y + newMeYdir[i]) && valid_position(foePos.x + newFoeXdir[i], foePos.y + newFoeYdir[i])) {
					/* printf("Valid Position Condition, myScore = %d, foeScore = %d\n", myScore, foeScore); */
					newMe = myPos;
					newFoe = foePos;
					newMe.x += newMeXdir[i];
					newMe.y += newMeYdir[i];
					newFoe.x += newFoeXdir[i];
					newFoe.y += newFoeYdir[i];
					result[i] = alpha_beta(myScore, foeScore, round+1, map, MushroomsAndStars, myPos, foePos, newMe, newFoe);
				}
				cout << "DEBUG" << endl;
			}
			/* for (int i=0; i<16; ++i) */
			/* 	printf("Alpha-beta search no %3d = %d\n", i, result[i]); */
			int tmpMax = INT32_MIN;
			int lastDecision = 0;
			for (int i=0; i<16; ++i) {
				if (tmpMax < result[i]) {
					tmpMax =result[i];
					lastDecision = i;
				}
			}
			// Decide where to go
			if (newMeXdir[lastDecision] == 1)
				cout << "DOWN\n";
			else if (newMeXdir[lastDecision] == -1) 
				cout << "UP\n";
			else if (newMeYdir[lastDecision] == 1) 
				cout << "RIGHT\n";
			else if (newMeYdir[lastDecision] == -1)
				cout << "LEFT\n";
			else
				cout << "ERROR\n";
			return;
		}
	}
	void print_distance();
	void print_traveled();
	void print_previous();
	void print_map(vector<vector<char> >& tmpmap);
private:
	Position find_pos(const char target_character) {
		for (int i = 0; i < map.size(); ++i)
			for (int j = 0; j < map[0].size(); ++j)
				if (map[i][j] == target_character)
					return Position(i, j);
		return Position();
	}
	bool is_in(const char c, const string s) {
		for (int i = 0; i < s.size(); ++i)
			if (c == s[i])
				return true;
		return false;
	}
	bool valid_position(const int x, const int y) {
		if (x < 0 || x >= map.size())
			return false;
		if (y < 0 || y >= map[0].size())
			return false;
		if (is_in(map[x][y], "xAB"))
			return false;
		return true;
	}
	int distance_calculator(const int x, const int y, const int& dis) {
		const char c = map[x][y];
		if (c == 'b')
			return -10;
		if (c == 'm')
			return 1;
		if (c == 'n')
			return -1;
		if (c == 's') {
			return dis;
		}
		if (c == 't') {
			return -(dis);
		}
		return 0;
	}
	int valid_position_count(const int x, const int y) {
		int count = 0;
		if (valid_position(x-1, y)) ++count;
		if (valid_position(x+1, y)) ++count;
		if (valid_position(x, y+1)) ++count;
		if (valid_position(x, y-1)) ++count;
		return count;
	}
	Position follow_foe() {
		Position find_foe, target_pos;
		if (character == 'A')
			find_foe = find_pos('B');
		else 
			find_foe = find_pos('A');
		const Position foe_pos = find_foe;
		int max_distance = INT32_MIN;
		if (valid_position(foe_pos.x+1, foe_pos.y)) {
			if (max_distance < distance[foe_pos.x+1][foe_pos.y]) {
				target_pos.x = foe_pos.x + 1;
				target_pos.y = foe_pos.y;
				max_distance = distance[foe_pos.x+1][foe_pos.y];
			}
		}
		if (valid_position(foe_pos.x-1, foe_pos.y)) {
			if (max_distance < distance[foe_pos.x-1][foe_pos.y]) {
				target_pos.x = foe_pos.x - 1;
				target_pos.y = foe_pos.y;
				max_distance = distance[foe_pos.x-1][foe_pos.y];
			}
		}
		if (valid_position(foe_pos.x, foe_pos.y+1)) {
			if (max_distance < distance[foe_pos.x][foe_pos.y+1]) {
				target_pos.x = foe_pos.x;
				target_pos.y = foe_pos.y + 1;
				max_distance = distance[foe_pos.x][foe_pos.y+1];
			}
		}
		if (valid_position(foe_pos.x, foe_pos.y-1)) {
			if (max_distance < distance[foe_pos.x][foe_pos.y-1]) {
				target_pos.x = foe_pos.x;
				target_pos.y = foe_pos.y - 1;
				max_distance = distance[foe_pos.x][foe_pos.y-1];
			}
		}
		/* cout << "Max_dis = " << max_distance << endl; */
		return target_pos;
	}
	bool trapped_foe_already(const char who) {
		Position foe_pos = find_pos(who);
		/* if (character == 'A') foe_pos = find_pos('B'); */
		/* else foe_pos = find_pos('A'); */
		if (valid_position_count(foe_pos.x, foe_pos.y) > 2) return false;
		bool find_trapped_end1 = false;
		Position foe_queue[100000];
		int cur = 0, back = 1;
		foe_queue[0] = foe_pos;
		bool step_before[map.size()][map[0].size()];
		for (int i=0; i<map.size(); ++i)
			for (int j=0; j<map[0].size(); ++j)
				step_before[i][j] = false;
		/* cout << "Trapped Foe While\n"; */
		while (cur < back) {
			bool no_more_path = true;
			const int x = foe_queue[cur].x;
			const int y = foe_queue[cur].y;
			/* printf("While Loop %d %d\n", x, y); */
			if (valid_position_count(x, y) > 2) {
				/* printf("First if Pos: %d %d\n", x, y); */
				return false;
			}
			if (valid_position(x+1, y) && !step_before[x+1][y]) {
				foe_queue[back].x = x+1;
				foe_queue[back].y = y;
				step_before[x+1][y] = true;
				no_more_path = false;
				++back;
			}
			if (valid_position(x-1, y) && !step_before[x-1][y]) {
				foe_queue[back].x = x-1;
				foe_queue[back].y = y;
				step_before[x-1][y] = true;
				no_more_path = false;
				++back;
			}
			if (valid_position(x, y+1) && !step_before[x][y+1]) {
				foe_queue[back].x = x;
				foe_queue[back].y = y+1;
				step_before[x][y+1] = true;
				no_more_path = false;
				++back;
			}
			if (valid_position(x, y-1) && !step_before[x][y-1]) {
				foe_queue[back].x = x;
				foe_queue[back].y = y-1;
				step_before[x][y-1] = true;
				no_more_path = false;
				++back;
			}
			++cur;
			if (!find_trapped_end1 && no_more_path) {
				/* printf("Second if Pos: %d %d\n", x, y); */
				find_trapped_end1 = true;
			}
			else if (find_trapped_end1 && no_more_path) {
				/* printf("Third if Pos: %d %d\n", x, y); */
				return true;
			}
		}
		/* cout << "Last decision\n"; */
		return false;
	}
	int newscore_alphabeta (const char& newPlaceChar, const int& curScore) {
		if (newPlaceChar == 'b') return curScore - 10;
		if (newPlaceChar == 'm') return curScore + 1;
		if (newPlaceChar == 'n') return curScore - 1;
		if (newPlaceChar == 's') return curScore * 2;
		if (newPlaceChar == 't') return curScore >> 1;
		return curScore;
	}
	int alpha_beta(const int _myScore, const int _foeScore, const int& _round, vector<vector<char> > _map, Position _countMashroomsAndStar, Position myPos, const Position foePos, const Position newMe, const Position newFoe) {
		/* cout << _round << endl; */
		/* if (_round > round + 6) { */
		if (_round > round + 50) {
			/* printf("Current round = %d, RUN OUT\n", _round); */
			/* cout << "Run Out" << endl; */
			if (_myScore == _foeScore) return 0;
			return _myScore > _foeScore ? 1 : -1;
		}
		// change old map with new Pos
		const int myNewScore = newscore_alphabeta(_map[newMe.x][newMe.y], _myScore);
		const int foeNewScore = newscore_alphabeta(_map[newFoe.x][newFoe.y], _foeScore);
		if (_map[newMe.x][newMe.y] == 'm') --_countMashroomsAndStar.x;
		if (_map[newFoe.x][newFoe.y] == 'm') --_countMashroomsAndStar.x;
		if (_map[newMe.x][newMe.y] == 's') --_countMashroomsAndStar.y;
		if (_map[newFoe.x][newFoe.y] == 's') --_countMashroomsAndStar.y;
		_map[newMe.x][newMe.y] = character;
		_map[newFoe.x][newFoe.y] = foe_character;
		_map[myPos.x][myPos.y] = '.';
		_map[foePos.x][foePos.y] = '.';
		if (_countMashroomsAndStar.y == 0) {
			if (myNewScore > _countMashroomsAndStar.x + foeNewScore) {
				/* cout << "I win\n"; */
				return 1;
			}
			if (myNewScore + _countMashroomsAndStar.x < foeNewScore) {
				/* cout << "Foe win\n"; */
				return -1;
			}
		}
		if (myNewScore > (_countMashroomsAndStar.x + foeNewScore) * 2 * _countMashroomsAndStar.y) {
			/* cout << "I win\n"; */
			return 1;
		}
		if ((_countMashroomsAndStar.x + myNewScore) * 2 * _countMashroomsAndStar.y < foeNewScore){
			/* cout << "Foe win\n"; */
			return -1;
		}
		if (_countMashroomsAndStar.x == 0 && _countMashroomsAndStar.y == 0) {
			/* cout << "All done\n"; */
			if (myNewScore == foeNewScore) return 0;
			return myNewScore > foeNewScore ? 1 : -1;
		}
		// Pruning Start
		// 16 if condition here
		int result = 0;
		Position nextNewMe, nextNewFoe;
		const int newMeXdir[16] =  { 1,  1, -1, -1,  0,  0,  0,  0,  1,  1, -1, -1,  0,  0,  0,  0};
		const int newMeYdir[16] =  { 0,  0,  0,  0,  1,  1, -1, -1,  0,  0,  0,  0,  1,  1, -1, -1};
		const int newFoeXdir[16] = { 1,  0,  1,  0,  1,  0,  1,  0, -1,  0, -1,  0, -1,  0, -1,  0};
		const int newFoeYdir[16] = { 0,  1,  0,  1,  0,  1,  0,  1,  0, -1,  0, -1,  0, -1,  0, -1};
		for (int i=0; i<16; ++i) {
			if (valid_position(newMe.x + newMeXdir[i], newMe.y + newMeYdir[i]) && valid_position(newFoe.x + newFoeXdir[i], newFoe.y + newFoeYdir[i])) {
				nextNewMe = newMe;
				nextNewFoe = newFoe;
				nextNewMe.x += newMeXdir[i];
				nextNewMe.y += newMeYdir[i];
				nextNewFoe.x += newFoeXdir[i];
				nextNewFoe.y += newFoeYdir[i];
				result += alpha_beta(myNewScore, foeNewScore, _round+1, _map, _countMashroomsAndStar, newMe, newFoe, nextNewMe, nextNewFoe);
				/* cout << "result = " << result << endl; */
			}
		}
		// if condition stop
		/* cout << "Result = " << result << endl; */
		return result;
	}
	vector<vector<char> > map;
	int round, P, Q, myScore, foeScore;
	char character, foe_character;
	bool ** traveled;
	bool ** foe_traveled;
	int ** distance;
	Direction ** previous;
	Position queue[100000];
	Position countMushroomsAndStar(vector<vector<char> >& _map);
	/* Direction ** from; */
	int in_danger_zone(const char who);
	int AB_dis();
};

int main (void) {
	int round, M, N;
	vector<vector<char> > map;
	int P, Q;
	char me;

	cin >> round >> M >> N;
	map.resize(M);
	for (int i=0; i<M; ++i) {
		map[i].resize(N);
		for (int j=0; j<N; ++j)
			cin >> map[i][j];
	}
	cin >> P >> Q >> me;

	Bot bot(map, P, Q, me);
	bot.decide(round);
	/* bot.print_traveled(); */
	/* bot.print_distance(); */
	/* bot.print_previous(); */
	return 0;
}

Bot::~Bot() {
	for (int i=0; i<map.size(); ++i) {
		delete [] traveled[i];
		delete [] foe_traveled[i];
		delete [] distance[i];
		delete [] previous[i];
	}
	delete [] traveled;
	delete [] foe_traveled;
	delete [] distance;
	delete [] previous;
	/* delete queue; */
}

int Bot::AB_dis() {
	Position positionA = find_pos('A'), positionB = find_pos('B');
	Position check_queue[100000];
	int cur = 0, back = 1;
	check_queue[0] = positionA;
	bool step_before[map.size()][map[0].size()];
	int step_number[map.size()][map[0].size()];
	for (int i=0; i<map.size(); ++i) {
		for (int j=0; j<map[0].size(); ++j) {
			step_before[i][j] = false;
			step_number[i][j] = 0;
		}
	}
	const int bound = map.size();
	while (cur < back) {
		const int x = check_queue[cur].x;
		const int y = check_queue[cur].y;
		const int cur_number = step_number[x][y];
		/* printf("While Loop %d %d\n", x, y); */
		/* printf("Cur_number = %d\n", cur_number); */
		if (x == positionB.x && y == positionB.y) {
			return step_number[x][y] - 1; // Distance between A and B
		}
		if (x < bound-1 && !is_in(map[x+1][y], "xA") && !step_before[x+1][y]) {
			check_queue[back].x = x+1;
			check_queue[back].y = y;
			step_before[x+1][y] = true;
			step_number[x+1][y] = cur_number + 1;
			++back;
		}
		if (x > 0 && !is_in(map[x-1][y], "xA") && !step_before[x-1][y]) {
			check_queue[back].x = x-1;
			check_queue[back].y = y;
			step_before[x-1][y] = true;
			step_number[x-1][y] = cur_number + 1;
			++back;
		}
		if (y < bound-1 && !is_in(map[x][y+1], "xA") && !step_before[x][y+1]) {
			check_queue[back].x = x;
			check_queue[back].y = y+1;
			step_before[x][y+1] = true;
			step_number[x][y+1] = cur_number + 1;
			++back;
		}
		if (y > 0 && !is_in(map[x][y-1], "xA") && !step_before[x][y-1]) {
			check_queue[back].x = x;
			check_queue[back].y = y-1;
			step_before[x][y-1] = true;
			step_number[x][y-1] = cur_number + 1;
			++back;
		}
		++cur;
	}
	return -1;

}

int Bot::in_danger_zone(const char who) {
	Position person_pos = find_pos(who);
	if (valid_position_count(person_pos.x, person_pos.y) > 2) return false;
	if (valid_position_count(person_pos.x, person_pos.y) == 1) return true;
	bool find_trapped_end1 = false;
	Position check_queue[100000];
	int cur = 0, back = 1;
	check_queue[0] = person_pos;
	bool step_before[map.size()][map[0].size()];
	int step_number[map.size()][map[0].size()];
	for (int i=0; i<map.size(); ++i) {
		for (int j=0; j<map[0].size(); ++j) {
			step_before[i][j] = false;
			step_number[i][j] = 0;
		}
	}
	/* cout << "In Danger While\n"; */
	bool find_out = false;
	bool find_end = false;
	int leave_num = -1;
	while (cur < back) {
		bool no_more_path = true;
		const int x = check_queue[cur].x;
		const int y = check_queue[cur].y;
		const int cur_number = step_number[x][y];
		/* printf("While Loop %d %d\n", x, y); */
		if (valid_position_count(x, y) > 2) {
			if (find_out && find_end) {
				/* cout << "Leave_number = " << leave_num << endl; */
				return leave_num;
			}
			if (!find_out) {
				leave_num = cur_number;
				find_out = true;
				/* printf("Leave_num check (%d, %d)\n", x, y); */
			}
		}
		if (valid_position(x+1, y) && !step_before[x+1][y]) {
			check_queue[back].x = x+1;
			check_queue[back].y = y;
			step_before[x+1][y] = true;
			step_number[x+1][y] = cur_number + 1;
			no_more_path = false;
			++back;
		}
		if (valid_position(x-1, y) && !step_before[x-1][y]) {
			check_queue[back].x = x-1;
			check_queue[back].y = y;
			step_before[x-1][y] = true;
			step_number[x-1][y] = cur_number + 1;
			no_more_path = false;
			++back;
		}
		if (valid_position(x, y+1) && !step_before[x][y+1]) {
			check_queue[back].x = x;
			check_queue[back].y = y+1;
			step_before[x][y+1] = true;
			step_number[x][y+1] = cur_number + 1;
			no_more_path = false;
			++back;
		}
		if (valid_position(x, y-1) && !step_before[x][y-1]) {
			check_queue[back].x = x;
			check_queue[back].y = y-1;
			step_before[x][y-1] = true;
			step_number[x][y-1] = cur_number + 1;
			no_more_path = false;
			++back;
		}
		++cur;
		if (no_more_path) {
			find_end = true;
		}
	}
	/* cout << "Last decision\n"; */
	return leave_num;
}
Position Bot::countMushroomsAndStar(vector<vector<char> >& countingMap) { // .x -> mushrooms; .y -> superStars
	Position count(0, 0);
	for (int i=0; i<countingMap.size(); ++i) {
		for (int j=0; j<countingMap[0].size(); ++j) {
			if (countingMap[i][j] == 'm') ++count.x;
			else if (countingMap[i][j] == 's') ++count.y;
		}
	}
	return count;
}
void Bot::print_distance() { 
	cout << "Print Distance\n";
	for (int i=0; i<map.size(); ++i) {
		for (int j=0; j<map[0].size(); ++j)
			printf("%11d", distance[i][j]);
		cout << endl;
	}
	return;
}
void Bot::print_traveled() {
	cout << "Print Traveled\n";
	for (int i=0; i<map.size(); ++i) {
		for (int j=0; j<map[0].size(); ++j)
			printf("%2d", traveled[i][j]);
		cout << endl;
	}
	return;
}
void Bot::print_previous() {
	cout << "Print Previous\n"; 
	for (int i=0; i<map.size(); ++i) {
		for (int j=0; j<map[0].size(); ++j)
			printf("%3d", previous[i][j]);
		cout << endl;
	}
	return;
}
void Bot::print_map(vector<vector<char> >& tmpmap) {
	for (int i=0; i<map.size(); ++i) {
		for (int j=0; j<map[0].size(); ++j) {
			cout  << tmpmap[i][j] << " ";
		}
		cout << endl;
	}
	return;
}
