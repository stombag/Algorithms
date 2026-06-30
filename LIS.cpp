#include<iostream>
#include<vector>

using namespace std;
//완전 탐색
int lis_n = 7; 
int lis_cache[100], S[100] = {1,2,3,5,10,15,20,25};;

int lis3(int start) {
    int& ret = lis_cache[start + 1];
    if (ret != -1) return ret;
    ret = 1;
    for (int next = start+1; next < lis_n; ++next)
        if (start == -1 || S[start] < S[next])
            ret = max(ret,lis3(next) + 1);
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
