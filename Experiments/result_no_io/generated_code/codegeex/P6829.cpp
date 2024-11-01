#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200010

int n, k, q;
int r[MAXN];

void init(int k, int r[]) {
    n = k;
    for (int i = 0; i < n; i++) {
        this->r[i] = r[i];
    }
}

int compare_plants(int x, int y) {
    int a = x, b = y;
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
    if (b - a == k - 1) {
        if (r[a] < r[b]) {
            return 1;
        } else if (r[a] > r[b]) {
            return -1;
        } else {
            return 0;
        }
    }
    int c = (a + k - 1) % n;
    if (c < a) {
        if (r[a] < r[c]) {
            return 1;
        } else if (r[a] > r[c]) {
            return -1;
        } else {
            return 0;
        }
    }
    int d = (b + k - 1) % n;
    if (d == b) {
        if (r[b] < r[a]) {
            return 1;
        } else if (r[b] > r[a]) {
            return -1;
        } else {
            return 0;
        }
    }
    if (r[a] < r[c] && r[b] < r[d]) {
        return 1;
    } else if (r[a] > r[c] && r[b] > r[d]) {
        return -1;
    } else {
        return 0;
    }
}

int main() {
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    int r[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    init(k, r);
    int x, y;
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);
        int result = compare_plants(x, y);
        printf("%d\n", result);
    }
    return 0;
}