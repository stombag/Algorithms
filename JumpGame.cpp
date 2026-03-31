#include<iostream>
#include<vector>

using namespace std;

int boardSize;
vector<vector<int>> gameMap(100, vector<int>(100, 0)); // 맵
vector<vector<int>> memoPad(100, vector<int>(100, -1)); // 메모이제이션

bool jump(int y, int x) {// 메모이제이션 X 
    if (y >= boardSize || x >= boardSize) return false; // 기저사례에서 벗어날때
    if (y == boardSize - 1 && x == boardSize - 1) return true; // 도착할때
    
    int jumpSize = gameMap[y][x]; //
    
    // 무한 루프 방지 (0일 경우 더 이상 못 가므로 종료)
    if (jumpSize == 0) return false;
    
    return jump(y + jumpSize, x) || jump(y, x + jumpSize);
}

bool jump2(int y, int x)
{
    // 이건 위에 있는 부분과 같가. 
    if (y >= boardSize || x >= boardSize) return 0;
    if (y == boardSize - 1 && x == boardSize - 1) return 1;
    
    // 간편한 이름 ret 라는 이름으로 참조변수 하나 만든다  ret의 주소는 memoPad의 주소와 같다 == 
    int& ret = memoPad[y][x];
    // 중복 방지로 != -1 누눈가 이미 이 칸을 사용해서 저장하고 있다 그리고 그값을 돌려준다 .
    // 처음에는 -1 로 했으니깐 지나가면 0또는1로 남겨진다 그래서 여기는 안전해 이상없으니깐 지나가 라는 느낌이다.
    if (ret != -1) return ret;
    
    int jumpSize = gameMap[y][x];
    
    // 무한 루프 방지
    if (jumpSize == 0) return ret = 0;
    // || 아래로 가거나 오른쪽으로 가거나 실행 한다. 실행은 아래 부터 시작한다.
    // 만약 아래로 가서 너무 값이 커지지면 실행을 종료하고 다시 올라와서 오른쪽도 안되는지 계산한다 이게 백트래킹이다
    return ret = (jump2(y + jumpSize, x) || jump2(y, x + jumpSize));
}

//int main() {
//    // 보드 데이터 주입
//    //gameMap = {
//    //    {2, 5, 1, 6, 1, 4, 1},
//    //    {6, 1, 1, 2, 2, 9, 3},
//    //    {7, 2, 3, 2, 1, 3, 1},
//    //    {1, 1, 3, 1, 2, 4, 1},
//    //    {4, 2, 1, 4, 1, 2, 1},
//    //    {1, 9, 1, 1, 1, 1, 1},
//    //    {1, 1, 1, 1, 1, 1, 0}
//    //};
//    gameMap = {
//        {1, 1, 1, 1},
//        {1, 1, 1, 1},
//        {1, 1, 1, 1},
//        {1, 1, 1, 0}
//    };
//    
//    boardSize = gameMap.size();
//
//    // memoPad(cache)를 다시 한번 -1로 깔끔하게 초기화 (기존 100x100 무시하고 현재 크기에 맞춤)
//    memoPad.assign(boardSize, vector<int>(boardSize, -1));
//
//    if (jump2(0, 0)) {
//        cout << "도착" << endl;
//    }
//    else {
//        cout << "불가능" << endl;
//    }
//
//    return 0;
//}