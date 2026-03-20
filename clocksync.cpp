#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;

// 각 스위치가 연결된 시계 정보를 나타냅니다. (문제의 설정 그대로 입력)
// 'x'는 해당 스위치가 시계에 연결됨을 의미합니다.
const char linked[SWITCHES][CLOCKS + 1] = {
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",
    "x...xxxx........",
    "......xxx.x.x...",
    "x.x...........xx",
    "...x..........xx",
    "....xx.x......xx",
    ".xxxxx..........",
    "...xxx...x...x.."
};

// 모든 시계가 12시(12)를 가리키고 있는지 확인하는 함수
bool areAligned(const vector<int>& clocks) {
    for (int i = 0; i < CLOCKS; ++i) {
        if (clocks[i] != 12) return false;
    }
    return true;
}

// 스위치를 누르는 함수: 연결된 시계들이 3시간씩 돌아갑니다.
void push(vector<int>& clocks, int swtch) {
    for (int i = 0; i < CLOCKS; ++i) {
        if (linked[swtch][i] == 'x') {
            clocks[i] += 3;
            if (clocks[i] == 15) clocks[i] = 3; // 12시 다음은 3시
        }
    }
}

int solve(vector<int>& clocks, int swtch) {
    // 모든 스위치를 다 결정했을 때 (Base Case)
    if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;

    int ret = INF;
    // 이 스위치를 0번, 1번, 2번, 3번 누르는 경우를 모두 시도
    for (int cnt = 0; cnt < 4; ++cnt) {
        ret = min(ret, cnt + solve(clocks, swtch + 1));
        push(clocks, swtch); // 재귀 호출 후 스위치를 눌러 다음 상태로 변경
    }
    // (중요) 4번 누르면 원래대로 돌아오므로, 다음 호출을 위해 상태 복구 필요 없음
    // 다만 위 루프가 끝난 뒤 clocks는 원래 상태에서 4번 눌린(제자리) 상태가 됨.
    
    return ret;
}
// int main() {
//     // 입출력 속도 향상
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//
//    int C; // 테스트 케이스의 수
//    if (cin >> C) {
//        while (C--) {
//            vector<int> clocks(16);
//            for (int i = 0; i < 16; ++i) {
//                cin >> clocks[i];
//            }
//
//            int result = solve(clocks, 0);
//
//            // 불가능한 경우(INF)는 -1 출력, 가능하면 횟수 출력
//            if (result == INF) cout << -1 << endl;
//            else cout << result << endl;
//        }
//    }
//    return 0;
//}

 