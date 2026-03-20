#include <iostream>
#include <vector>
using namespace std;

int bruteForce(const vector<int>& h) {
	int ret = 0;
	// fence의 크기를 N에 넣기 
	int N = h.size();
for (int left = 0; left < N; ++left) {
	int minHeight = h[left];
		for (int right = left; right < N; ++right) {
	// 왼쪽부터 시작해서 왼쪽의 크기와 오른쪽의 크기를 비고 하기
	// 그리고 min으로 작은 또는 동일한 수를 minHeight에 다시 넣기 
			minHeight = min(minHeight, h[right]);
			// max는 크값 또는 동일한 수를 ret에 넣기 
			// left 와 right의 값이 같을경우 1이 남고 ret의 값을 최신화한다. 
			// 만약 이전 값이 더 클경우 값은 그대로 남고 작을 경우 ret값이 교체가 된다. 
			ret = max(ret, (right - left + 1) * minHeight);

		}
	}
	return ret;

}

vector<int> h;
int solve(int left, int right) {
	// 판이 한개 남으면 그 판자가 곧 면적이 된다 가로가 1이니깐
	if (left == right) return h[left];
	int mid = (left + right) / 2;
	//재귀함수
	// 왼쪽 절반에서 가장 큰놈과 오른쪽 절반에서 가장큰놈을 구한다. 
	int ret = max(solve(left, mid), solve(mid + 1, right));
	// 중간 지점을  lo, hi로 둔다 그리고 min으로 비교해서 가운데로 가로지르는 높이를 구한다
	int lo = mid, hi = mid + 1;
	// 여기서 작은 것을 선택한다.
	int height = min(h[lo], h[hi]);
	//  height를 2곱한 이유는 lo와 hi가 확정적으로 포함 되기때문이다.
	ret = max(ret, height * 2);
	
	// 중간 값이 왼쪽값보다 클경우 또는 중간+1값이 오른쪽 보다 클경우실행된다
	while (left < lo || hi < right)
	{
		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
			++hi; // 오른쪽 판자가 높으면 오른쪽으로 확장 한다
			height = min(height, h[hi]);

		}
		else {
			--lo; // 왼쪽 판자가 더 높으면 왼쪽으로 확장한다. 
			height = min(height, h[lo]);
		}
		// 계속 비교하면서 조건이 끝날때 까지 실행한다.
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;

}

int main() {
    // 예시 울타리 높이 배열 (게임 지형 데이터라고 생각해보세요!)
    // [7, 1, 5, 9, 6, 7, 3]
    //vector<int> fence = {7, 1, 5, 9, 6, 7, 3};

    //int result = bruteForce(fence);

    //cout << "울타리 높이 데이터: ";
    //for (int h : fence) cout << h << " ";
    //cout << endl;

    //cout << "가장 큰 직사각형의 넓이: " << result << endl;

   //return 0;
	h = {1, 1, 1, 1, 1, 1, 0};

    cout << "--- 분할 정복 알고리즘 실행 ---" << endl;
    cout << "울타리 데이터: ";
    for (int val : h) cout << val << " ";
    cout << endl;

    // 전체 구간(0번 인덱스부터 마지막 인덱스까지)에 대해 실행
    int result = solve(0, h.size() - 1);

    cout << "최대 직사각형 넓이: " << result << endl;

    return 0;

}