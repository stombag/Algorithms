#include <iostream>
using namespace std;


int n; // 학생 수
bool areFriends[10][10]; // 친구 관계를 저장하는 인접 행렬
// 최대 학생의 수는 10명이고 0~9으로 되는데 0번째 학생이 다른 학생과 친한 친구인지 확인하는 용도이다.
// [0][1] 이 친구이면 여기세 t로 되어지고 친한 친구가 아니면 f로 된다.
//   |  0  |  1  |  2  |  3
// 0 |  F  |  T  |  T  |  F  이러면 0 은 1, 2와 친하다 


int countPairings(bool taken[10]) {
	// 남은 학생 중 가장 번호가 빠른 학생을 찾는다. 
    // 여기서 taken은 정한 학생이 짝이 있는 지 확인하는 용도이다 
    int firstFree = -1; // 아직 짝을 못 찾은 학생
	for (int i = 0; i < n; ++i) {
		if (!taken[i]) {
			firstFree = i;
			break;

		}
	}
  
	if (firstFree == -1) return 1; // 모든 짝을 찾았을때 

	int ret = 0;
    // 학생과 짝지을 학생을 결정한다. 
	for (int pairWith = firstFree + 1; pairWith < n; ++pairWith) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true; // 짝을 맺음 
			ret += countPairings(taken);// 다시 재귀 호출
			taken[firstFree] = taken[pairWith] = false; // 짝을 해제 

		}
	}
	return ret;
}
//int main() {
//    int C; // 테스트 케이스의 수
//    cin >> C;
//    // 케이스를 만든 이유는 학생의 수가 다른 경우도 생각해야하기 때문이다. 
//    // 3명일 수도 있고 6명일 수도 있고 
//
//    while (C--) {
//        int m; // m: 친구 쌍의 수
//        cin >> n >> m;
//
//        // 전역 변수 및 배열 초기화 (테스트 케이스마다 리셋 필수)
//        memset(areFriends, false, sizeof(areFriends));
//        bool taken[10];
//        memset(taken, false, sizeof(taken));
//
//        // 친구 관계 입력 받기
//        for (int i = 0; i < m; ++i) {
//            int u, v;
//            cin >> u >> v;
//            // 친구 관계는 양방향이므로 둘 다 true로 설정
//            areFriends[u][v] = areFriends[v][u] = true;
//        }
//
//        // 결과 계산 및 출력
//        cout << countPairings(taken) << endl;
//    }
//
//    return 0;
//}