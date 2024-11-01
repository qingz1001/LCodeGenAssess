pp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int binary_search(const vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1, mid, cnt = 0;
    while (l < r) {
        cnt++;
        bool w = rand() % 2;
        mid = (l + r + w) / 2;
        if (nums[mid] - w < target) l = mid + !w;
        else r = mid - w;
    }
    return cnt;
}

int main() {
    srand(time(0));
    int n, q;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    cin >> q;
    while (q--) {
        int target;
        cin >> target;
        cout << binary_search(nums, target) << endl;
    }
    return 0;
}