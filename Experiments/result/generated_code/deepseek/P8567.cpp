#include <stdio.h>

int f(int x) {
    int ans = 0;
    while (x % 2 == 0) {
        x /= 2;
        ans += 1;
    }
    return ans;
}

int count_valid_pairs(int l, int r) {
    int count = 0;
    for (int i = l; i < r; i++) {
        if (f(i) < f(i + 1)) {
            count++;
        }
    }
    return count;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", count_valid_pairs(l, r));
    }
    return 0;
}