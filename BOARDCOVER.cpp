#include<iostream>
#include<vector>
#include<string>
using namespace std;
// 완전 탐색, 재귀, 백트래킹(안되면 다시 치우고 다른 방법으로 시도)

//ㄴ자 모양 블록(3칸 자지)을 덮는 4가지 방법을 상대 좌표로 정의한다. -> 룩업 테이블
// 룩업 테이블 : 미리 계산된 값을 배열로 넣어두고 인덱스만 꺼내는 방식
const int coverType[4][3][2] = {
	{{0,0},{1,0},{0,1}},
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,1}},
	{{0,0},{1,0},{1,-1}}
};



// 블록 놓기, 블록 치우기, 겹침/경계 검사를 수행한다.
// board : 게임 판, yx 기준점 좌표, type : 덮을 블록의 모양, Dleta: 1이면 덮기, -1이면 치우기 
bool setBoard(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true; //성공 여부 확인

	// 블록을 구성하는 3개의 칸을 하나씩 처리
	for (int i = 0; i < 3; ++i) {
		//  블록 조각들이 실제 게임판 어디에 떨어질지 계산하는 과정
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		// [type][i][0] = [4][3][2] 이렇게 비교하면 보기 편하다
		//coverType에 있는 좌표는 상대좌표, 기준점으로부터 얼마나 떨어져 있나
		// ny, nx는 절대좌표, 실제 게임판 배열의 인덱스
	
		//블록이 게임판 밖으로 삐져나가는지 확인하는 안전장치
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()) ok = false;
		// ny < 0 : 위쪽 벽을 뚥었나?,
		// ny >= board.size(): 아래쪽 벽을 뚫었나?,
		// nx < 0 : 왼쪽 벽을 뚫었나?,
		// nx >= board[0].size() : 오른쪽 벽을 뚫었나?
		
		// 값 갱신 및 겹침 검사: 실제로 블록을 놓고 이미 누가 있는지 확인하는 과정
		else if ((board[ny][nx] += delta) > 1)
			ok = false;

	}
	return ok;
}

int cover(vector<vector<int>>& board) {
	// -1로 해야 못 찾았을때 구분 가능하다
	int y = -1, x = -1; 
	// 이중 반복문으로 게임판 정체를 훑는다 빈칸이 있는 지 확인 하는 용도이다. 
	// 찾으면 x,y에 그값을 입력하고 나온다. 
	for (int i = 0; i < board.size(); ++i) {
		// 2차원 배열에서 사이즈를 크기를 측정할때 배열이 없으면 세로줄(y), 배열이 있으면 가로줄(x)을 의미한다. 
		for(int j= 0;j < board[i].size(); ++j)
			if (board[i][j] == 0) { // 빈칸(0) 발견
				y = i;
				x = j;
				break; // 찾았으니 안쪽 루프 탈출

			}
		if (y != -1) break; // 찾았으니 바깥쪽 루프 탈출

	}

	// y가 여전히 -1이라는 건, 위에서 빈 칸(0)을 하나도 못 찾았다는 뜻이다. 
	if (y == -1) return 1;
	// 찾은 방법은 수를 저장할 변수
	int ret = 0; 

	// 여기서 빈칸으로 이동한 xy기준으로 SetBoared가 true면 ret 값을 증가 시키고 다시 실행한다.
	for (int type = 0; type < 4; ++type) {
		// 1차 시도 : set 함수가 true를 반환하면(성공적으로 놓았으면)
		if (setBoard(board, y, x, type, 1))
			// 2차 시도 : 나머지 칸들도 채운다
			// 재귀로 다시 cover로 함수 안들어 들어간다 끝까지 들어가서 해결을 하면 함수에서 나와 ret에 값을 더한다.
			// 내가 부른 cover가 자식, 손자, 증손자까지 끝까지 다녀와서 퍼즐을 완성한 횟수(1들의 합)를 전부 들고 오면, 그때 내 지갑(ret)에 더하겠다!`
			ret += cover(board);
	
		// 블록을 다시 치운다
		// 다음 type을 시도하기 위해서 치워야 한다.
		setBoard(board, y, x, type, -1);

	}
	// 최종 방법의 수 보고
	return ret;
	
}

//int main() {
//    // 빠른 입출력을 위한 설정 (선택 사항)
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//
//    int C; // 테스트 케이스의 수
//    if (!(cin >> C)) return 0;
//
//    while (C--) {
//		// H은 줄 세로
//		// W은 칸 가로
//        int H, W;
//        cin >> H >> W; // 높이와 너비 입력
//
//        // 게임판 생성 (0: 빈 칸, 1: 검은 칸/채워진 칸)\
//		// 크기가 w(가로)이고 Int 형 데이터를 담는 1차원 벡터를 만들어라
//		// 이름은 board이고 안에 int형 벡터를 담는 큰 통(2차원 벡터)을 만들어라 
//        vector<vector<int>> board(H, vector<int>(W));
//        int whiteCount = 0; // 빈 칸 개수 세기
//
//		// 이 반복문은 사용자가 보드를 입력하는 칸을 나타난것이다. 
//        for (int i = 0; i < H; ++i) {
//			// 한줄씩 H 만큼 반복시킨다.  
//            string row;
//            cin >> row; // 한 줄씩 문자열로 입력 받음 (예: "#..#..")
//            for (int j = 0; j < W; ++j) {
//                if (row[j] == '#') { //row에 입력한 값에서 문자열은 배열에서 하나씩 들어간다 그점을 이용해서 로직을 짜고
//					// true면 board에 1을 넣는다.
//                    board[i][j] = 1; // '#'은 벽(검은 칸)이므로 1
//                } else {
//                    board[i][j] = 0; // '.'은 빈 칸이므로 0
//                    whiteCount++;
//                }
//            }
//        }
//
//        // [최적화] 가지치기
//        // 빈 칸의 개수가 3의 배수가 아니면 절대로 3칸짜리 블록으로 채울 수 없음
//        if (whiteCount % 3 != 0) {
//            cout << 0 << endl;
//        } else {
//            cout << cover(board) << endl;
//        }
//    }
//
//    return 0;
//}


