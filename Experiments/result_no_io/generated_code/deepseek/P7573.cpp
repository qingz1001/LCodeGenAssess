#include <stdio.h>

int min_cuts(int n) {
    if (n == 1) return 0;
    int cuts = 0;
    while (n > 1) {
        cuts += 1;
        n = (n + 1) / 2;
    }
    return cuts;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", min_cuts(n));
    }
    return 0;
}