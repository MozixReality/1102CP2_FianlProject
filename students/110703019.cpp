#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
using namespace std;
#define min59 -576460752303423488
string directionn[4]= { "LEFT\n","UP\n","DOWN\n","RIGHT\n" };
int directiony[4] = { 0,-1,1,0 };
int directionx[4] = { -1,0,0,1 };
pair<int, int> positiona, positionb, position;
char board[20][20], player;
int roundd, y, x, count1, count2, bestway2;
long long pointa, pointb, point;
int bestway = 0, curdepth = 1, bestwaytemp = 0;
long long bestpt = min59, bestpttemp = min59; 
clock_t a, b; 
struct move1 
{
	pair<int, int> pos;
	int point = 0;
	int depth = 0;
	int dir = 0;
	int dir_ori = 0;
	map < pair<int, int>, int> visited;
};
move1 movetemp1, movetemp2, movetemp[4];
queue< move1 > q;
bool isvalidpos(int yy, int xx) 
{
	if (xx < 0 || xx >= x)
		return false;
	else if (yy < 0 || yy >= y)
		return false;
	return true;
}
bool isvalidchar(char a) 
{
	if (a == 'x')
		return false;
	else if (a == 'B' && player == 'A')
		return false;
	else if (a == 'A' && player == 'B')
		return false;
	return true;
}
long long pointcal(char a, long long point1) 
{
	switch (a) {
	case 'm':
		return point1 + 1;
	case 'n':
		return point1 - 1;
	case 's':
		return point1 * 2;
	case 't':
		return point1 / 2;
	default:
		return point1;
	}
}
int findbestpos() 
{
	priority_queue<pair<long long, int>> decidetemp1;
	for (count1 = 0; count1 < 4; count1++) 
	{
		if (isvalidpos(position.first + directiony[count1], position.second + directionx[count1]))
		{
			if (isvalidchar(board[position.first + directiony[count1]][position.second + directionx[count1]]))
			{
				movetemp1.point = pointcal(board[position.first + directiony[count1]][position.second + directionx[count1]], point);
				movetemp1.dir = count1;
				movetemp1.dir_ori = count1;
				movetemp1.pos = make_pair(position.first + directiony[count1], position.second + directionx[count1]);
				movetemp1.visited[position] = 1;
				movetemp[count1] = movetemp1;
				movetemp[count1].visited[movetemp1.pos] = 1;
				decidetemp1.push(make_pair(movetemp1.point, count1));
				if (movetemp1.point > bestpt)
				{
					bestway = movetemp1.dir_ori;
					bestpt = movetemp1.point;
				}
			}
		}
	}
	while (decidetemp1.size())
	{
		q.push(movetemp[decidetemp1.top().second]);
		decidetemp1.pop();
	}
	while ((double(b) - double(a)) / CLOCKS_PER_SEC < 0.7 && q.size()) 
	{
		b = clock();
		movetemp1 = q.front();
		if (movetemp1.depth != curdepth)
		{
			curdepth = movetemp1.depth;
			bestway = bestwaytemp;
			bestpt = bestpttemp;
			bestpttemp = min59;
		}
		for (count1 = 0; count1 < 4; count1++)
		{
			if (isvalidpos(movetemp1.pos.first + directiony[count1], movetemp1.pos.second + directionx[count1]))
			{
				if (isvalidchar(board[movetemp1.pos.first + directiony[count1]][movetemp1.pos.second + directionx[count1]]))
				{
					movetemp2.depth = curdepth + 1;
					movetemp2.dir = count1;
					movetemp2.dir_ori = movetemp1.dir_ori;
					movetemp2.pos = make_pair(movetemp1.pos.first + directiony[count1], movetemp1.pos.second + directionx[count1]);
					movetemp2.visited = movetemp1.visited;
					if (movetemp2.visited[movetemp2.pos])
					{
						movetemp2.point = movetemp1.point;
					}
					else
					{
						movetemp2.point = pointcal(board[movetemp1.pos.first + directiony[count1]][movetemp1.pos.second + directionx[count1]], movetemp1.point);
					}
					movetemp[count1] = movetemp2;
					movetemp[count1].visited[movetemp2.pos] = 1;
					decidetemp1.push(make_pair(movetemp2.point, count1));
					if (movetemp2.point > bestpttemp)
					{
						bestwaytemp = movetemp2.dir_ori;
						bestpttemp = movetemp2.point;
					}
				}
			}
		}
		while (decidetemp1.size())
		{
			q.push(movetemp[decidetemp1.top().second]);
			decidetemp1.pop();
		}
		q.pop();
	}
	return bestway;
}
int main()
{
	cin >> roundd >> y >> x; 
	for (count1 = 0; count1 < y; count1++) 
	{
		for (count2 = 0; count2 < x; count2++)
		{
			cin >> board[count1][count2];
			if (board[count1][count2] == 'A')
				positiona = make_pair(count1, count2);
			if (board[count1][count2] == 'B')
				positionb = make_pair(count1, count2);
		}
	}
	cin >> pointa >> pointb >> player;
	a = clock();
	if (player == 'A') 
	{
		position = positiona;
		point = pointa;
	}
	else
	{
		position = positionb;
		point = pointb;
	}
	movetemp1.depth = 1;
	movetemp1.point = point;
	movetemp1.pos = position;
	bestway2=findbestpos();
	cout << directionn[bestway];
}