#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string WayTooLong(string s) {
        if (s.length() > 10) {
            return s[0] + to_string(s.length() - 2) + s[s.length() - 1];
        } else {
            return s;
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    Solution sol;
    for (auto &i : arr) {
        cout << sol.WayTooLong(i) << endl;
    }

    return 0;
}
