#include<iostream>
#include<vector>

using namespace std;

int lis(const vector<int>& A) {
	if (A.empty()) return 0;

	int ret = 0;

	for (int i = 0; i < A.size(); i++) {
		vector<int> B;
		for (int j = i + 1; j < A.size(); j++) {
			if (A[i] < A[j])
				B.push_back(A[j]);
		
		}
		return ret; 
	}
}

int main() {

}
