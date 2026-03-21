#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 두 다항식의 합을 구함 (A += B)
void addTo(vector<int>& a, const vector<int>& b, int k) {
    if (a.size() < b.size() + k) a.resize(b.size() + k);
    for (int i = 0; i < b.size(); ++i) a[i + k] += b[i];
}

// 두 다항식의 차를 구함 (A -= B)
void subFrom(vector<int>& a, const vector<int>& b) {
    for (int i = 0; i < b.size(); ++i) a[i] -= b[i];
}

// 카라츠바 알고리즘 구현부
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
    int n = a.size(), m = b.size();
    if (n < m) return karatsuba(b, a);
    if (n == 0 || m == 0) return vector<int>();
    // 크기가 작을 때는 일반적인 O(n^2) 곱셈으로 처리
    if (n <= 50) {
        vector<int> res(n + m - 1, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                res[i + j] += a[i] * b[j];
        return res;
    }

    int half = n / 2;
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

    vector<int> z2 = karatsuba(a1, b1);
    vector<int> z0 = karatsuba(a0, b0);

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

int main() {
    // 예시 입력: F는 여자, M은 남자
    // 모든 멤버가 남-남 없이 포옹하는 횟수를 구함
    string members = "MFFM";
    string fans = "FMFMFFM";

    int result = Hugs(members, fans);
    cout << "모든 멤버가 포옹하는 횟수: " << result << endl;

    return 0;
}