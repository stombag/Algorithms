#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void printVec(string name, const vector<int>& v) {
    cout << name << ": [ ";
    for (int x : v) cout << x << " ";
    cout << "]" << endl;
}
// 두 다항식의 합을 구함 (A += B)
void addTo(vector<int>& a, const vector<int>& b, int k) {
    //  a의 크기가 부족하면 b를 k만큼 밀어서 더할 수 있도록 늘려준다. 
    if (a.size() < b.size() + k) a.resize(b.size() + k);

    for (int i = 0; i < b.size(); ++i) a[i + k] += b[i];
}

// 두 다항식의 차를 구함 (A -= B)
void subFrom(vector<int>& a, const vector<int>& b) {
    for (int i = 0; i < b.size(); ++i) a[i] -= b[i];
}

// 카라츠바 알고리즘 구현부
// 곱셈 횟수를 줄이기 위해 덧셈과 뺄셈을 활용하는 것
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
    int n = a.size(), m = b.size();
    // 아래 if는 편의성을 위해서 앞에 더 a의 값이 너 클 경우 해당된다. 
    if (n < m) return karatsuba(b, a);
    // 한쪽이 0이면 결과는 0이다 그래서 리턴 값은 비어진 벡터를 준다.
    if (n == 0 || m == 0) return vector<int>();

    // 크기가 작을 때는 일반적인 O(n^2) 곱셈으로 처리
    // n사이즈를 계속쪽 쪼개고 50 이하가 되면 계산해서 값을 넣는다 .
    // 
    if (n <= 50) {
        vector<int> res(n + m - 1, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                res[i + j] += a[i] * b[j];
        return res;
    }

    // 함수의 메인 
    // 다항식을 자르는 기준선 
	//  ex) A = 10x^3 + 5x^2 + 3x + 1 
    //   10x^3  5x^2  3x 1 
    int half = n / 2;
    // 벡터 a를 Begin, end는 그 범위에 해당되는 값을 다 a0에 넣게다는거다 
    // 그래서 백터 a에 들어간 값음 절반을 나누어서 넣었다.
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());

    // half보다 b가 더 짧을 수 있기 때문에 
    // min은 더 작은 숫자를 선택하기 때문에 Min으로 사이즈 또는 절반값을 골라서 범위를 선택한다.
    // b.size가 2고 half가 4 이면 min<int> ==2가 된다. 
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

    vector<int> z2 = karatsuba(a1, b1); // 50개 이하가 될 때까지 쪼개러 들어감
    vector<int> z0 = karatsuba(a0, b0); // 50개 이하가 될 때까지 쪼개러 들어감


    addTo(a0, a1, 0); 
    addTo(b0, b1, 0);
    vector<int> z1 = karatsuba(a0, b0);

    subFrom(z1, z0);
    subFrom(z1, z2);

    vector<int> res;
    addTo(res, z0, 0);
    addTo(res, z1, half);
    addTo(res, z2, half + half);
    return res;


}
int Hugs(string members, string fans) {
    int N = members.size();
    int M = fans.size(); // 쉼표 대신 세미콜론이나 별도 선언 필요
    vector<int> A(N), B(M);

    for (int i = 0; i < N; ++i) A[i] = (members[i] == 'M');
    for (int i = 0; i < M; ++i) B[M - i - 1] = (fans[i] == 'M');

    // 카라츠바를 이용한 곱셈 (다항식 곱셈 결과 반환)
    vector<int> C = karatsuba(A, B);
    
    int allHugs = 0;
    // N-1부터 M-1까지의 위치가 모든 멤버가 팬과 매칭되는 구간입니다.
    for (int i = N - 1; i < M; ++i)
        if (C[i] == 0) // 결과가 0이면 남-남(1*1) 매칭이 하나도 없다는 뜻
            ++allHugs;
    return allHugs;
}

//int main() {
//    // 예시 입력: F는 여자, M은 남자
//    // 모든 멤버가 남-남 없이 포옹하는 횟수를 구함
//    string members = "MFMMMM";
//    string fans = "FMFMFFMMMFMFMFMFFMFMMFFFFMFMFM";
//
//    int result = Hugs(members, fans);
//     cout << "모든 멤버가 포옹하는 횟수: " << result << endl;
//
////int sizeA = 60; // 60항 다항식
////    int sizeB = 40; // 40항 다항식
////    
////    vector<int> polyA(sizeA), polyB(sizeB);
////
////    // 모든 항을 1로 채우거나, i % 10 같은 규칙으로 채웁니다.
////    for(int i = 0; i < sizeA; ++i) polyA[i] = 1; 
////    for(int i = 0; i < sizeB; ++i) polyB[i] = 1;
////
////    cout << sizeA << "항과 " << sizeB << "항의 곱셈을 시작합니다..." << endl;
////
////    // 카라츠바 실행
////    vector<int> result = karatsuba(polyA, polyB);
////
////    cout << "결과 다항식의 총 항의 개수: " << result.size() << endl;
////    cout << "최고차항의 계수: " << result.back() << endl;
////
////    return 0;
//}