pp
#include <iostream>
#include <vector>
#include <algorithm>

int n, k;
std::vector<int> r;

void init(int _k, std::vector<int> _r) {
    k = _k;
    r = _r;
    n = r.size();
}

int compare_plants(int x, int y) {
    if (r[x] == k - 1) return 1;
    if (r[y] == 0) return -1;
    
    int left = (x + 1) % n;
    int right = (y + k - 1) % n;
    
    if (left == right) return 0;
    
    if (left == y) return -1;
    if (right == x) return 1;
    
    return 0;
}