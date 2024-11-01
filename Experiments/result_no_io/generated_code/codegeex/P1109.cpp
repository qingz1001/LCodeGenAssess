#include <stdio.h>

int main() {
    int n, L, R;
    scanf("%d", &n);
    int groups[n];
    int sum = 0;
    int excess = 0;
    int deficit = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &groups[i]);
        sum += groups[i];
    }

    scanf("%d %d", &L, &R);

    // Calculate total excess and deficit
    for (int i = 0; i < n; i++) {
        if (groups[i] > R) {
            excess += groups[i] - R;
        } else if (groups[i] < L) {
            deficit += L - groups[i];
        }
    }

    // Check if it's possible to balance the groups
    if (excess < deficit) {
        printf("-1\n");
    } else {
        printf("%d\n", deficit);
    }

    return 0;
}