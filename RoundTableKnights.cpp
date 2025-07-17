#include <iostream>
#include <vector>
using namespace std;

// Function to check if a regular polygon of size 'k' can be formed
bool check(int n, const vector<int>& mood, int k) {
    if (k < 3) return false; // only polygons with 3 or more vertices are valid
    int step = n / k;
    for (int start = 0; start < step; ++start) {
        bool all_good = true;
        for (int i = 0; i < k; ++i) {
            int index = (start + i * step) % n;
            if (mood[index] != 1) {
                all_good = false;
                break;
            }
        }
        if (all_good) return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;

    vector<int> mood(n);
    for (int i = 0; i < n; ++i) {
        cin >> mood[i];
    }

    // Try all divisors k of n where k >= 3
    for (int k = 3; k <= n; ++k) {
        if (n % k == 0) {
            if (check(n, mood, k)) {
                cout << "YES" << endl;
                return 0;
            }
        }
    }

    cout << "NO" << endl;
    return 0;
}
