pp
#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> r;

void init(int _k, vector<int> _r) {
    k = _k;
    r = _r;
    n = r.size();
}

int compare_plants(int x, int y) {
    if (r[x] == k - 1) return 1;
    if (r[y] == 0) return -1;
    if (r[x] > r[y]) return 1;
    if (r[x] < r[y]) return -1;
    return 0;
}