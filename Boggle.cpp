#include <iostream>
#include <vector>
#include <string>
#include <cstring> // memset 사용을 위해 필요

using namespace std;

// 8방향 (상, 하, 좌, 우, 대각선)
const int dx[8] = { -1, -1, -1,  1, 1, 1,  0, 0 };
const int dy[8] = { -1,  0,  1, -1, 0, 1, -1, 1 };
// x 좌표와 y좌표를 구현한거로 dx[0],dy[0] == (-1,-1) 이런식이다 
// 0,0이 없는 이유는 제자리 이기 때문에 변하지 않아서 문제와 맞지 않다 "인접한 칸으로 이동"
char board[5][5];
// cache[y][x][index]: (y, x) 위치에서 word[index] 글자부터 시작해서 단어를 찾을 수 있는가?
// 1: 성공, 0: 실패, -1: 아직 방문 안 함
int cache[5][5][11]; 
// 게임 세이브 포인트, 상태 [5][5] 은 현재위치, [11]은 몇번째 글자을 찾고 있는지 확인하는용도야 
string targetWord;
//어떤 문자로 게임을 진행할지 확인하는거다 


// (y, x) 위치에서 targetWord의 index번째 글자부터 매칭을 시도하는 함수
bool hasWord(int y, int x, int index) {
    // 1. 기저 사례: 범위 밖이면 실패 보드 판에서 나면 시도 못하게 한다. || 또는이다 
    if (y < 0 || y >= 5 || x < 0 || x >= 5) return false;

    // 2. 기저 사례: 현재 글자가 일치하지 않으면 실패 , 만약 타켓을 글자가 아닐때 실패한다
    if (board[y][x] != targetWord[index]) return false; 

    // 3. 기저 사례: 단어의 끝에 도달했으면 성공 (글자가 일치하는 상태로 끝남)
    if (index == targetWord.size() - 1) return true;

    // 4. 메모이제이션: 이미 계산한 적이 있다면 그 결과를 반환
    int& ret = cache[y][x][index];
    if (ret != -1) return ret;

    // 5. 인접한 8방향 탐색
    for (int dir = 0; dir < 8; ++dir) {
        int nextY = y + dy[dir];
        int nextX = x + dx[dir];
        
        // 다음 글자를 찾으러 재귀 호출
        if (hasWord(nextY, nextX, index + 1)) {
            return ret = 1; // 성공하면 1 저장 후 반환
        }
    }

    // 8방향 모두 실패했으면 실패
    return ret = 0;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int C; // 테스트 케이스 수
    cin >> C;

    while (C--) {
        // 보드 입력
        for (int i = 0; i < 5; ++i) {
            cin >> board[i];
        }

        int N; // 단어의 수
        cin >> N;
        while (N--) {
            cin >> targetWord;

            // 캐시 초기화 (-1로 설정)
            // 주의: 단어가 바뀔 때마다 캐시를 초기화해야 함
            memset(cache, -1, sizeof(cache));

            bool found = false;
            // 보드의 모든 위치에서 시작해봄
            for (int y = 0; y < 5; ++y) {
                for (int x = 0; x < 5; ++x) {
                    if (hasWord(y, x, 0)) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }

            cout << targetWord << " " << (found ? "YES" : "NO") << "\n";
        }
    }

    return 0;
}