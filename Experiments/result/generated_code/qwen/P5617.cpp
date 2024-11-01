pp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, k, r;
    cin >> n >> k >> r;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    double area = 0;
    for (int i = 0; i + k - 1 < n; ++i) {
        int left = x[i], right = x[i + k - 1];
        double overlap = max(0.0, (right - left - 2 * r) / 2.0);
        area += M_PI * r * r + overlap * overlap;
    }

    cout << fixed << setprecision(10) << area << endl;
    return 0;
}