#include<iostream>
#include<vector>

using namespace std;

const long long NEGINF = numeric_limits<long long> ::min();
int n, m, A[100], B[100];
int lis_cache[101][101];

int jlis(int indexA, int indexB)
{
    int& ret = lis_cache[indexA + 1][ indexB + 1];

    if (ret != -1) return ret;

    ret = 2;
    long long a = (indexA == -1 ? NEGINF : A[indexA]);
    long long b = (indexB == -1 ? NEGINF : B[indexB]);
    long long maxElenment = max(a, b);

    for (int nextA = indexA + 1; nextA < n; ++nextA)
        if (maxElenment < A[nextA])
            ret = max(ret, jlis(nextA, indexB) + 1);
    for (int nextB = indexB + 1; nextB < m; ++nextB)
        if (maxElenment < B[nextB])
            ret = max(ret, jlis(indexA, nextB) + 1);
    return ret;
}



int main() {
    
    memset(lis_cache, -1, sizeof(lis_cache));
	cout <<""<< endl;
    //lis(-1)를 한 이유는
    //0이면 0번째에서 너무 크면 수를 뺄 수 없다 그렇기 때문에 뒤에 있는 수를 넣고나 뺄 수 없다
    // 무조건 0은 된다는 것을 의미하게 된다
    //-1이면 가장 작은 수를 기준으로 진행하며 뒤에 자유럽게 넣고뺄 수 있다. 
	cout << lis3(-1)-1 << endl;
    //재귀함수 끝나고 -1를 한 이유는 가상으로 -1를 한 값도 들어가기 때문에 그값을 빼는 것이다.
    //1->13->26->39 4개
    return 0;
}
