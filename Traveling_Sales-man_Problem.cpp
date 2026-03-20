#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// === [1] 변수 및 상수 정의 (전역 변수) ===
const int Max = 20;
const double INF = 1e9;

int an;                  // 여기서 딱 한 번만 정의됨
double dist[Max][Max];  // 여기서 딱 한 번만 정의됨

// === [2] 함수 구현 ===
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
    if (path.size() == an) {
        if (dist[path.back()][path[0]] == 0) return INF;
        return currentLength + dist[path.back()][path[0]];
    }

    double ret = INF;
    for (int next = 0; next < an; ++next) {
        if (visited[next]) continue;
        int here = path.back();
        if (dist[here][next] == 0) continue;

        path.push_back(next);
        visited[next] = true;

        double cand = shortestPath(path, visited, currentLength + dist[here][next]);
        ret = min(ret, cand);

        visited[next] = false;
        path.pop_back();
    }
    return ret;
}

//int main() {
//    // 입력 속도 향상
//    ios::sync_with_stdio(false);
//    cin.tie(NULL);
//
//    // 1. 입력 받기
//    cout << "도시의 개수(n)를 입력하세요: ";
//    cin >> an;
//
//    cout << "도시 간 거리 행렬을 입력하세요 (" << an << "x" << an << "):" << endl;
//    for (int i = 0; i <an; i++) {
//        for (int j = 0; j <an; j++) {
//            cin >> dist[i][j];
//        }
//    }
//
//    // 2. 초기값 설정
//    vector<int> path;
//    vector<bool> visited(an, false);
//
//    // 0번 도시에서 시작한다고 가정
//    path.push_back(0);
//    visited[0] = true;
//
//    // 3. 함수 호출
//    double result = shortestPath(path, visited, 0.0);
//
//    // 4. 결과 출력
//    if (result >= INF) {
//        cout << "순회 불가능" << endl;
//    } else {
//        cout << "최소 비용: " << fixed << setprecision(2) << result << endl;
//    }
//
//    return 0;
//}
//
//// +
