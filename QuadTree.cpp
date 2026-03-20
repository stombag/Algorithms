#include <iostream>
#include <string>
#include <vector>

using namespace std;

string S;
int cursor;

string reverse() {
	// 입력한 문자열에서 해당하는 배열의 위치를 Char로 변환하고 head로 넣는다. 
	// 전체에서 하나를 쏙빼고 다시 포장하는 느낌
	char head = S[cursor];
	cursor++;
	// 문제에서 x는 안에 검정과 하양 둘다 있을 경우 나오는데 만약 첫 헤드가 b,w면 변하는게 없이 똑같이 나온다.
	//   x 인경우 그안에서 또 재배치 정의?를 해야하기때문에 x가 많을 수록 깊게 들어간다.
	if (head == 'b' || head == 'w') {
		// C++ 문법상 문자(char)를 문자열(string)로 변환하려면 '반복 횟수(1)'를　넣어야한다．
		return string(1, head);
	}

	string upperLeft = reverse();
	string upperRight = reverse();
	string lowerLeft = reverse();
	string lowerRight = reverse();

	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;

}

//int main() {
//	int C;
//	cin >> C;
//
//	while (C--) {
//		//문자열 변수를 입력한다
//		cin >> S;
//		// cursor : 어디 인지 확인하는 용도 이다
//		cursor = 0;
//		cout << reverse() << endl;
//	}
//	return 0;
//}