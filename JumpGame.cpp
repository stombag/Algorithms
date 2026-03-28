#include<iostream>
#include<vector>

using namespace std;

int n;
vector<vector<int>> board(100, vector<int>(100, 0));
vector<vector<int>> cache(100, vector<int>(100, 0));

bool jump(int y, int x) {
	if (y >= n || x >= n) return false;

	if (y == n - 1 && x == n - 1) return true;
	int jumpSize = board[y][x];
	return jump(y + jumpSize, x) || jump(y, x + jumpSize);
}

bool jump2(int y, int x)
{
	if (y >= n || x >= n) return 0;
	if (y == n - 1 && x == n - 1) return 1;
	int& ret = cache[y][x];

	if (ret != -1) return ret;
	int jumpSize = board[y][x];
	return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));

}
