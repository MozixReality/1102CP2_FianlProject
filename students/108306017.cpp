#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define TIMELIMIT 0.92
#define SERACHDEPTH 8

enum Direction {
   UP,
   LEFT,
   RIGHT,
   DOWN
};

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
   Position(int _score, Direction _direction, pair<int, int> _position) {
      score = _score;
      direction = _direction;
      position = _position;
   }
   void print() {
      cout << "==========" << endl;
      cout << "score: " << score << endl;
      cout << "direction: " << defaultOutput(direction) << endl;
      cout << "position: (" << position.first << ", " << position.second << ")" << endl;
      cout << "==========" << endl;
   }
   int score;
   Direction direction;
   pair<int, int> position;
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

char reVal(int num)
{
   if (num >= 0 && num <= 9)
      return (char)(num + '0');
   else
      return (char)(num - 10 + 'A');
}


string fromDeci(string& res, int base, int inputNum, int string_len)
{
   int index = 0;

   while (inputNum > 0) {
      res.push_back(reVal(inputNum % base));
      index++;
      inputNum /= base;
   }

   
   reverse(res.begin(), res.end());

   int precision = string_len - std::min(string_len, int(res.size()));
   std::string s = std::string(precision, '0').append(res);
   return s;
}

class PLAYER : public Timer, public Random {
public:
   PLAYER(int round, int width, int height);
   ~PLAYER();
   void init();
   string makeDecision();

   Position getPositionFromNum(int n, int first, int second, int score);
   string makeDecision_Nstep(int Nstep);
   
private:
   bool validatePosition(int x, int y);
   void check_potential_of_position(
      Position& tmp, int& currentMaxScore, Direction& currentDirection, queue<Position>& tmpq, bool**& visited);
   
   pair<int, int> getCurrentPosition();
   int calculateScore(int currentScore, int x, int y);
   char** board;
   int round;
   int width, height;
   int AScore, BScore;
   pair<int, int> ALocation, BLocation;
   char identity;
};


Position PLAYER::getPositionFromNum(int n, int first, int second, int score) {
   switch (n - 48) {
   case 0:
      return Position(score, LEFT, make_pair(first - 1, second));
   case 1:
      return Position(score, RIGHT, make_pair(first + 1, second));
   case 2:
      return Position(score, UP, make_pair(first, second - 1));
   case 3:
      return Position(score, DOWN, make_pair(first, second + 1));
   default:
      break;
   }
   return Position(0, LEFT, make_pair(0, 0));
}

string PLAYER::makeDecision_Nstep(int Nstep) {
   
   int currentMaxScore = INT32_MIN;
   Direction currentDirection;

   
   queue<vector<Position> > route_queue;
   for (int i = 0; i < pow(4, Nstep); i++) {
      pair<int, int> currentPosition = getCurrentPosition();
      vector<Position> route;
      string  dirs;
      dirs = fromDeci(dirs, 4, i, Nstep);
      for (int j = 0; j < Nstep; j++) {
         route.push_back(getPositionFromNum(dirs[j], currentPosition.first, currentPosition.second, 0));
         currentPosition.first = route.back().position.first;
         currentPosition.second = route.back().position.second;
      }
      route_queue.push(route);
   }


   vector<Position> route;
   vector<Position> best_route;
   vector<int> scores;
   int best_route_id = 0;
   int counter = 0;
   while (!route_queue.empty()) {
      this->stopTimer();
      if (getTime() > TIMELIMIT)
         break;

      route = route_queue.front();
      bool** visited = new bool* [height];
      for (int i = 0; i < height; i++) {
         visited[i] = new bool[width];
         for (int j = 0; j < width; j++) {
            visited[i][j] = false;
         }
      }
      int tmpscore = 0;
      for (int j = 0; j < route.size(); j++) {
         Position tmp = route[j];
         if (!validatePosition(route[j].position.first, route[j].position.second)) {
            tmpscore = INT32_MIN;
            break;
         }
         else {
            if (visited[route[j].position.second][route[j].position.first]) {
               route[j].score = tmpscore;
               continue;
            }
            else {
               visited[route[j].position.second][route[j].position.first] = true;
               tmpscore = calculateScore(tmpscore, route[j].position.first, route[j].position.second);
               route[j].score = tmpscore;
            }
         }
      }
      delete[] visited;
      route_queue.pop();
      if (tmpscore >= currentMaxScore) {
         currentMaxScore = tmpscore;
         currentDirection = route[0].direction;
         best_route = route;
         best_route_id = counter;
      }
      scores.push_back(tmpscore);
      counter += 1;  
   }
   return defaultOutput(currentDirection);
}

