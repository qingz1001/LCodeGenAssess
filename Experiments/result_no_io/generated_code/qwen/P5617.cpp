pp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const double EPS = 5e-8;
const double PI = acos(-1.0);

double area(double r) {
    return PI * r * r;
}

int main() {
    int n, k;
    double r;
    cin >> n >> k >> r;
    vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    double max_area = 0;
    for (int i = 0; i <= n - k; ++i) {
        double left = x[i];
        double right = x[i + k - 1];
        double diameter = right - left;
        double radius = diameter / 2.0;
        if (radius > r) {
            max_area += area(r);
        } else {
            max_area += area(radius);
        }
    }

    cout << fixed << setprecision(15) << max_area << endl;
    return 0;
}