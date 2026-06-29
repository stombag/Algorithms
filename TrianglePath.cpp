#include <iostream>

using namespace std;

int nTP, triangle[100][100];
int cashe[100][100];


// 방법 2 
int path2(int y, int x)
{
	// 기저 사례
	if (y == nTP - 1) return  triangle[y][x];

	// 캐쉬에 저장 같은 위치로 가면 나감
	int& ret = cashe[y][x];
	if (ret != -1) return ret;

	// 재귀 함수로 들어간다 그리고 삼각형의 값을 계속 더한다 
	// 재귀에 들어가는 위치는 아래와 오른쪽이다 
	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}


