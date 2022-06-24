#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

struct grid {
  char obj;
};

struct pos {
  int x: 8, y: 8;
};

struct player {
  pos p;
  int score;
};

struct choice {
  string dir;
  int score;
};

int m, n;
vector<vector<grid>> map;

bool valid (pos p, bool first) {
  if (p.x < 0 || p.x >= n || p.y < 0 || p.y >= m || map[p.y][p.x].obj == 'x') return false;
  if (first && (map[p.y][p.x].obj == 'A' || map[p.y][p.x].obj == 'B')) return false;
  return true;
}

choice max (vector<choice> choices) {
  vector<choice> cur_max = {{"LEFT", -2147483648}};
  for (auto x: choices) {
    if (x.score > cur_max[0].score) {
      cur_max.resize(0);
      cur_max.push_back(x);
    }
    if (x.score == cur_max[0].score)
      cur_max.push_back(x);
  }
  return cur_max[rand() % cur_max.size()];
}

choice bot (pos p, choice cur, int step) {
  int score = cur.score;
  if (map[p.y][p.x].obj == 'm') ++score;
  else if (map[p.y][p.x].obj == 'n') --score;
  else if (map[p.y][p.x].obj == 's') score *= 2;
  else if (map[p.y][p.x].obj == 't') score /= 2;
  if (step == 0) return {cur.dir, score};
  vector<choice> choices;
  if (valid({p.x - 1, p.y}, false))
    choices.push_back(bot({p.x - 1, p.y}, {cur.dir, score}, step - 1));
  if (valid({p.x + 1, p.y}, false))
    choices.push_back(bot({p.x + 1, p.y}, {cur.dir, score}, step - 1));
  if (valid({p.x, p.y - 1}, false))
    choices.push_back(bot({p.x, p.y - 1}, {cur.dir, score}, step - 1));
  if (valid({p.x, p.y + 1}, false))
    choices.push_back(bot({p.x, p.y + 1}, {cur.dir, score}, step - 1));
  return max(choices);
}

int main () {
  srand(4112170);
  int t;
  char c;
  player A, B, me;
  vector<choice> choices;
  cin >> t >> m >> n;
  map.resize(m, vector<grid>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> map[i][j].obj;
      if (map[i][j].obj == 'A') A.p = {j, i};
      if (map[i][j].obj == 'B') B.p = {j, i};
    }
  }
  cin >> A.score >> B.score >> c;
  if (c == 'A') me = A;
  else me = B;
  if (valid({me.p.x - 1, me.p.y}, true))
    choices.push_back(bot({me.p.x - 1, me.p.y}, {"LEFT", me.score}, 8));
  if (valid({me.p.x + 1, me.p.y}, true))
    choices.push_back(bot({me.p.x + 1, me.p.y}, {"RIGHT", me.score}, 8));
  if (valid({me.p.x, me.p.y - 1}, true))
    choices.push_back(bot({me.p.x, me.p.y - 1}, {"UP", me.score}, 8));
  if (valid({me.p.x, me.p.y + 1}, true))
    choices.push_back(bot({me.p.x, me.p.y + 1}, {"DOWN", me.score}, 8));
  if (choices.empty()) cout << "LEFT\n";
  else cout << max(choices).dir << '\n';
  return 0;
}