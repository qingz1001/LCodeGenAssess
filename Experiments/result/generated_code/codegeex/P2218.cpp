#include <stdio.h>
#include <algorithm>
#include <limits.h>
using namespace std;

#define MAXN 20001

struct Point {
    long long x, y;
};

Point trees[MAXN];
long long minL = LLONG_MAX;

bool compareX(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool compareY(const Point &a, const Point &b) {
    return a.y < b.y;
}

void checkCoverage(int n, long long L) {
    // Check if all trees are covered by placing one square at each corner
    for (int i = 0; i < n; ++i) {
        if (trees[i].x > L || trees[i].y > L) {
            return;
        }
    }
    minL = min(minL, L);
}

void solve(int n) {
    // Sort trees by x and y coordinates
    sort(trees, trees + n, compareX);
    sort(trees, trees + n, compareY);

    // Try placing squares at each combination of corner points
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long L = max(trees[n-1].x - trees[i].x, trees[n-1].y - trees[j].y);
            checkCoverage(n, L);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &trees[i].x, &trees[i].y);
    }

    solve(n);

    printf("%lld\n", minL);
    return 0;
}