PLAYER::PLAYER(int _round, int _width, int _height) {
   round = _round;
   width = _width;
   height = _height;
}

PLAYER::~PLAYER() {
   for (int i = 0; i < height; i++) {
      delete[] board[i];
   }
   delete[] board;
}

void PLAYER::init() {
   board = new char* [height];
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

pair<int, int> PLAYER::getCurrentPosition() {
   if (identity == 'A')
      return ALocation;
   else if (identity == 'B')
      return BLocation;
   return make_pair(-1, -1);
}

bool PLAYER::validatePosition(int x, int y) {
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

int PLAYER::calculateScore(int currentScore, int x, int y) {
   if (x < 0 || x >= width || y < 0 || y >= height) return -1;
   char gettingObject = board[y][x];
   switch (gettingObject) {
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

string PLAYER::makeDecision() {
   
   bool** visited = new bool* [height];
   for (int i = 0; i < height; i++) {
      visited[i] = new bool[width];
      for (int j = 0; j < width; j++) {
         visited[i][j] = false;
      }
   }

   
   int currentMaxScore = 0;
   Direction currentDirection;

   queue<Position> position_queue;
   pair<int, int> currentPosition = getCurrentPosition();
   Position initPositions[4] = {
       Position(0, LEFT, make_pair(currentPosition.first - 1, currentPosition.second)),
       Position(0, RIGHT, make_pair(currentPosition.first + 1, currentPosition.second)),
       Position(0, UP, make_pair(currentPosition.first, currentPosition.second - 1)),
       Position(0, DOWN, make_pair(currentPosition.first, currentPosition.second + 1)) };
   map<int, int> refrenceOrder;

   setRandom();
   for (int i = 0; i < 4; i++) {
      refrenceOrder[generateRandom(0, INT32_MAX)] = i;
   }
   for (const auto& s : refrenceOrder) {
      int i = s.second;
      if (validatePosition(initPositions[i].position.first, initPositions[i].position.second)) {
         // Tp prevent no legal steps.
         currentDirection = initPositions[i].direction;
         position_queue.push(initPositions[i]);
      }
      else {
         initPositions[i].score = -1;
      }
   }
   refrenceOrder.clear();
   visited[currentPosition.second][currentPosition.first] = true;

   while (!position_queue.empty()) {
      if (getTime() > TIMELIMIT)
         break;
      
      queue<Position> tmpq;
      while (!position_queue.empty()) {
         if (getTime() > TIMELIMIT) break;

         Position tmp = position_queue.front();
         check_potential_of_position(tmp, currentMaxScore, currentDirection, tmpq, visited);
         visited[tmp.position.second][tmp.position.first] = true;
         position_queue.pop();
      }
      position_queue = tmpq;
   }
   delete[] visited;
   return defaultOutput(currentDirection);
}

void PLAYER::check_potential_of_position(Position& tmp, int& currentMaxScore, Direction& currentDirection, queue<Position>& tmpq, bool**& visited)
{
   map<int, int> refrenceOrder;
   Position tmpInitPsitions[4] = {
            Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first - 1), tmp.direction, make_pair(tmp.position.first - 1, tmp.position.second)),
            Position(calculateScore(tmp.score, tmp.position.second, tmp.position.first + 1), tmp.direction, make_pair(tmp.position.first + 1, tmp.position.second)),
            Position(calculateScore(tmp.score, tmp.position.second - 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second - 1)),
            Position(calculateScore(tmp.score, tmp.position.second + 1, tmp.position.first), tmp.direction, make_pair(tmp.position.first, tmp.position.second + 1)) };
   setRandom();
   for (int i = 0; i < 4; i++) {
      //refrenceOrder[generateRandom(0, INT32_MAX)] = i;
      refrenceOrder[i] = i;
   }
   for (const auto& s : refrenceOrder) {
      int i = s.second;
      if (validatePosition(tmpInitPsitions[i].position.first, tmpInitPsitions[i].position.second) && !visited[tmp.position.second][tmp.position.first]) {
         if (tmpInitPsitions[i].score > currentMaxScore) {
            currentMaxScore = tmpInitPsitions[i].score;
            currentDirection = tmpInitPsitions[i].direction;
         }
         tmpq.push(tmpInitPsitions[i]);
      }
   }
}


int main(void) {
   int round, M, N;
   cin >> round >> M >> N;
   PLAYER player(round, N, M);
   player.startTimer();
   player.init();
   cout << player.makeDecision_Nstep(SERACHDEPTH) << endl;
   player.stopTimer();
}
