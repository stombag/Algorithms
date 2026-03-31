#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> cache(30, vector<int>(30,0));

int bino2(int n, int r) {

	if (r == 0 || n == r) return 1;
	if (cache[n][r] != -1)
		return cache[n][r];
	return cache[n][r] = bino2(n - 1, r - 1) + bino2(n - 1, r);

}

//int main() {
//	int n, r;
//
//	cout << "n과 r을 입력하세요:	";
//	cin >> n >> r;
//
//	int result = bino2(n, r);
//
//	cout << n << r << endl;
//	cout<< result << endl;
//	return 0;
//}
