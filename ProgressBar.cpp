#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
	vector<int>Progress(int box, int capacity, int time){
		int bar = floor(box * capacity * (time/100.0));
		int full_bar = bar / capacity;
		int rem = bar % capacity;
		vector<int>result(box,0);
		for(int i = 0;i<full_bar && i<box;i++){
			result[i] = capacity;
		}
		if (rem > 0 && full_bar<box){
			result[full_bar] = rem;
		}
		return result;
	}
};

int main(){
	int n,k,t;
	cin>>n>>k>>t;
	Solution sol;
	vector<int> res = sol.Progress(n,k,t);
	for(auto &i:res){
		cout<<i<<" ";
	}

}